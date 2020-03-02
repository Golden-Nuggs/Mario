#pragma once

#include "Powerup.h"

class Coin : public Powerup
{
public:
	Coin();
	virtual void update(float deltaSeconds) override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	
private:
	float startY;
};