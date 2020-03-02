#include "NoobEngine.h"
#include "Constants.h"
#include "ViewTools.h"
#include <iostream>

void NoobEngine::start()
{
    CreateWindow();

    gravity = b2Vec2(Constants::GRAVITY_X, Constants::GRAVITY_Y); 
    world = new b2World(gravity);
    game.start(world);
    LevelManager* levelManager = LevelManager::getInstance();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                levelManager->getGameView() = ViewTools::getLetterBoxView(levelManager->getGameView(), event.size.width, event.size.height);
            }
        }

        game.update();
        world->Step(Constants::TIME_STEP, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);
        game.draw(window);
    }
}

void NoobEngine::CreateWindow()
{
    window.create(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "PLAYER!", sf::Style::Default); // TODO: Hardcoded screen res. and window name
    //Window.create(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), "PLAYER!", sf::Style::Fullscreen); 
}
