#define LED_PIN_1 3
#define BTN_PIN_1 2
#define POTENTIOMETER_PIN_1 A1
#define LED_PIN_2 5
#define BTN_PIN_2 4
#define POTENTIOMETER_PIN_2 A2
#define LED_PIN_3 6
#define BTN_PIN_3 7
#define POTENTIOMETER_PIN_3 A1
#define LED_PIN_4 9
#define BTN_PIN_4 8
#define POTENTIOMETER_PIN_4 A4
#define LED_PIN_5 11
#define BTN_PIN_5 12
#define POTENTIOMETER_PIN_5 A5

uint8_t btn1_prev_state;
uint8_t btn2_prev_state;
uint8_t btn3_prev_state;
uint8_t btn4_prev_state;
uint8_t btn5_prev_state;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(BTN_PIN_1, INPUT_PULLUP);
  btn1_prev_state = digitalRead(BTN_PIN_1);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(BTN_PIN_2, INPUT_PULLUP);
  btn2_prev_state = digitalRead(BTN_PIN_2);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(BTN_PIN_3, INPUT_PULLUP);
  btn3_prev_state = digitalRead(BTN_PIN_3);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(BTN_PIN_4, INPUT_PULLUP);
  btn4_prev_state = digitalRead(BTN_PIN_4);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(BTN_PIN_5, INPUT_PULLUP);
  btn5_prev_state = digitalRead(BTN_PIN_5);
}

void loop() {
  int pot1_val = analogRead(POTENTIOMETER_PIN_1);
  int bright1 = map(pot1_val, 0, 1023, 0, 255);
  analogWrite(LED_PIN_1, bright1);
  uint8_t btn1 = digitalRead(BTN_PIN_1);
  if (btn1 == LOW && btn1_prev_state == HIGH)
  {
    String comp = "Comp_1_" + pot1_val;
    Serial.println(comp);
  }
  btn1_prev_state = digitalRead(BTN_PIN_1);
}
