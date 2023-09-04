
#include "Arduino.h"
#include "SPI.h"

void _cb(void) {
  Serial.println("DO1");
}

void _cb1(void) {
  Serial.printf("TEMP %f\n", readBoardTemperature());
}

mcp4461_t* dev_mcp4461_0;
mcp4461_t* dev_mcp4461_1;

void init_pot() {
  mcp4461_cfg_t mcp4461_cfg;
  dev_mcp4461_0 = (mcp4461_t*)malloc(sizeof(mcp4461_t));
  dev_mcp4461_1 = (mcp4461_t*)malloc(sizeof(mcp4461_t));
  mcp4461_set_default_cfg(&mcp4461_cfg);
  mcp4461_cfg.i2c_addr = MCP4461_DEV_ADDR_1;
  mcp4461_init(dev_mcp4461_0, &mcp4461_cfg);
  mcp4461_cfg.i2c_addr = MCP4461_DEV_ADDR_3;
  mcp4461_init(dev_mcp4461_1, &mcp4461_cfg);
}

bool do_en = true;

void enableDO0() {
  cy8c9520_pin_mode(dev_cy8c9520, CY8C9520_GPIO_0, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_UP);
}

void disableDO0() {
  cy8c9520_pin_mode(dev_cy8c9520, CY8C9520_GPIO_0, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  delay(3000);

  Serial.println("Initializing..");
  pinMode(CONTROLLINO_MICRO_DI0, INPUT); // Digital only input 0-11V LOW > 11V HIGH
  pinMode(CONTROLLINO_MICRO_DI1, INPUT); // Digital only input 0-11V LOW > 11V HIGH
  pinMode(CONTROLLINO_MICRO_AI0, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  pinMode(CONTROLLINO_MICRO_AI1, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  setDigitalThreshold(CONTROLLINO_MICRO_AI0, 0x3FFFFF); // Digital therhold for analog input arround 12 V

  pinMode(CONTROLLINO_MICRO_DO0, OUTPUT); // DIgital outputs all with PWM
  pinMode(CONTROLLINO_MICRO_DO1, OUTPUT);
  pinMode(CONTROLLINO_MICRO_DO4, OUTPUT);
  pinMode(CONTROLLINO_MICRO_DO5, OUTPUT);

  init_pot();

  float current = 0.6923F;
  float parallel = (1.5F / (current * 0.0001F)) - 5000.0F;
  float r = parallel * 50000.0F / (50000.0F - parallel);
  Serial.printf("R: %f\n", r);
  

  uint16_t rxdata;
  mcp4461_write_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, 0x00);
  mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, &rxdata);
  Serial.println(rxdata, HEX);
}

unsigned long lastMillis = 0;

void loop(void) {
  Serial.print("CONTROLLINO_MICRO_DI0 state:");
  Serial.print(digitalRead(CONTROLLINO_MICRO_DI0) ? "HIGH" : "LOW");
  Serial.print("      CONTROLLINO_MICRO_DI1 ADC:");
  Serial.print(analogRead(CONTROLLINO_MICRO_DI1));
  Serial.print("      CONTROLLINO_MICRO_AI0 ADC:");
  Serial.print(analogRead(CONTROLLINO_MICRO_AI0));
  Serial.print(" DIGITAL:");
  Serial.print(digitalRead(CONTROLLINO_MICRO_AI0) ? "HIGH" : "LOW");

  digitalWrite(CONTROLLINO_MICRO_DO1, digitalRead(CONTROLLINO_MICRO_DI0));
  digitalWrite(CONTROLLINO_MICRO_DO5, digitalRead(CONTROLLINO_MICRO_AI0));

  uint8_t pwm = map(analogRead(CONTROLLINO_MICRO_AI0), 0, 0x7FFFFF, 0, 0xFF); // Analog 23 bits to 8 bit for PWM 
  Serial.print("      PWM:");
  Serial.print(pwm);
  
  Serial.print("      CONTROLLINO_MICRO_AI1 ADC:");
  Serial.print(analogRead(CONTROLLINO_MICRO_AI1));

  analogWrite(CONTROLLINO_MICRO_DO0, pwm);
  analogWrite(CONTROLLINO_MICRO_DO4, pwm);

  if ((millis() - lastMillis) > 5000)
  {
    if (do_en) {
      Serial.println("DO0 DISABLED");
      disableDO0();
      do_en = false;
    }
    else {
      Serial.println("DO0 ENABLED");
      enableDO0();
      do_en = true;
    }
    lastMillis = millis();
  }

  Serial.println();
  delay(500);
}
