#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"
#include "api.h"
#include "solution.h"

void print_check() {
    printf("\U00002705");
}

void print_x() {
    printf("%s", "\U0000274C");
}

void render(int car_x) {
    system("clear");
    if (reporting[FRONT]) {
        printf("Front Sensor Module Heartbeat:");
        print_check();
        printf("\n");
    } else {
        printf("Front Sensor Module Heartbeat:");
        print_x();
        printf("\n");
    }

    if (reporting[REAR]) {
        printf("Rear Sensor Module Heartbeat:");
        print_check();
        printf("\n");
    } else {
        printf("Rear Sensor Module Heartbeat:");
        print_x();
        printf("\n");
    }

    for (int i = 0; i < WIDTH - car_x; i += 1) printf(" ");
    printf("🏎️\n");

    printf("Missing Front Sensor Heartbeat Monitor Alerts: %d\n", alerts[FRONT]);
    printf("Missing Front Sensor Heartbeat Monitor Alerts: %d\n", alerts[REAR]);
}

int main() {
    int car_x = 0;
    clock_t time_ms = 0;
    clock_t time_ms_since_last_hb = 0;
    clock_t time_ms_since_last_task = 0;
    clock_t time_ms_since_last_render = 0;

    for (;;) {
        
        // Keep track of time.
        const clock_t delta_time_ms = time_ms - clock() / CLOCKS_PER_MS;
        time_ms += delta_time_ms;
        time_ms_since_last_hb += delta_time_ms;
        time_ms_since_last_task += delta_time_ms;
        time_ms_since_last_render += delta_time_ms;
        
        if (time_ms_since_last_hb > HB_MS) {
            // Heartbeats get updated every HB_MS.
            heartbeats[FRONT] = reporting[FRONT];
            heartbeats[REAR] = reporting[REAR];
            
            time_ms_since_last_hb = 0;
        }

        if (time_ms_since_last_task > TASK_MS) {
            // Task gets run every TASK_MS.
            task_1Hz();

            time_ms_since_last_task = 0;
        }

        if (time_ms_since_last_render > RENDER_MS) {
            if (RENDER_ENABLED) render(car_x);

            if (alive) {
                car_x += 1;
                car_x %= WIDTH;
            }

            time_ms_since_last_render = 0;
        }
    }
}

