#include <Arduino.h>

#define PIN_LED 18
typedef enum
{
  LED_OFF = 0,
  LED_ON = 1,
  LED_LOW_BLINK = 2,
  LED_QUICK_BLINK = 3
} LED_STATUS;

void testLedSetStatus(LED_STATUS status)
{
  switch (status)
  {
  case LED_OFF:
    // digitalWrite 设置电平
    digitalWrite(PIN_LED, LOW);
    break;
  case LED_ON:
    digitalWrite(PIN_LED, HIGH);
    break;
  case LED_LOW_BLINK:
    digitalWrite(PIN_LED, HIGH);
    delay(1000);
    digitalWrite(PIN_LED, LOW);
    delay(1000);
    digitalWrite(PIN_LED, HIGH);
    delay(1000);
    digitalWrite(PIN_LED, LOW);
    delay(1000);
    break;
  case LED_QUICK_BLINK:
    digitalWrite(PIN_LED, HIGH);
    delay(500);
    digitalWrite(PIN_LED, LOW);
    delay(500);
    digitalWrite(PIN_LED, HIGH);
    delay(500);
    digitalWrite(PIN_LED, LOW);
    delay(500);
    break;
  default:
    digitalWrite(PIN_LED, LOW);

    break;
  }

  // if (status == LED_OFF)
  // {
  //   digitalWrite(PIN_LED, LOW);
  // }
  // else if (status == LED_ON)
  // {
  //   digitalWrite(PIN_LED, HIGH);
  // }
  // else if (status == LED_LOW_BLINK)
  // {
  //   digitalWrite(PIN_LED, HIGH);
  //   delay(1000);
  //   digitalWrite(PIN_LED, LOW);
  //   delay(1000);
  //   digitalWrite(PIN_LED, HIGH);
  //   delay(1000);
  //   digitalWrite(PIN_LED, LOW);
  //   delay(1000);
  // }
  // else if (status == LED_QUICK_BLINK)
  // {
  //   digitalWrite(PIN_LED, HIGH);
  //   delay(500);
  //   digitalWrite(PIN_LED, LOW);
  //   delay(500);
  //   digitalWrite(PIN_LED, HIGH);
  //   delay(500);
  //   digitalWrite(PIN_LED, LOW);
  //   delay(500);
  // }
}

// setup 函数大概率不显示，实际上是运行了的
void setup()
{
  Serial.begin(115200);
  Serial.print("init steup\n");
  // pinMode() 函数将引脚18设置为输出模式
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // Serial.print("helloworld\n");
  // delay(1000);

  testLedSetStatus(LED_LOW_BLINK);
}