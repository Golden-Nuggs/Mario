#include "Camera.h"
#include "Constants.h"
#include "ViewTools.h"
#include <iostream>

void Camera::initView(unsigned int levelWidth, unsigned int levelHeight)
{
	gameView.setSize(Constants::VIEW_WIDTH, Constants::VIEW_HEIGHT);
	float gameViewExtentsX = gameView.getSize().x / 2.f;
	float gameViewExtentsY = gameView.getSize().y / 2.f;
	gameView.setCenter(gameViewExtentsX, gameView.getSize().y / 2.f);
	gameView = ViewTools::getLetterBoxView(gameView, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);

	minX = gameViewExtentsX;
	maxX = levelWidth - gameViewExtentsX;
	minY = gameViewExtentsY;
	maxY = levelHeight - gameViewExtentsY;

}

void Camera::followTarget(sf::Vector2f target)
{
	float pos_x = target.x;
	float pos_y = target.y;
	pos_x = ViewTools::clamp(pos_x, minX, maxX);
	pos_y = ViewTools::clamp(pos_y, minY, maxY);
	gameView.setCenter(pos_x, pos_y);
}

sf::View& Camera::getGameView()
{
	return gameView;
}
