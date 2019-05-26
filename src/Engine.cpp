#include "Engine.h"
#include <iostream>
#include "Scene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include "PauseScene.h"

using std::cout;

Engine::Engine()
    : mWindow(sf::VideoMode(windowWidth, windowHeight), "Battleship", sf::Style::Titlebar | sf::Style::Close),
      mFont(),
      mGameSettings(),
      mSceneStack(Scene::Context(mWindow, mFont, mGameSettings, mBackground, mGameBackground, mPanel, mMainMenuMusic, mGameSceneMusic, mVictoryMusic, mThreeStars, mMedal)),
      mFpsCounter(),
      mFpsTime(sf::Time::Zero) {
    mWindow.setFramerateLimit(120);

    if (!mFont.loadFromFile("res/fonts/ARCADE_N.TTF")) {
        throw std::runtime_error("Could not load font.");
    }

    if(!mBackground.loadFromFile("res/img/title/bg.png", sf::IntRect(0, 0, 1999, 1123))) {
        throw std::runtime_error("Could not load res/img/title/bg.png");
    }

    if(!mGameBackground.loadFromFile("res/img/platform/metal_bg.png", sf::IntRect(0, 0, 1999, 1123))) {
        throw std::runtime_error("Could not load res/img/platform/metal_bg.png");
    }

    if(!mPanel.loadFromFile("res/img/platform/panel.png", sf::IntRect(0, 0, 1999, 1123))) {
        throw std::runtime_error("Could not load res/img/platform/panel.png");
    }

    if(!mThreeStars.loadFromFile("res/img/victory/3stars.png")) {
        throw std::runtime_error("Could not load res/img/victory/3stars.png");
    }

    if(!mMedal.loadFromFile("res/img/victory/medal.png")) {
        throw std::runtime_error("Could not load res/img/victory/medal.png");
    }

    if(!mMainMenuMusic.openFromFile("res/audio/main.ogg")){
        throw std::runtime_error("Could not load res/audio/main.ogg");
    };

    if(!mGameSceneMusic.openFromFile("res/audio/game1.ogg")){
        throw std::runtime_error("Could not load res/audio/game1.ogg");
    }

    if(!mVictoryMusic.openFromFile("res/audio/victory.ogg")){
        throw std::runtime_error("Could not load res/audio/victory.ogg");
    }

    mGameSettings.setBoardSize(5, 5);
    mGameSettings.setNumberOfShips(5);

    registerScenes();
    mSceneStack.pushScene(Scene::ID::MainMenu);

    mFpsCounter.setFont(mFont);
    mFpsCounter.setCharacterSize(10);
    mFpsCounter.setString("INIT");
    mFpsCounter.setPosition(0, 0);
    mFpsCounter.setFillColor(sf::Color::Green);
}

void Engine::start() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();

        input();
        update(dt);
        draw();

        if (mSceneStack.isEmpty()) {
            mWindow.close();
        }
    }
}

void Engine::registerScenes() {
    mSceneStack.registerScene<MainMenuScene>(Scene::ID::MainMenu);
    mSceneStack.registerScene<GameScene>(Scene::ID::Game);
    mSceneStack.registerScene<SettingsScene>(Scene::ID::Settings);
    mSceneStack.registerScene<PauseScene>(Scene::ID::Pause);
}

void Engine::input() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mSceneStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            mSceneStack.clearScenes();
            mWindow.close();
        }
    }

    // realtime handling
    // if (windowFocus) {

    // }
}

void Engine::update(sf::Time deltaTime) {
    mSceneStack.update(deltaTime);

    mFpsTime += deltaTime;
    if (mFpsTime.asSeconds() > 1) {
        mFpsCounter.setString(std::to_string(1 / deltaTime.asSeconds()));
        mFpsTime = sf::Time::Zero;
    }
}

void Engine::draw() {
    mWindow.clear();

    mSceneStack.draw();

    mWindow.draw(mFpsCounter);

    mWindow.display();
}