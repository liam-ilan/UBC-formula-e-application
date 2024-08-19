#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h>

#include "main.h"
#include "api.h"
#include "solution.h"

// stores original terminal settings
struct termios orig_termios;

// stores terminal settings for while the program is running (echo off)
struct termios run_termios;

void exitEvents() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    // \e[?1000l disables mouse events
    printf("\e[?1000l\e[?25h");
}

void disableRaw() {
    // reset
    printf("\e[?1000l");
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &run_termios);
}

void initEvents() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    run_termios = orig_termios;
    run_termios.c_lflag &= ~(ECHO);

    atexit(exitEvents);
}

void enableRaw() {

    // get standard settings
    struct termios raw = orig_termios;

    // set flags
    raw.c_iflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_oflag &= ~(OPOST);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    // write settings back into terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  
    // flush stdout
    fflush(stdout);
}

// reads a single char from stdin, assuming that raw is enabled
char readChar() {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    // printf("%c\r\n", c);
    // handle exit
    if (iscntrl(c) && (c == 26 || c == 3)) exit(0);
    return c;
}

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

    if (reporting[BATTERY]) {
        printf("Battery Management System Heartbeat:");
        print_check();
        printf("\n");
    } else {
        printf("Battery Management System Heartbeat:");
        print_x();
        printf("\n");
    }

    for (int i = 0; i < WIDTH - car_x; i += 1) printf(" ");
    printf("🏎️\n");

    printf("Missing Front Sensor Heartbeat Monitor Alerts: %d\n", alerts[FRONT]);
    printf("Missing Rear Sensor Heartbeat Monitor Alerts: %d\n", alerts[REAR]);
    printf("Missing Battery Management System Heartbeat Monitor Alerts: %d\n", alerts[BATTERY]);
    printf("\e[1mPress f to toggle the Front Sensor Module heartbeat.\e[0m\n");
    printf("\e[1mPress r to toggle the Rear Sensor Module Heartbeat.\e[0m\n");
    printf("\e[1mPress b to toggle the Battery Management System heartbeat.\e[0m\n");
}

int main() {
    initEvents();

    int car_x = 0;
    uint64_t time_ms = 0;
    uint64_t time_ms_since_last_hb = 0;
    uint64_t time_ms_since_last_task = 0;
    uint64_t time_ms_since_last_render = 0;

    for (;;) {
        // ReadChar blocks for a maximum of 100ms.
        enableRaw();
        char c = readChar();
        disableRaw();

        if (c == 'f') {
            reporting[FRONT] = !reporting[FRONT];
        } else if (c == 'r') {
            reporting[REAR] = !reporting[REAR];
        } else if (c == 'b') {
            reporting[BATTERY] = !reporting[BATTERY];
        }

        // Keep track of time.
        time_ms += 100;
        time_ms_since_last_hb += 100;
        time_ms_since_last_task += 100;
        time_ms_since_last_render += 100;
        
        if (time_ms_since_last_hb > HB_MS) {
            // Heartbeats get updated every HB_MS.
            heartbeats[FRONT] = reporting[FRONT];
            heartbeats[REAR] = reporting[REAR];
            heartbeats[BATTERY] = reporting[BATTERY];
            
            time_ms_since_last_hb = 0;
        }

        if (time_ms_since_last_task > TASK_MS) {
            alive = true;
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

