#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Paddle
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);
    sf::Vector2f getPosition();
    float getWidth();
    float getSpeed();
    void setSpeed(float coeff, float duration);


private:

    sf::Vector2f position;
    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    float _speed = PADDLE_SPEED;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
    float _timeAtNewSpeed = 0.0f;
};
