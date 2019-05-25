#include "Command.h"
#include "Board.h"
#include <iostream>

Board::Board(GameScene::GameState& state, Scene::Context& context) : mContext(context), mGameState(state), mCells() {
    // initialize mCells first
    // attempting to insert this loop into the following loop
    // causes some weird error where only one square
    // is drawn on the screen
    for (int i = 0; i < 10; i++) {
        std::vector<BoardCell> row;
        for (int j = 0; j < 10; j++) {
            row.emplace_back(BoardCell(i, j, context));
        }
        mCells.push_back(row);
    }

    // set properties of each cell
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << i << ", " << j << std::endl;
            mCells[i][j].setSize(sf::Vector2f(64, 64));
            mCells[i][j].setPosition(69 * i + 40, 69 * j + 40);
            mCells[i][j].rectangle.setOutlineThickness(2);
            mCells[i][j].rectangle.setOutlineColor(sf::Color::Black);
            mCells[i][j].onClickCommand.reset(new GameCommands::PlaceShip(mGameState, mCells[i][j]));

            const int boardSize = context.gameSettings.getBoardSize().x;
            int xOffset = (10 / 2 - boardSize / 2);
            int yOffset = xOffset;
            if (boardSize % 2 != 0) {
                yOffset--;
            }

            if (i >= xOffset && i < xOffset + boardSize && j >= yOffset &&
                j < yOffset + boardSize) {
                mCells[i][j].setState(BoardCell::State::None);
                mCells[i][j].setFillColor(sf::Color::Magenta);
            }

            if (mCells[i][j].getState() == BoardCell::State::None) {
                std::cout << i << ", " << j << " ACTIVE\n";
            }
        }
    }
}

Board::~Board() {}

std::vector<BoardCell>& Board::operator[](int row) {
    return mCells[row];
}

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
            j->onClickCommand.reset(new GameCommands::Attack(mGameState, *j));
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
}