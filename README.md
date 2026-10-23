# 아두이노 실습 2

아두이노 우노로 LED, 가변 저항, 소리 센서, 버튼, 7세그먼트를 다뤄 본 실습 코드 모음이에요.
폴더 하나가 스케치 하나이고, 폴더 이름과 `.ino` 파일 이름이 같아요.

## 스케치 목록

| 폴더 | 하는 일 | 연결 |
|---|---|---|
| [blink](blink/blink.ino) | 보드의 L LED를 1초 간격으로 깜빡여요 | 13번 (보드에 붙은 LED) |
| [pot_led](pot_led/pot_led.ino) | 가변 저항을 돌리면 LED 밝기가 바뀌어요 | LED → 9번, 가변 저항 → A0 |
| [sound_led](sound_led/sound_led.ino) | 소리가 크면 LED가 켜져요 | LED → 9번, 소리 센서 → A0 |
| [sound_toggle](sound_toggle/sound_toggle.ino) | 큰 소리가 날 때마다 LED가 켜짐/꺼짐을 번갈아 바꿔요 | LED → 9번, 소리 센서 → A0 |
| [sound_red_green](sound_red_green/sound_red_green.ino) | 조용하면 빨간 LED, 소리가 들리면 초록 LED가 켜져요 | 빨간 → 9번, 초록 → 10번, 소리 센서 → A0 |
| [button_counter](button_counter/button_counter.ino) | 버튼 누른 횟수를 7세그먼트에 표시해요. 빠르게 두 번 누르면 0으로 초기화 | 세그먼트 A~G → D2~D8, 버튼 → D10, LED → D11 |

LED는 모두 220Ω 저항을 거쳐 연결하고, 짧은 다리는 GND에 꽂아요.

## 알아 둔 것

- **밝기 조절은 `~` 표시가 있는 핀에서만 돼요.** 13번은 켜기/끄기만 가능해서 `pot_led`는 9번 핀을 써요.
- **소리 크기는 한 번만 읽지 않아요.** 소리 센서 값은 소리가 나면 위아래로 흔들리기 때문에, 50ms 동안 여러 번 읽어서 가장 큰 값과 가장 작은 값의 차이를 소리 크기로 써요.
- **기준값(`THRESHOLD`)은 센서마다 달라요.** 시리얼 모니터(9600)로 값을 보면서 맞추면 돼요.
- **버튼은 `INPUT_PULLUP`으로 읽어요.** 누르면 LOW, 떼면 HIGH예요. 버튼 접점이 떨리는 건 50ms 디바운싱으로 걸러요.

## 실습 3 · 7세그먼트 + 버튼 + LED

![5161AS 배선도](button_counter/5161AS_wiring.png)

배선하면서 헷갈렸던 점(공통 캐소드, COM 다리, 다리 번호와 핀 번호 구분 등)은 [실습3_어려웠던점.md](button_counter/실습3_어려웠던점.md)에 정리했어요.

## 보드에 업로드하는 방법

[arduino-cli](https://arduino.github.io/arduino-cli/)로 컴파일하고 업로드해요. 포트(`COM3`)는 `arduino-cli board list`로 확인하세요.

```
arduino-cli compile --fqbn arduino:avr:uno --upload -p COM3 button_counter
```

시리얼 출력 보기:

```
arduino-cli monitor -p COM3 -c baudrate=9600
```
