#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{

    if ( position.x > 0)
    {
        _sprite.move(sf::Vector2f(-dt * _speed, 0));
    }
}

void Paddle::moveRight(float dt)
{

    if (position.x < _window->getSize().x - _width)
    {
      _sprite.move(sf::Vector2f(dt * _speed, 0));
    }
    
}

void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
      
        setWidth(1.0f, 0.0f); // Reset to default width after duration
        
    }

    if (_timeAtNewSpeed > 0)
    {
        _timeAtNewSpeed -= dt;
    }
    else
    {
        if (_speed != PADDLE_SPEED)
        {
         setSpeed(1, 0);
        }
    }

    //std::cout << _speed << std::endl;
    position = _sprite.getPosition();
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}

void Paddle::setSpeed(float coeff, float duration)
{
    _timeAtNewSpeed = duration;
    _speed = coeff * PADDLE_SPEED;
    std::cout << _speed;
}
sf::Vector2f Paddle::getPosition()
{
    return _sprite.getPosition();
}

float Paddle::getWidth()
{
    return _width;
}

float Paddle::getSpeed()
{
    return _speed;
}

