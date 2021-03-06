#ifndef SCENE_H
#define SCENE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

class SceneStack;  // forward declaration, solves circular dependency

class Scene {
   public:
    struct Context {
        Context(sf::RenderWindow& window, sf::Font& font,
                sf::Font& sevenSegment, GameSettings& gameSettings,
                sf::Texture& background, sf::Texture& gameBackground,
                sf::Texture& greenLed, sf::Texture& redLed,
                sf::Texture& yellowLed, sf::Texture& grille, sf::Texture& ship,
                sf::Texture& hit, sf::Texture& miss, sf::SoundBuffer& confirm,
                sf::SoundBuffer& explode, sf::SoundBuffer& splash,
                sf::Music& mainMenuMusic, sf::Music& gameSceneMusic,
                sf::Music& victoryMusic, sf::Texture& threeStars,
                sf::Texture& medal);
        sf::RenderWindow& window;
        sf::Font& font;
        sf::Font& sevenSegment;
        GameSettings& gameSettings;
        sf::Texture& background;
        sf::Texture& gameBackground;
        sf::Texture& greenLed;
        sf::Texture& redLed;
        sf::Texture& yellowLed;
        sf::Texture& grille;
        sf::Texture& ship;
        sf::Texture& hit;
        sf::Texture& miss;
        sf::Texture& threeStars;
        sf::Texture& medal;
        sf::SoundBuffer& confirm;
        sf::SoundBuffer& explode;
        sf::SoundBuffer& splash;
        sf::Music& mainMenuMusic;
        sf::Music& gameSceneMusic;
        sf::Music& victoryMusic;
    };

    enum class ID { None, MainMenu, Game, Settings, Pause, Credits };

   public:
    Scene(SceneStack& stack, Context& context);
    virtual ~Scene() {}
    virtual bool input(const sf::Event& e) = 0;
    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;

    void requestScenePush(Scene::ID sceneID);
    void requestScenePop();
    void requestSceneClear();

    Context& getContext();

   private:
    SceneStack& mStack;
    Context& mContext;
};

#endif