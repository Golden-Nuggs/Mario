#pragma once

#include "Powerup.h"

class Coin : public Powerup
{
public:
	Coin();
	void update(float deltaSeconds) override;
	void draw(sf::RenderWindow& window) override;

protected:

};