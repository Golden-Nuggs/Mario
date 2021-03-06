#include "Constants.h"

const float Constants::WINDOW_ASPECT_RATIO = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

const std::string Constants::PLAYER_SPRITE_SHEET_FILEPATH = "Textures/mario-small.png";
const float Constants::WALK_FORCE = 2.0f;
const float Constants::JUMP_FORCE = -148000.f;
const float Constants::JUMP_BOOST_FORCE = Constants::JUMP_FORCE * 0.1f;
const float Constants::JUMP_BOOST_TIMER = 0.35f;

const float Constants::TIME_STEP = 1.f / 10.f;
const float Constants::GRAVITY_X = 0.f;
const float Constants::GRAVITY_Y = 9.81f;

const float Constants::BASE_ANIM_FRAME_DELAY = 1 / 10.f;

const std::string Constants::PLAYER_TOP_SENSOR_FIXTUREDATA_NAME = "player_top_sensor";
const std::string Constants::PLAYER_MAIN_FIXTURE_FIXTUREDATA_NAME = "player_main_fixture";
const std::string Constants::BLOCK_FIXTUREDATA_NAME = "block";
const float Constants::BLOCK_MOVEMENT_AMOUNT = 4.f;
const float Constants::BLOCK_MOVEMENT_SPEED = 4 / 2.f;
const float Constants::POWERUP_BASE_MOVE_SPEED = 32.f;
const std::string Constants::TILED_PROPERTIES_BLOCK_NUMCOIN = "numCoin";

const std::string Constants::OBJECT_LAYER_NAME_BLOCKS_Q = "blocks_?";
const std::string Constants::OBJECT_LAYER_NAME_BLOCKS_BRICK = "blocks_brick";


