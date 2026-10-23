// 가변 저항(A0)으로 LED 밝기 조절하기
const int LED_PIN = 9;          // PWM(~) 핀이어야 밝기 조절 가능 (13번은 PWM 불가)
const int POT_PIN = A0;         // 가변 저항 가운데 다리 연결

void setup() {
  pinMode(LED_PIN, OUTPUT);     // 9번 핀을 출력으로 설정
  Serial.begin(9600);           // 시리얼 모니터로 값 확인용
}

void loop() {
  int potValue = analogRead(POT_PIN);              // 0 ~ 1023 읽기
  int brightness = map(potValue, 0, 1023, 0, 255); // 0 ~ 255로 변환
  analogWrite(LED_PIN, brightness);                // PWM으로 밝기 출력

  Serial.print("가변저항: ");
  Serial.print(potValue);
  Serial.print("  밝기: ");
  Serial.println(brightness);

  delay(50);                    // 50ms마다 갱신
}
