#pragma once

#include <iostream>

class Constants
{
public:
    // Video
    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;
    static const int VIEW_WIDTH = 254;
    static const int VIEW_HEIGHT = 240;
    static const int PPU = 16;
    static const float WINDOW_ASPECT_RATIO;

    // Physics
    static const float TIME_STEP;
    static const signed int VELOCITY_ITERATIONS = 6;
    static const signed int POSITION_ITERATIONS = 5;
    static const float GRAVITY_X;
    static const float GRAVITY_Y;

    // Level
    static const unsigned int BLOCK_BRICK_ID = 1;
    static const unsigned int BLOCK_Q_ID = 24;

    // Player
    static const int STARTING_LIVES = 5;
    static const int MAX_WALK_SPEED = 7;
    static const int MAX_SPRINT_SPEED = 15;
    static const float WALK_FORCE;
    static const float JUMP_FORCE;
    static const float JUMP_BOOST_FORCE;
    static const float JUMP_BOOST_TIMER;
    static const int SPRITE_WIDTH = 16;
    static const int SPRITE_HEIGHT = 16;
    static const int MARIO_SMALL_IDLE_ATLAS_X = 0;
    static const int MARIO_SMALL_RUN_ATLAS_X = 1;
    static const int MARIO_SMALL_SKID_ATLAS_X = 4;
    static const int MARIO_SMALL_JUMP_ATLAS_X = 5;
    static const int MARIO_SMALL_FLAG_POLE_1_ATLAS_X = 6;
    static const int MARIO_SMALL_FLAG_POLE_2_ATLAS_X = 7;
    static const int MARIO_SMALL_SWIM_ATLAS_X = 8;
    static const int MARIO_SMALL_DEAD_ATLAS_X = 13;
    static const int MARIO_SMALL_WALK_FRAME_COUNT = 3;
    static const int MARIO_SMALL_SWIM_FRAME_COUNT = 5;
    static const float BASE_ANIM_FRAME_DELAY;

    // Fixture Names
    static const std::string MARIO_TOP_SENSOR_FIXTUREDATA_NAME;
    static const std::string MARIO_MAIN_FIXTURE_FIXTUREDATA_NAME;
    static const std::string BLOCK_FIXTUREDATA_NAME;

    // Block
    static const float BLOCK_MOVEMENT_SPEED;


};

