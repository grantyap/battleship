#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "SceneStack.h"
#include "Button.h"

class MainMenuScene : public Scene {
   public:
    MainMenuScene(SceneStack& stack, Scene::Context& context);
    ~MainMenuScene();
    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

   private:
    sf::Font mFont;
    sf::RenderWindow& mWindow;
    sf::Vector2u mWindowSize;
    sf::Sprite mSpriteBG;

    sf::Text title;
    Button playButton, exitButton;
};

#endif