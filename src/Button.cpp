#include "Button.h"

using std::cout;


void Button::create(const float left, const float top, const sf::Vector2f& size,
                    const std::string& text) {
    buttonRect.setSize(size);
    buttonRect.setFillColor(sf::Color::Red);

    if (!font.loadFromFile(FONT_PATH)) {
        cout << FONT_FAILURE;
    }
    buttonText.setFont(font);
    buttonText.setString(text);
    setPosition(left, top);

    sf::Time timeSinceClick = sf::Time::Zero;
    lastMousePos = sf::Vector2i(0, 0);
    stateColors = {{Default, sf::Color::Red},
                   {Hovered, sf::Color::Blue},
                   {Pressed, sf::Color::Cyan},
                   {Released, sf::Color::Green}};
}

void Button::create(const float left, const float top, const float width,
                    const float height, const std::string& text) {
    create(left, top, sf::Vector2f(width, height), text);
}

Button::Button() { create(0, 0, 100, 100, std::string("default")); }
Button::Button(const float left, const float top, const sf::Vector2f& size,
               const std::string& text) {
    create(left, top, size, text);
}
Button::Button(const float left, const float top, const float width,
               const float height, const std::string& text) {
    create(left, top, sf::Vector2f(width, height), text);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(buttonRect, states);
    target.draw(buttonText, states);
}

void Button::setPosition(const float x, const float y) {
    buttonRect.setPosition(x, y);
    centerText();
}
void Button::setPosition(const sf::Vector2f& pos) { setPosition(pos.x, pos.y); }
const sf::Vector2f& Button::getPosition() { return buttonRect.getPosition(); }

void Button::setText(std::string text) {
    buttonText.setString(text);
    centerText();
}
const std::string Button::getText() { return buttonText.getString(); }

void Button::setCharacterSize(unsigned int size) {
    buttonText.setCharacterSize(size);
    centerText();
}
unsigned int Button::getCharacterSize() {
    return buttonText.getCharacterSize();
}

void Button::setFillColor(const sf::Color& color) {
    buttonRect.setFillColor(color);
}
const sf::Color& Button::getFillColor() { return buttonRect.getFillColor(); }

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}
const sf::Color& Button::getTextColor() { return buttonText.getFillColor(); }

sf::FloatRect Button::getGlobalBounds() { return buttonRect.getGlobalBounds(); }

void Button::setState(const State state) { currentState = state; }
const Button::State Button::getState() { return currentState; }
void Button::setStateColor(const State state, const sf::Color& color) {
    stateColors[state] = color;
}
const sf::Color& Button::getStateColor(const State state) {
    return stateColors[state];
}

void Button::resetTimeSinceClick() { timeSinceClick = sf::Time::Zero; }

void Button::update(sf::Time deltaTime) {
    timeSinceClick += deltaTime;

    if (currentState == State::Default) {
        buttonRect.setFillColor(stateColors[State::Default]);
    } else if (currentState == State::Hovered) {
        buttonRect.setFillColor(stateColors[State::Hovered]);
    } else if (currentState == State::Pressed) {
        buttonRect.setFillColor(stateColors[State::Pressed]);
    } else if (currentState == State::Released) {
        if (timeSinceClick.asSeconds() > buttonReleaseTime) {
            if (getGlobalBounds().contains(lastMousePos.x, lastMousePos.y)) {
                setState(State::Hovered);
            } else {
                setState(State::Default);
            }
        }
        buttonRect.setFillColor(stateColors[State::Released]);
    }
}

void Button::handleInput(sf::Event& e) {
    switch (e.type) {
        case sf::Event::MouseMoved: {
            lastMousePos = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
            if (currentState != State::Pressed &&
                currentState != State::Released) {
                if (getGlobalBounds().contains(lastMousePos.x, lastMousePos.y)) {
                    setState(State::Hovered);
                } else {
                    setState(State::Default);
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed: {
            lastMousePos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
            if (e.mouseButton.button == sf::Mouse::Left &&
                getGlobalBounds().contains(lastMousePos.x, lastMousePos.y)) {
                setState(State::Pressed);
                resetTimeSinceClick();
            }
            break;
        }
        case sf::Event::MouseButtonReleased: {
            lastMousePos = sf::Vector2i(e.mouseButton.x, e.mouseButton.y);
            if (e.mouseButton.button == sf::Mouse::Left &&
                getGlobalBounds().contains(lastMousePos.x, lastMousePos.y)) {
                setState(State::Released);
            } else {
                setState(State::Default);
            }
            break;
        }
        default:
            break;
    }
}

void Button::centerText() {
    buttonTextBounds = buttonText.getLocalBounds();
    sf::Vector2f rectPos = buttonRect.getPosition();
    sf::FloatRect rectBounds = buttonRect.getLocalBounds();
    buttonText.setOrigin(buttonTextBounds.left + buttonTextBounds.width / 2,
                         buttonTextBounds.top + buttonTextBounds.height / 2);
    buttonText.setPosition(rectPos.x + rectBounds.width / 2,
                           rectPos.y + rectBounds.height / 2);
}