#include "Board.h"
#include <iostream>
#include "Command.h"

Board::Board(GameScene::GameState& state, Scene::Context& context)
    : mContext(context), mGameState(state) {
    // initialize mCells first
    // attempting to insert this loop into the following loop
    // causes some weird error where only one square
    // is drawn on the screen
    mCells.reserve(10);
    for (int i = 0; i < 10; i++) {
        std::vector<BoardCell> row;
        row.reserve(10);
        for (int j = 0; j < 10; j++) {
            row.emplace_back(i, j, context, state);
        }
        mCells.push_back(row);
    }

    // set properties of each cell
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mCells[i][j].setSize(sf::Vector2f(64, 64));
            mCells[i][j].setPosition(69 * i + 40, 69 * j + 40);
            mCells[i][j].rectangle.setOutlineThickness(2);
            mCells[i][j].rectangle.setOutlineColor(sf::Color::Black);
            mCells[i][j].onClickCommand.reset(new GameCommands::PlaceShip(
                mGameState, mCells[i][j], context.confirm));
            mCells[i][j].setStateColor(Button::State::Default,
                                       sf::Color(12, 25, 42));

            const int boardSize = context.gameSettings.getBoardSize().x;
            int xOffset = (10 / 2 - boardSize / 2);
            int yOffset = xOffset;
            if (boardSize % 2 != 0) {
                yOffset--;
            }

            if (i >= xOffset && i < xOffset + boardSize && j >= yOffset &&
                j < yOffset + boardSize) {
                mCells[i][j].setStateColor(Button::State::Default,
                                           sf::Color(45, 105, 173));
                mCells[i][j].setStateColor(Button::State::Hovered,
                                           sf::Color(150, 180, 214));
                mCells[i][j].setStateColor(Button::State::Pressed,
                                           sf::Color(222, 173, 31));
                mCells[i][j].setStateColor(Button::State::Released,
                                           sf::Color(222, 173, 31));
                mCells[i][j].setState(BoardCell::State::None);
            }
        }
    }

    // set grid coordinates
    for (int i = 0; i < 10; i++) {
        mLetters[i].setFont(context.font);
        mLetters[i].setCharacterSize(15);
        mLetters[i].setPosition(69 * i + 65, 16);
        mLetters[i].setString((char)('A' + i));
        mLetters[i].setFillColor(sf::Color::White);

        mNumbers[i].setFont(context.font);
        mNumbers[i].setCharacterSize(15);
        mNumbers[i].setPosition(20, 69 * i + 65);
        mNumbers[i].setString(std::to_string(i + 1));
        mNumbers[i].setFillColor(sf::Color::White);
    }
    mNumbers[9].setPosition(7, mNumbers[9].getPosition().y);
}

Board::~Board() {}

std::vector<BoardCell>& Board::operator[](int row) { return mCells[row]; }

unsigned int Board::getNumberOfShips() {
    unsigned int sum = 0;
    for (auto i = mCells.begin(); i != mCells.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            if (j->getState() == BoardCell::State::Ship) {
                sum++;
            }
        }
    }
    return sum;
}

void Board::setBattlePhase() {
    for (auto i = mCells.begin(); i != mCells.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            j->onClickCommand.reset(
                new GameCommands::Attack(mGameState, *j, mContext));
        }
    }
}

bool Board::input(sf::Event e) {
    for (auto i = mCells.begin(); i != mCells.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            j->input(e);
        }
    }
    return true;
}

bool Board::update(sf::Time deltaTime) {
    for (auto i = mCells.begin(); i != mCells.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            j->update(deltaTime);
        }
    }
    return true;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto i = mCells.begin(); i != mCells.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            target.draw(*j, states);
        }
    }
    for (int i = 0; i < 10; i++) {
        target.draw(mLetters[i], states);
        target.draw(mNumbers[i], states);
    }
}