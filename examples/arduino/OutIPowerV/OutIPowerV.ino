#include <SPI.h>

void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.println("Initializing..");
  pinMode(NEO_CORE_AI0, INPUT);
  setDigitalThreshold(NEO_CORE_AI0, 0x7FFFFF);

  pinMode(NEO_CORE_DI0, INPUT);

  pinMode(NEO_CORE_DO0, OUTPUT);
  pinMode(NEO_CORE_DO4, OUTPUT);
  pinMode(NEO_CORE_DO5, OUTPUT);
  pinMode(NEO_CORE_DO6, OUTPUT);
  pinMode(NEO_CORE_DO7, OUTPUT);
}

void loop(void) {
  delay(500);
  uint8_t pwm = map(analogRead(NEO_CORE_AI0), 0, 0x7FFFFF, 0, 0xFF);
  Serial1.print("analogWrite: ");
  Serial1.print(pwm);
  Serial1.print("\t hysteresis: ");
  Serial1.print(gpio_is_input_hysteresis_enabled(NEO_CORE_DI0->getPin()) ? "TRUE" : "FALSE");
  Serial1.print(" state: ");
  Serial1.println(digitalRead(NEO_CORE_DI0) ? "TRUE" : "FALSE");
  analogWrite(NEO_CORE_DO0, pwm);
  // analogWrite(NEO_CORE_DO4, pwm);
  // analogWrite(NEO_CORE_DO5, pwm);
  // analogWrite(NEO_CORE_DO6, pwm);
  // analogWrite(NEO_CORE_DO7, pwm);

  digitalWrite(NEO_CORE_DO5, digitalRead(NEO_CORE_DI0) ? HIGH : LOW);
}
