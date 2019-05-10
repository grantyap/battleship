#include <SFML/Graphics.hpp>

#ifndef CONTEXT_H
#define CONTEXT_H

class Context {
   public:
    Context(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font) {}
    sf::RenderWindow& getWindow() { return mWindow; }
    sf::Font& getFont() { return mFont; }

   private:
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
};

#endif