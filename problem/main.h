#ifndef MAIN_H
#define MAIN_H
#include "api.h"

#define TASK_MS (1000)
#define HB_MS (500)
#define RENDER_MS (100)
#define WIDTH (40)
#define RENDER_ENABLED (true)

extern bool reporting[BOARD_COUNT];
extern bool heartbeats[BOARD_COUNT];
extern int alerts[BOARD_COUNT];
extern bool alive;

#endif