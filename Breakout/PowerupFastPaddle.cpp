#include "PowerupFastPaddle.h"
#include <iostream>
PowerupFastPaddle::PowerupFastPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball) : 
	PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(paddleEffectsColour);
}

PowerupFastPaddle::~PowerupFastPaddle()
{
}

std::pair<POWERUPS, float> PowerupFastPaddle::applyEffect()
{
	std::cout << "apply effect speed" << std::endl;
	_paddle->setSpeed(5, 5);
	return { fastPaddle, 5.0f };
}
