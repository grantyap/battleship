#include "SettingsScene.h"
#include "Command.h"

SettingsScene::SettingsScene(SceneStack& stack, Context& context)
    : Scene(stack, context),
      mSettingsText("Settings", context.font),
      mNumberOfShipsText("", context.font),
      mBoardSizeText("", context.font),
      mIncreaseShips("+", context.font),
      mDecreaseShips("-", context.font),
      mIncreaseBoard("+", context.font),
      mDecreaseBoard("-", context.font),
      playButton(100, context.window.getSize().y-100-30, 300, 30, "Play", context.font) {
    mBackground.setPosition(0, 0);
    sf::Vector2f windowSize(context.window.getSize().x,
                            context.window.getSize().y);
    mBackground.setSize(windowSize);
    mBackground.setFillColor(sf::Color::Black);
    mSettingsText.setPosition(100, 100);

    sf::Vector2f buttonSize(45, 45);

    mNumberOfShipsText.setPosition(100, 200);
    mDecreaseShips.setPosition(450, 200);
    mDecreaseShips.setSize(buttonSize);
    mDecreaseShips.onClickCommand.reset(new SettingsCommand::DecreaseShips(context));
    mIncreaseShips.setPosition(500, 200);
    mIncreaseShips.setSize(buttonSize);
    mIncreaseShips.onClickCommand.reset(new SettingsCommand::IncreaseShips(context));

    mBoardSizeText.setPosition(100, 250);
    mDecreaseBoard.setPosition(450, 250);
    mDecreaseBoard.setSize(buttonSize);
    mDecreaseBoard.onClickCommand.reset(new SettingsCommand::DecreaseBoard(context));
    mIncreaseBoard.setPosition(500, 250);
    mIncreaseBoard.setSize(buttonSize);
    mIncreaseBoard.onClickCommand.reset(new SettingsCommand::IncreaseBoard(context));

    playButton.onClickCommand.reset(
        new SceneCommand::ChangeAndRemoveScene(*this, Scene::ID::Game));
}

SettingsScene::~SettingsScene() {}

bool SettingsScene::input(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyReleased: {
            if (e.key.code == sf::Keyboard::Escape) {
                requestScenePop();
            } else if (e.key.code == sf::Keyboard::Up) {
                SettingsCommand::IncreaseShips(getContext()).execute();
            } else if (e.key.code == sf::Keyboard::Down) {
                SettingsCommand::DecreaseShips(getContext()).execute();
            } else if (e.key.code == sf::Keyboard::Right) {
                SettingsCommand::IncreaseBoard(getContext()).execute();
            } else if (e.key.code == sf::Keyboard::Left) {
                SettingsCommand::DecreaseBoard(getContext()).execute();
            }
        }
        default:
            break;
    }
    mDecreaseShips.handleInput(e);
    mIncreaseShips.handleInput(e);

    mDecreaseBoard.handleInput(e);
    mIncreaseBoard.handleInput(e);

    playButton.handleInput(e);

    return false;
}

void SettingsScene::draw() {
    getContext().window.draw(mBackground);
    getContext().window.draw(mSettingsText);

    getContext().window.draw(mNumberOfShipsText);
    getContext().window.draw(mDecreaseShips);
    getContext().window.draw(mIncreaseShips);

    getContext().window.draw(mBoardSizeText);
    getContext().window.draw(mDecreaseBoard);
    getContext().window.draw(mIncreaseBoard);

    getContext().window.draw(playButton);
}

bool SettingsScene::update(sf::Time deltaTime) {
    unsigned int tiles = getContext().gameSettings.getBoardSize().x *
                               getContext().gameSettings.getBoardSize().y;
    if (getContext().gameSettings.getNumberOfShips() > tiles / 2) {
        getContext().gameSettings.setNumberOfShips(tiles/2);
    }

    mNumberOfShipsText.setString(
        std::string("Number of ships: ") +
        std::to_string(getContext().gameSettings.getNumberOfShips()));
    mBoardSizeText.setString(
        std::string("Board size: ") +
        std::to_string(getContext().gameSettings.getBoardSize().x) +
        std::string(" x ") +
        std::to_string(getContext().gameSettings.getBoardSize().y));

    mDecreaseShips.update(deltaTime);
    mIncreaseShips.update(deltaTime);

    mDecreaseBoard.update(deltaTime);
    mIncreaseBoard.update(deltaTime);

    playButton.update(deltaTime);

    return false;
}