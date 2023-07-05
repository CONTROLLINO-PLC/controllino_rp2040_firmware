
#include "Arduino.h"
#include "SPI.h"
#include "hw_platform.h"

uint8_t txdata;
uint8_t rxdata;
uint32_t adc_data;
uint8_t sgn;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  delay(3000);

  Serial.println("Initializing..");
  pinMode(NEO_CORE_DI0, INPUT); // Digital only input 0-10V LOW > 10V HIGH 
  pinMode(NEO_CORE_AI0, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  pinMode(NEO_CORE_AI1, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  setDigitalThreshold(NEO_CORE_AI0, 0x3FFFFF); // Digital therhold for analog input arround 12 V

  pinMode(NEO_CORE_DO0, OUTPUT); // DIgital outputs all with PWM
  pinMode(NEO_CORE_DO1, OUTPUT);
  pinMode(NEO_CORE_DO4, OUTPUT);
  pinMode(NEO_CORE_DO5, OUTPUT);
}

void loop(void) {
  Serial.print("NEO_CORE_DI0 state:");
  Serial.print(digitalRead(NEO_CORE_DI0) ? "HIGH" : "LOW");
  Serial.print("      NEO_CORE_AI0 ADC:");
  Serial.print(analogRead(NEO_CORE_AI0));
  Serial.print(" DIGITAL:");
  Serial.print(digitalRead(NEO_CORE_AI0) ? "HIGH" : "LOW");

  digitalWrite(NEO_CORE_DO1, digitalRead(NEO_CORE_DI0));
  digitalWrite(NEO_CORE_DO5, digitalRead(NEO_CORE_AI0));

  // mcp356x_iread(neo_mcp356x, MCP356X_REG_MUX, &rxdata, 1);
  // mcp356x_read_adc_def(neo_mcp356x, &adc_data, &sgn);
  // Serial.printf("    ADC %d MUX %02x:", adc_data, rxdata);
  // Serial.print(analogRead(NEO_CORE_AI2));
  // rxdata = 0x00;
  // adc_data = 0x00;
  // mcp356x_iread(neo_mcp356x, MCP356X_REG_MUX, &rxdata, 1);
  // mcp356x_read_adc_def(neo_mcp356x, &adc_data, &sgn);
  // Serial.printf("    ADC %d MUX %02x:", adc_data, rxdata);

  uint8_t pwm = map(analogRead(NEO_CORE_AI0), 0, 0x7FFFFF, 0, 0xFF); // Analog 23 bits to 8 bit for PWM 
  Serial.print("      PWM:");
  Serial.print(pwm);

  analogWrite(NEO_CORE_DO0, pwm);
  analogWrite(NEO_CORE_DO4, pwm);

  Serial.println();
  delay(500);
}
