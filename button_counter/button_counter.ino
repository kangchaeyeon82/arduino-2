// 버튼 누른 횟수를 누적해서 5161AS 한 자리 세그먼트에 표시하기
// 배선: 5161AS_배선도.png 참고
//   세그먼트 A~G -> D2~D8, 버튼 -> D10 (반대쪽은 GND), LED -> D11
const int SEG_PINS[7] = {2, 3, 4, 5, 6, 7, 8}; // A, B, C, D, E, F, G 순서
const int BUTTON_PIN = 10;      // 버튼 (누르면 GND와 연결되어 LOW)
const int LED_PIN = 11;         // 버튼을 누를 때마다 잠깐 켜지는 LED
const unsigned long DEBOUNCE_MS = 50; // 버튼 떨림 무시 시간
const unsigned long LED_ON_MS = 100;  // 누를 때 LED가 켜져 있는 시간
const unsigned long DOUBLE_MS = 400;  // 이 시간 안에 두 번 누르면 초기화
const unsigned long RESET_LED_MS = 1000; // 초기화되면 LED를 1초 켜서 알려줌

// 숫자 0~9를 켤 세그먼트 (1 = 켜기), 순서: A B C D E F G
const byte DIGITS[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

unsigned long count = 0;        // 누적된 버튼 누른 횟수
int lastReading = HIGH;         // 직전에 읽은 버튼 값
int buttonState = HIGH;         // 떨림을 걸러낸 확정된 버튼 상태
unsigned long lastChange = 0;   // 버튼 값이 마지막으로 바뀐 시각
unsigned long ledOnAt = 0;      // LED를 켠 시각
unsigned long ledDuration = LED_ON_MS; // 이번에 LED를 켜 둘 시간
unsigned long lastPress = 0;    // 마지막으로 버튼을 눌러 횟수를 올린 시각

// 세그먼트에 숫자 하나 표시 (캐소드 공통형이라 HIGH = 켜짐)
void showDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(SEG_PINS[i], DIGITS[digit][i] ? HIGH : LOW);
  }
}

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(SEG_PINS[i], OUTPUT); // 세그먼트 핀을 출력으로 설정
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 내부 풀업 사용 (안 누르면 HIGH)
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);             // 시리얼 모니터로 전체 횟수 확인용

  showDigit(0);                   // 처음엔 0 표시
  Serial.println("누른 횟수: 0");
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // 값이 바뀌면 시간 기록 (버튼 떨림 확인용)
  if (reading != lastReading) {
    lastChange = millis();
  }

  // 50ms 동안 같은 값이 유지되면 진짜 눌림/뗌으로 인정
  if (millis() - lastChange > DEBOUNCE_MS && reading != buttonState) {
    buttonState = reading;

    if (buttonState == LOW) {     // 눌린 순간에만 처리
      if (lastPress != 0 && millis() - lastPress < DOUBLE_MS) {
        // 빠르게 두 번 누름 -> 초기화
        count = 0;
        lastPress = 0;            // 세 번째 누름이 또 초기화되지 않도록
        ledDuration = RESET_LED_MS;
        Serial.println("초기화! 누른 횟수: 0");
      } else {
        count++;                  // 한 번 누름 -> 횟수 증가
        lastPress = millis();
        ledDuration = LED_ON_MS;
        Serial.print("누른 횟수: ");
        Serial.println(count);
      }
      showDigit(count % 10);      // 한 자리라서 일의 자리만 표시 (9 다음은 0)
      digitalWrite(LED_PIN, HIGH);
      ledOnAt = millis();
    }
  }
  lastReading = reading;

  // LED는 정해진 시간만 켜고 끄기
  if (millis() - ledOnAt > ledDuration) {
    digitalWrite(LED_PIN, LOW);
  }
}
