#include <stdbool.h>
#include "api.h"

bool reporting[BOARD_COUNT] = {true, true, true};
bool heartbeats[BOARD_COUNT] = {true, true, true}; 
int alerts[BOARD_COUNT] = {0, 0, 0}; 
bool alive = true;

void alert_missing_heartbeat(Board board) {
    alerts[board] += 1;
}

bool heartbeats_get(Board board) {
    return heartbeats[board];
}

void heartbeats_set(Board board, bool status) {
    heartbeats[board] = status;
}

void shutdown() {
    alive = false;
}