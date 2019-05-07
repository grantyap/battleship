#include <SFML/Graphics.hpp>
#include <unordered_map>

#ifndef BUTTON_H
#define BUTTON_H

class Button : public sf::Drawable, public sf::Transformable {
    const float buttonReleaseTime = 0.3f;

    sf::RectangleShape buttonRect;
    sf::Text buttonText;
    sf::FloatRect buttonTextBounds;
    static sf::Vector2i lastMousePos;

   public:
    sf::Time timeSinceClick;

    enum class State { Default, Hovered, Pressed, Released };

    void create(const float left, const float top, const sf::Vector2f& size,
                const std::string& text, const sf::Font& font);
    void create(const float left, const float top, const float width,
                const float height, const std::string& text,
                const sf::Font& font);

    Button();

    Button(const float left, const float top, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font);
    Button(const float left, const float top, const float width,
           const float height, const std::string& text, const sf::Font& font);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition();

    void setText(std::string text);
    const std::string getText();

    void setCharacterSize(unsigned int size);
    unsigned int getCharacterSize();

    void setFillColor(const sf::Color& color);
    const sf::Color& getFillColor();

    void setTextColor(const sf::Color& color);
    const sf::Color& getTextColor();

    sf::FloatRect getGlobalBounds();

    void setState(const State& state);
    const State getState();
    void setStateColor(const State state, const sf::Color& color);
    const sf::Color& getStateColor(const State state);

    void resetTimeSinceClick();

    void update(sf::Time deltaTime);

    void handleInput(sf::Event e);

   private:
    State currentState;
    std::unordered_map<State, sf::Color> stateColors;

    void centerText();
};

#endif