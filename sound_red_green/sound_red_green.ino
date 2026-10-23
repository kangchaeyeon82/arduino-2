// 조용하면 빨간 LED, 소리가 들리면 초록 LED 켜기
const int RED_PIN = 9;          // 빨간 LED 연결 핀
const int GREEN_PIN = 10;       // 초록 LED 연결 핀
const int SOUND_PIN = A0;       // 소리 센서 아날로그 출력(AO) 연결
const int THRESHOLD = 50;       // 이 값보다 소리가 크면 "소리 있음"으로 판단

void setup() {
  pinMode(RED_PIN, OUTPUT);     // 9번 핀을 출력으로 설정
  pinMode(GREEN_PIN, OUTPUT);   // 10번 핀을 출력으로 설정
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

  if (soundLevel > THRESHOLD) {
    digitalWrite(RED_PIN, LOW);     // 소리가 들리면 빨간 LED 끄고
    digitalWrite(GREEN_PIN, HIGH);  // 초록 LED 켜기
  } else {
    digitalWrite(RED_PIN, HIGH);    // 조용하면 빨간 LED 켜고
    digitalWrite(GREEN_PIN, LOW);   // 초록 LED 끄기
  }

  Serial.print("소리 크기: ");
  Serial.println(soundLevel);
}
