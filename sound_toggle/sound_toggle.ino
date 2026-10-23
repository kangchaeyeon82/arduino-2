// 큰 소리가 날 때마다 LED(9번) 켜짐/꺼짐 번갈아 바꾸기
const int LED_PIN = 9;          // LED 연결 핀
const int SOUND_PIN = A0;       // 소리 센서 아날로그 출력(AO) 연결
const int THRESHOLD = 50;       // 이 값보다 소리가 크면 "큰 소리"로 판단
const unsigned long WAIT_MS = 300; // 한 번 바뀐 뒤 300ms 동안은 다시 안 바뀜 (소리 울림 무시)

bool ledOn = false;             // 현재 LED 상태 (처음엔 꺼짐)
bool wasLoud = false;           // 직전에 큰 소리였는지
unsigned long lastToggle = 0;   // 마지막으로 LED를 바꾼 시각

void setup() {
  pinMode(LED_PIN, OUTPUT);     // 9번 핀을 출력으로 설정
  Serial.begin(9600);           // 시리얼 모니터로 소리 값 확인용
}

void loop() {
  // 50ms 동안 센서 값을 여러 번 읽어 가장 큰 값과 가장 작은 값을 찾음
  int maxValue = 0;
  int minValue = 1023;
  unsigned long start = millis();
  while (millis() - start < 50) {
    int value = analogRead(SOUND_PIN);  // 0 ~ 1023 읽기
    if (value > maxValue) maxValue = value;
    if (value < minValue) minValue = value;
  }
  int soundLevel = maxValue - minValue; // 흔들린 폭 = 소리 크기
  bool isLoud = soundLevel > THRESHOLD;

  // 조용하다가 큰 소리가 "새로" 들렸을 때만 LED 상태를 뒤집음
  if (isLoud && !wasLoud && millis() - lastToggle > WAIT_MS) {
    ledOn = !ledOn;                               // 켜짐 <-> 꺼짐
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    lastToggle = millis();

    Serial.print("LED ");
    Serial.println(ledOn ? "켜짐" : "꺼짐");
  }
  wasLoud = isLoud;

  Serial.print("소리 크기: ");
  Serial.println(soundLevel);
}
