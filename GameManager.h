#pragma once
#include "CoreLibs.h"

struct GameState {

    int windowWidth;    // set by reshape callback
    int windowHeight;   // set by reshape callback

    bool freeCameraMode;        // false;
    float cameraElevationAngle; // in degrees = initially 0.0f

    bool gameOver;              // false;
    bool keyMap[KEYS_COUNT];    // false

    float elapsedTime;
    float missileLaunchTime;
    float ufoMissileLaunchTime;

} gameState;

// parameters of individual objects in the scene (e.g. position, size, speed, etc.)
typedef struct Object {
    glm::vec3 position;
    glm::vec3 direction;
    float     speed;
    float     size;

    bool destroyed;

    float startTime;
    float currentTime;

} Object;

class GameManager
{
public:


};
