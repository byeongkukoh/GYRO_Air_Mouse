# Gyro Air Mouse 🎯

MPU6050 자이로센서 기반으로 **STM32F103RB** 보드드와 **Windows 데스크탑 애플리케이션**을 이용해 구현한 **유선 에어마우스 프로젝트**입니다.  
센서 기울기에 따라 마우스 커서가 이동하며, 버튼 입력을 통해 좌/우 클릭 및 DPI 감도 변경이 가능합니다.

---

## 📦 프로젝트 구조
```text

GYRO_AIR_MOUSE/  
├── firmware/       # STM32 펌웨어 프로젝트 (STM32CubeIDE)  
├── desktop-app/    # Windows용 C++ 마우스 제어 프로그램  
├── docs/           # 기술 문서 및 배선도  
└── README.md       # 전체 프로젝트 소개 (이 문서)  

```

---

## 🎮 시스템 개요

| 구성 요소 | 설명 |
|-----------|------|
| MPU6050   | 3축 자이로/가속도 센서 (I2C 기반) |
| STM32F103RB     | 센서값 읽기 + 버튼 입력 감지 + UART 통신 |
| PC 앱     | 시리얼 데이터 수신 후 Windows 마우스 커서 이동 제어 |

> 버튼 입력에 따라 마우스 클릭 명령도 전송됩니다.

---

## 🔧 하드웨어 사양

| 항목       | 모델                    |
|------------|-------------------------|
| MCU        | STM32F103RB             |
| 센서       | MPU6050 (I2C 통신)      |
| 인터페이스 | USB-UART (115200 baud)  |
| 버튼       | GPIO 연결 (3개: 좌/우/DPI) |

> [📷 MPU6050 연결도 보기](docs/mpu6050-wiring.png) *(이미지 별도 첨부 필요)*

---

## 🧩 주요 기능

- 자이로 기반 마우스 커서 이동
- 좌클릭 / 우클릭 / DPI 감도 변경 버튼
- 감도 단계별 전환 (`1`, `4`, `8`, `12` 배율)
- UART 통신 기반 커맨드 전송
- C++ Windows API (`SetCursorPos`, `mouse_event`)로 커서/클릭 제어

---

## 📡 시리얼 통신 프로토콜

| 송신 형식       | 의미                   |
|----------------|------------------------|
| `CLICK:L`      | 좌클릭 실행            |
| `CLICK:R`      | 우클릭 실행            |
| `CLICK:D`      | DPI 단계 변경          |
| `ax, ay, az`   | 센서 측정값 (정수값)   |

---

## 🚀 사용 방법

### ▶ STM32 펌웨어 업로드

1. STM32CubeIDE로 `firmware/` 폴더 열기
2. `.ioc` 파일로 자동 구성 확인
3. 빌드 후 보드에 업로드
4. UART(USART2) → USB 연결

### ▶ Windows 데스크탑 앱 실행

1. `desktop-app/` 폴더 진입
2. `main.cpp`, `serial.c/h` 확인
3. Visual Studio로 빌드 또는 g++로 컴파일  
   *(예: `g++ main.cpp serial.c -lsetupapi -o air_mouse.exe`)*  
4. 보드의 COM 포트 번호 확인 후 `COMx`로 코드 수정

---

## 📁 참고 문서

- [`docs/system-overview.md`](docs/system-overview.md): 전체 동작 흐름도
- [`docs/mpu6050-wiring.png`](docs/mpu6050-wiring.png): 배선도
- [`desktop-app/README.md`](desktop-app/README.md): C++ 앱 설명
- [`firmware/README.md`](firmware/README.md): STM32 펌웨어 설명

---

## ⚠️ 주의 사항

- **UART 속도는 반드시 115200 bps로 설정**해야 합니다.
- 센서 초기화 시 `PWR_MGMT_1 = 0x00` 설정 필요
- 버튼은 풀업 회로를 통해 눌렸을 때 LOW를 출력해야 합니다.

---

> Made with 💡 & ⚙️ by [DevKuk](https://github.com/byeongkukoh)

