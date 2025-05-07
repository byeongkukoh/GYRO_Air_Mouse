# Windows Air Mouse Application 🎯

이 디렉토리는 **STM32에서 전송된 센서 데이터(UART)** 를 받아서 **Windows 마우스 커서와 클릭을 제어**하는 C++ 애플리케이션을 포함합니다.

STM32 보드는 MPU6050 자이로센서로부터 측정한 가속도 값을 UART를 통해 전송하며, 이 애플리케이션은 해당 데이터를 분석하여 커서 이동, 클릭 이벤트를 발생시킵니다.

---

## 🗂️ 파일 구성

```text

desktop-app/
├── include/
│ └── serial.h              # 시리얼 통신 헤더 정의
├── src/
│ ├── main.cpp              # 메인 로직 (커서 제어, 클릭 처리)
│ └── serial.c              # 시리얼 포트 오픈/읽기/닫기 구현
└── README.md

```

---

## ✅ 주요 기능

- 시리얼 포트(COMx)로부터 센서 데이터 수신
- 가속도(ax, ay) 값을 기반으로 마우스 커서 이동
- `CLICK:L`, `CLICK:R`, `CLICK:D` 명령에 따라
  - 좌클릭 / 우클릭 / DPI 전환 수행
- DPI 감도는 4단계(`1, 4, 8, 12`) 순환

---

## ⚙️ 빌드 방법

### ▶ Visual Studio (GUI 기반)

1. `desktop-app/` 디렉토리에 Visual Studio 프로젝트 생성
2. `main.cpp`, `serial.c`, `serial.h` 포함
3. Windows API(`<Windows.h>`)가 포함된 콘솔 애플리케이션으로 설정
4. 빌드 후 실행

### ▶ g++ (CLI 기반)

```bash
g++ src/main.cpp src/serial.c -o air_mouse.exe -lsetupapi
```
- `-lsetupapi`: 시리얼 포트 열기 위한 Windows API 라이브러리
- `-static` 옵션 추가로 실행 파일을 배포용으로 만들 수 있음

---

## 🖱️ 동작 방식 요약

### STM32 보드에서 UART로 전송되는 메시지 예시:

|                   |                           |
|-------------------|---------------------------|
| `CLICK:L\r\n`            | 좌클릭                     |
| `CLICK:R\r\n`            | 우클릭                     |
| `CLICK:D\r\n`            | DPI 감도 전환              |
| `1200, -800, 4096\r\n`   | x, y, z축 가속도 값        |

### PC 애플리케이션 처리 방식:

|                   |                           |
|-------------------|---------------------------|
| 커서 이동             | `SetCursorPos(x, y)`                                   |
| 좌/우 클릭            | `mouse_event(MOUSEEVENTF_LEFT/RIGHT...)`               |
| DPI 변경              | `sensitivity_list[]` 배열로 1→4→8→12 배율 순환         |

---

## 📌 실행 전 확인 사항

- COM 포트 설정:  
    STM32가 연결된 포트(COMx)를 확인하고 코드 내 포트 문자열 수정

- 통신 속도:  
    반드시 115200 baud로 설정해야 정상 동작

- 실행 권한:  
    커서 조작 및 클릭 동작을 위해 관리자 권한 필요할 수 있음

- 문자열 종료:  
    STM32 측에서 반드시 "\r\n"으로 줄을 종료해야 함

---

> Made with ⚙️ by DevKuk (https://github.com/byeongkukoh)