#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
   
 
    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + powerUpFreq && rand()%spawnChance == 0)      
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        chosenInput = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        chosenInput = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        chosenInput = 2;
    }

    switch (chosenInput)
    {
    case 0 :
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            _paddle->moveRight(dt);
            canMove = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _paddle->moveLeft(dt);
            canMove = false;
        }
        break;

    case 1:
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            _paddle->moveRight(dt);
            canMove = false;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _paddle->moveLeft(dt);
            canMove = false;
        }
        break;
    case 2:

        if (sf::Mouse::getPosition(*_window).x - _paddle->getWidth() / 2 > _paddle->getPosition().x && canMove)
        {

            _paddle->moveRight(dt);
        }
        else if (sf::Mouse::getPosition(*_window).x - _paddle->getWidth() / 2 < _paddle->getPosition().x && canMove)
        {
            _paddle->moveLeft(dt);

        }
        break;
    }


    if (cameraShakeDuration >0)
    {
       cameraShakeDuration -= dt;
       timeSinceDeath += dt;
       cameraShake(0.05,5,5);
    }
    else
    {
        _window->setView(_window->getDefaultView());
    }
 
    
    canMove = true;
    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    lifeLost = true;
    cameraShakeDuration = 0.5;
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::cameraShake(float frequency, float offsetX, float offsetY)
{
    if (timeSinceDeath > frequency)
    {
    direction = -direction;
    sf::View viewWindow = _window->getView();
    viewWindow.move(offsetX*direction, offsetY * direction);
    _window->setView(viewWindow);
    timeSinceDeath = 0;
    }
   
    
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
