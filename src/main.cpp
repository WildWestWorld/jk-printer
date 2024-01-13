#include <Arduino.h>

// 蓝牙模块
#include <BLEDevice.h>
#include <BLE2902.h>

// LED DEMO
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
// LED DEMO 止

// 按钮DEMO
// 按钮的IO引脚
#define BUTTON_PIN_KEY 5
// 短按的时长
#define SHORT_PRESS_TIME 1000

// 按键是否按下
bool keyIsPress = false;
// 按键按下的时间
unsigned long clickTime = 0;
bool longPressIsStart = false;

// 初始化BUTTON引脚
void initButton()
{
  pinMode(BUTTON_PIN_KEY, INPUT);
}
// 检测按键是否按下，是否长按
void keyCheckRun()
{
  if (keyIsPress == false)
  {
    // 如果按键按下是低电平
    if (digitalRead(BUTTON_PIN_KEY) == LOW)
    {
      // 按键按下需要去除抖动
      delay(10);
      if (digitalRead(BUTTON_PIN_KEY) == LOW)
      {
        // 按键按下的状态为 按下
        keyIsPress = true;
        // 获取当前时间
        clickTime = millis();
      }
    }
  }

  // 如果按键按下后松开 就判断按下时间和松开时间 是否长按
  if (keyIsPress == true)
  {
    if (digitalRead(BUTTON_PIN_KEY) == HIGH)
    {
      if (millis() - clickTime > SHORT_PRESS_TIME)
      {
        Serial.printf("long click free\n");
        // 按键松开说明 长按结束
        longPressIsStart = false;
      }
      else
      {
        Serial.printf("short click \n");
      }
      // 按键松开，keyIsPress  就置为false
      keyIsPress = false;
    }
    // 按键一直按下 如果超过 短按时长就认定为长按
    else
    {
      if (millis() - clickTime > SHORT_PRESS_TIME)
      {
        // 如果之前按钮没被认定为长按，就把他认定为长按
        if (longPressIsStart == false)
        {
          Serial.printf("long click\n");
          longPressIsStart = true;
        }
      }
    }
  }
}
// 按钮 DEMO 止

// 电路检测demo

// 电量ADC引脚
#define PIN_BATTERY_ADC 34
// 分辨率为12bits (0-4095)
#define BATTERY_ADC_BIT 12

void adcInit()
{
  // 之前没有机械开关，
  // 所以用了个IO控制mos管来打开电量检测功能，后面加了开关后，这个mos管不需要了，所以这个io可以不用啦
  // digitalWrite(PIN_ADC_EN, LOW);
  // 默认分辨率也是12bit，可以不设置
  //  analogReadResolution(BATTERY_ADC_BIT);
}

/**
 * @brief 获取ADC引脚电压值，可根据需要加入滤波算法
 *
 * @return int
 */
int getAdcVolts()
{
  // int data = 0;
  // // 根据ADC算出Vout电压ADC值，ADC值/4095 ≈ 电压值/3.3，该方式与实测电压值有误差，需校准
  // // Vout = analogRead(BAT_PIN)* 3.3/ 4095.0;
  // // 获取IO口电压值
  // data = analogReadMilliVolts(PIN_BATTERY_ADC);
  // return data;

  int data = 0;
  int sum = 0;
  int numReadings = 10; // 读取的次数
  for (int i = 0; i < numReadings; i++)
  {
    sum += analogReadMilliVolts(PIN_BATTERY_ADC);
    delay(10); // 可以根据需要调整延迟时间
  }
  data = sum / numReadings;
  return data;
}

