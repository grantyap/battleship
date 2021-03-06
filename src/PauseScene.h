#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "Button.h"
#include "Scene.h"

class PauseScene : public Scene {
   public:
    PauseScene(SceneStack& stack, Context& context);
    ~PauseScene();
    bool input(const sf::Event& e);
    void draw();
    bool update(sf::Time deltaTime);

   private:
    sf::RectangleShape mBackground;
    sf::Text mPauseText;
    Button mContinueButton;
    Button mExitButton;

    sf::Sprite mHit;
    sf::Text mHitText;
    sf::Sprite mMiss;
    sf::Text mMissText;
    sf::Text mLegendText;
};

#endif