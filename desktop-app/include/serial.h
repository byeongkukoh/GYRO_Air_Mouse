#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>  // Windows API �Լ� ��� (HANDLE ��)
#include <stdbool.h>  // bool Ÿ�� ����� ���� ���

#ifdef __cplusplus
extern "C" {
#endif

    // �ø��� ��Ʈ �ڵ� ����ü
    typedef struct {
        HANDLE hSerial;   // Windows�� �ø��� ��Ʈ �ڵ�
        bool isOpen;      // ��Ʈ�� ���ȴ��� ����
    } SerialPort;

    /**
     * �ø��� ��Ʈ�� ���ϴ�.
     *
     * @param port      SerialPort ����ü ������
     * @param portName  ��Ʈ �̸� (��: "COM3")
     * @param baudRate  ������Ʈ (��: 9600, 115200)
     * @return          true: ����, false: ����
     */
    bool serial_open(SerialPort* port, const char* portName, int baudRate);

    /**
     * ���� �ø��� ��Ʈ�� �ݽ��ϴ�.
     *
     * @param port  SerialPort ����ü ������
     */
    void serial_close(SerialPort* port);

    /**
     * �����͸� �ø��� ��Ʈ�� �����մϴ�.
     *
     * @param port   SerialPort ����ü ������
     * @param data   ������ ������ (����Ʈ �迭)
     * @param length ������ ������ ����
     * @return       true: ����, false: ����
     */
    bool serial_write(SerialPort* port, const char* data, int length);

    /**
     * �ø��� ��Ʈ���� �����͸� �н��ϴ� (blocking).
     *
     * @param port   SerialPort ����ü ������
     * @param buffer ���� �����͸� ������ ����
     * @param length ���� ����Ʈ ��
     * @return       ���� ���� ����Ʈ �� (���� �� -1 �Ǵ� 0 ����)
     */
    int serial_read(SerialPort* port, char* buffer, int length);

    /**
     * �ø��� ��Ʈ���� �� ���� �н��ϴ� (���� ���ڱ���).
     *
     * @param port       SerialPort ����ü ������
     * @param buffer     ���� ���ڿ� ���� ����
     * @param maxLength  ���� �ִ� ũ��
     * @return           ���� ���� ���� (null ����), ���� �� -1
     */
    int serial_readline(SerialPort* port, char* buffer, int maxLength);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_H
