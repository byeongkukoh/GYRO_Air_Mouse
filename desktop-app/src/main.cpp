#include "serial.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>

void connect_mouse(SerialPort* port);
void left_click();
void right_click();

int main()
{
    SerialPort port;
    
    if (serial_open(&port, "COM6", 115200)) {
        std::cout << "[SUCCESS] Connect GYRO AIR MOUSE.\n";

        connect_mouse(&port);
    }

    serial_close(&port);

    return 0;
}

void connect_mouse(SerialPort* port) {
    char line[255];
    POINT pt;
    int ax, ay, az;

    const int sensitivity_list[4] = { 1, 4, 8, 12 };

    int sens_idx = 0;
    int sensitivity = sensitivity_list[sens_idx];
    const int threshold = 2000;

    while (true) {
        int len = serial_readline(port, line, sizeof(line));

        if (len <= 0) continue;

        //std::cout << "[수신] " << line << "\n";

        if (strncmp(line, "CLICK:L", 7) == 0) {
            left_click();
            std::cout << "[수신] " << line << "\n";
            continue;
        }

        if (strncmp(line, "CLICK:R", 7) == 0) {
            right_click();
            std::cout << "[수신] " << line << "\n";
            continue;
        }

        if (strncmp(line, "CLICK:D", 7) == 0) {
            //right_click();
            sens_idx = (sens_idx + 1) % 4;
            std::cout << "[수신] " << line << "\n";
            continue;
        }

        if (sscanf(line, "%d, %d, %d", &ax, &ay, &az)) {
            //std::cout << "[수신] " << line << "\n";

            //std::cout << ax << " " << ay << " " << az << "\n";
            
            if (abs(ax) < threshold) ax = 0;
            else {
                ax = -ax / 1000;
            }

            //ay = ay < 0 ? -5 : 5;
            if (abs(ay) < threshold) ay = 0;
            else {
                ay = ay / 1000;
            }

            if (GetCursorPos(&pt)) {
                // 화면 좌표
                // (0, 0)       (2559, 0)
                // (0, 1439)    (2559, 1439)

                //std::cout << pt.x << " " << pt.y << "\n";

                int dx = ax * sensitivity;
                int dy = ay * sensitivity;

                //std::cout << pt.x + dx << " " << pt.y + dy << "\n";

                SetCursorPos(pt.x + dx, pt.y + dy);
            }
        }

    }

    return;
}

void left_click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void right_click() {
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}