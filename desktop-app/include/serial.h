#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>  // Windows API 함수 사용 (HANDLE 등)
#include <stdbool.h>  // bool 타입 사용을 위한 헤더

#ifdef __cplusplus
extern "C" {
#endif

    // 시리얼 포트 핸들 구조체
    typedef struct {
        HANDLE hSerial;   // Windows의 시리얼 포트 핸들
        bool isOpen;      // 포트가 열렸는지 여부
    } SerialPort;

    /**
     * 시리얼 포트를 엽니다.
     *
     * @param port      SerialPort 구조체 포인터
     * @param portName  포트 이름 (예: "COM3")
     * @param baudRate  보레이트 (예: 9600, 115200)
     * @return          true: 성공, false: 실패
     */
    bool serial_open(SerialPort* port, const char* portName, int baudRate);

    /**
     * 열린 시리얼 포트를 닫습니다.
     *
     * @param port  SerialPort 구조체 포인터
     */
    void serial_close(SerialPort* port);

    /**
     * 데이터를 시리얼 포트로 전송합니다.
     *
     * @param port   SerialPort 구조체 포인터
     * @param data   전송할 데이터 (바이트 배열)
     * @param length 전송할 데이터 길이
     * @return       true: 성공, false: 실패
     */
    bool serial_write(SerialPort* port, const char* data, int length);

    /**
     * 시리얼 포트에서 데이터를 읽습니다 (blocking).
     *
     * @param port   SerialPort 구조체 포인터
     * @param buffer 수신 데이터를 저장할 버퍼
     * @param length 읽을 바이트 수
     * @return       실제 읽은 바이트 수 (오류 시 -1 또는 0 가능)
     */
    int serial_read(SerialPort* port, char* buffer, int length);

    /**
     * 시리얼 포트에서 한 줄을 읽습니다 (개행 문자까지).
     *
     * @param port       SerialPort 구조체 포인터
     * @param buffer     읽은 문자열 저장 버퍼
     * @param maxLength  버퍼 최대 크기
     * @return           실제 읽은 길이 (null 제외), 오류 시 -1
     */
    int serial_readline(SerialPort* port, char* buffer, int maxLength);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_H
