#include "serial.h"
#include <stdio.h>

bool serial_open(SerialPort* port, const char* portName, int baudRate) {
    port->hSerial = CreateFileA(portName,                // COM 포트 이름 (예: "COM3")
        GENERIC_READ | GENERIC_WRITE,
        0,                      // 공유 모드 없음
        NULL,                   // 기본 보안 속성
        OPEN_EXISTING,
        0,                      // 비동기 사용 안함
        NULL);

    if (port->hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "[ERROR] Unable to open COM port %s\n", portName);
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(port->hSerial, &dcbSerialParams)) {
        fprintf(stderr, "[ERROR] GetCommState failed\n");
        CloseHandle(port->hSerial);
        return false;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(port->hSerial, &dcbSerialParams)) {
        fprintf(stderr, "[ERROR] SetCommState failed\n");
        CloseHandle(port->hSerial);
        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    SetCommTimeouts(port->hSerial, &timeouts);

    port->isOpen = true;
    return true;
}

void serial_close(SerialPort* port) {
    if (port->isOpen) {
        CloseHandle(port->hSerial);
        port->isOpen = false;
    }
}

bool serial_write(SerialPort* port, const char* data, int length) {
    DWORD bytesWritten;
    if (!WriteFile(port->hSerial, data, length, &bytesWritten, NULL)) {
        fprintf(stderr, "[ERROR] WriteFile failed\n");
        return false;
    }
    return bytesWritten == (DWORD)length;
}

int serial_read(SerialPort* port, char* buffer, int length) {
    DWORD bytesRead;

    if (!ReadFile(port->hSerial, buffer, length, &bytesRead, NULL)) {
        fprintf(stderr, "[ERROR] ReadFile failed\n");

        return -1;
    }

    return (int)bytesRead;
}

int serial_readline(SerialPort* port, char* buffer, int maxLength) {
    int idx = 0;
    char ch;
    while (idx < maxLength - 1) {
        int result = serial_read(port, &ch, 1);
        if (result <= 0) continue;
        if (ch == '\n') break;
        buffer[idx++] = ch;
    }
    buffer[idx] = '\0';

    return idx;
}
