#pragma once

#include <SFML/Graphics.hpp>

class Powerup
{
public:
	Powerup();
	virtual void update(float deltaSeconds);
	virtual void draw(sf::RenderWindow& window);

	bool bGravity;
	bool bCollectable;
	sf::Vector2f moveDirection;
	float moveSpeed;


protected:
	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;

private:

};