void readBattery()
{
  // 根据公式Vout = Vbat * R2 / (R1 + R2)，可以算出Vbat电压 Vbat = Vout*(10+10)/10
  // 电池满电4.2V，没电按3.3V算，就可以根据比例换算出实际的剩余电量

  // map为映射函数，把值从一个区间映射到另一个区间
  // map(long x, long in_min, long in_max, long out_min, long out_max)

  // const long rise = out_max - out_min;
  // const long delta = x - in_min;
  // return (delta * rise) / (in_max - in_min) + out_min;
  // map(值，原来的范围 最小值，原来的范围 最大值， 想要映射范围的最小值，想要映射范围的最大值)

  // Vout = Vbat * R2 / (R1 + R2)=> Vbat = Vout*(10+10)/10=> Vbat = Vout*(10+10)/10 => Vbat => getAdcVolts() * 2 =

  uint8_t battery = map(getAdcVolts() * 2, 3300, 4200, 0, 100);
  Serial.printf("battery = %d%\n", battery);
}
// 电路检测demo  止

// 蓝牙模块demo
#define BLE_NAME "Mini-Printer"                                    // 连接蓝牙模块时显示的名字
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"        // 自定义打印服务UUID
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // 自定义打印特征UUID

bool bleConnected = false;

BLECharacteristic *pCharacteristic;

void bleReport()
{
  if (bleConnected == true)
  {
    uint8_t status[4];
    status[0] = 0;
    status[1] = 1;
    status[2] = 2;
    status[3] = 3;

    // 接下来，使用 pCharacteristic->setValue() 函数将 status 数组的值设置为BLE特征的值。
    // 最后，使用 pCharacteristic->notify() 函数发送通知，将特征的值发送给已连接的设备。

    pCharacteristic->setValue((uint8_t *)&status, sizeof(status));
    pCharacteristic->notify();
  }
}

// Server回调函数声明
// 这段代码定义了一个名为 bleServerCallbacks 的类，该类继承自 BLEServerCallbacks 类。
// 硬件服务端 连入事件
class bleServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    bleConnected = true;
    Serial.println("现在有设备接入~");
  }

  void onDisconnect(BLEServer *pServer)
  {
    bleConnected = false;
    Serial.println("现在有设备断开连接~");
    // 在有设备接入后Advertising广播会被停止，所以要在设备断开连接时重新开启广播
    pServer->startAdvertising();
  }
};
// 客户端 接收参数事件
class bleCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *pCharacteristic)
  { // 客户端读取事件回调函数
    Serial.println("触发读取事件");
  }

  void onWrite(BLECharacteristic *pCharacteristic)
  { // 客户端写入事件回调函数
    size_t length = pCharacteristic->getLength();
    uint8_t *pdata = pCharacteristic->getData();
    Serial.printf("触发写入事件 length=%d \n", length);
  }
};

void initBle()
{
  // 初始化 设备名称
  BLEDevice::init(BLE_NAME); // 填写自身对外显示的蓝牙设备名称，并初始化蓝牙功能

  BLEServer *pServer = BLEDevice::createServer(); // 创建服务器，板卡与手机的关系：手机是客户端，板卡蓝牙是服务器
  // 绑定 服务端 连入事件
  pServer->setCallbacks(new bleServerCallbacks()); // 绑定回调函数

  BLEService *pService = pServer->createService(SERVICE_UUID); // 创建服务

  // createCharacteristic(id,特征权限)
  //       BLECharacteristic::PROPERTY_READ |
  // BLECharacteristic::PROPERTY_NOTIFY |
  //     BLECharacteristic::PROPERTY_WRITE  = >可读可写可订阅
  pCharacteristic = pService->createCharacteristic( // 创建特征
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_WRITE);

  // 绑定 客户端 接收参数事件
  pCharacteristic->setCallbacks(new bleCharacteristicCallbacks()); // 绑定回调函数

  pService->start();             // 启动服务
  BLEDevice::startAdvertising(); // 开启Advertising广播
}
// 蓝牙模块demo 止

// setup 函数大概率不显示，实际上是运行了的
void setup()
{
  Serial.begin(115200);
  Serial.print("init steup\n");
  // initButton();

  // 初始化蓝牙
  initBle();
}

void loop()
{
  // Serial.print("helloworld\n");
  // delay(1000);

  // testLedSetStatus(LED_LOW_BLINK);

  // 检测是否按下/长按按钮
  // keyCheckRun();

  // 查看电池电量
  // delay(1000);
  // readBattery();

  // 如果连入蓝牙，就会发送消息
  delay(5000);
  bleReport();
}