#pragma once

#include <SFML/Graphics.hpp>

class ViewTools
{
public:
	static sf::View getLetterBoxView(sf::View view, int windowWidth, int windowHeight);
	static float clamp(float value, float min, float max);
};