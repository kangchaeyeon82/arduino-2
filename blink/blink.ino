// [재구성 예시] LED 1초 간격 깜빡이기
const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);     // 13번 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // LED 켜기 (5V 출력)
  delay(1000);                  // 1000ms = 1초 대기
  digitalWrite(LED_PIN, LOW);   // LED 끄기 (0V 출력)
  delay(1000);                  // 1초 대기
}
