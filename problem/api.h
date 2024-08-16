#ifndef API_H
#define API_H

#include <stdbool.h>

// an enum to define common indicies to the front and rear sensor modules
typedef enum {
    FRONT,
    REAR,
    BOARD_COUNT
} Board;

// get the heartbeat signal of a given board
bool heartbeats_get(Board board);

// set the heartbeat signal of a given board
void heartbeats_set(Board board, bool status);

// send out an alert that a given heartbeat is missing from a board
void alert_missing_heartbeat(Board board);

// shutdown the car
void shutdown();

#endif