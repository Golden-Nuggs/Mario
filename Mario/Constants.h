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
    static const unsigned int SOURCETILESINDEX_BLOCK_BRICK = 1;
    static const unsigned int SOURCETILESINDEX_BLOCK_Q = 24;
    static const unsigned int SOURCETILESINDEX_BLOCK_USED = 27;
    static const unsigned int SOURCETILESINDEX_COIN = 57;
    static const std::string TILED_PROPERTIES_BLOCK_NUMCOIN;
    static const std::string OBJECT_LAYER_NAME_BLOCKS_Q;
    static const std::string OBJECT_LAYER_NAME_BLOCKS_BRICK;

    // Player
    static const std::string PLAYER_SPRITE_SHEET_FILEPATH;
    static const int STARTING_LIVES = 5;
    static const int MAX_WALK_SPEED = 7;
    static const int MAX_SPRINT_SPEED = 15;
    static const float WALK_FORCE;
    static const float JUMP_FORCE;
    static const float JUMP_BOOST_FORCE;
    static const float JUMP_BOOST_TIMER;
    static const int TEXTURE_WIDTH = 16;
    static const int TEXTURE_HEIGHT = 16;
    static const int PLAYER_SMALL_IDLE_ATLAS_X = 0;
    static const int PLAYER_SMALL_RUN_ATLAS_X = 1;
    static const int PLAYER_SMALL_SKID_ATLAS_X = 4;
    static const int PLAYER_SMALL_JUMP_ATLAS_X = 5;
    static const int PLAYER_SMALL_FLAG_POLE_1_ATLAS_X = 6;
    static const int PLAYER_SMALL_FLAG_POLE_2_ATLAS_X = 7;
    static const int PLAYER_SMALL_SWIM_ATLAS_X = 8;
    static const int PLAYER_SMALL_DEAD_ATLAS_X = 13;
    static const int PLAYER_SMALL_WALK_FRAME_COUNT = 3;
    static const int PLAYER_SMALL_SWIM_FRAME_COUNT = 5;
    static const float BASE_ANIM_FRAME_DELAY;

    // Fixture Names
    static const std::string PLAYER_TOP_SENSOR_FIXTUREDATA_NAME;
    static const std::string PLAYER_MAIN_FIXTURE_FIXTUREDATA_NAME;
    static const std::string BLOCK_FIXTUREDATA_NAME;

    // Block
    static const float BLOCK_MOVEMENT_AMOUNT;
    static const float BLOCK_MOVEMENT_SPEED;

    // Powerup
    static const float POWERUP_BASE_MOVE_SPEED;
    static const int COIN_MAX_Y = 3 * PPU;
    static const int COIN_MOVE_SPEED = 9 * PPU;


};

