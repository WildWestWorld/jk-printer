// #include <Arduino.h>

// // 蓝牙模块
// #include <BLEDevice.h>
// #include <BLE2902.h>

// // 步进电机依赖
// #include <Ticker.h>


// // LED DEMO
// #define PIN_LED 18
// typedef enum
// {
//   LED_OFF = 0,
//   LED_ON = 1,
//   LED_LOW_BLINK = 2,
//   LED_QUICK_BLINK = 3
// } LED_STATUS;

// void testLedSetStatus(LED_STATUS status)
// {
//   switch (status)
//   {
//   case LED_OFF:
//     // digitalWrite 设置电平
//     digitalWrite(PIN_LED, LOW);
//     break;
//   case LED_ON:
//     digitalWrite(PIN_LED, HIGH);
//     break;
//   case LED_LOW_BLINK:
//     digitalWrite(PIN_LED, HIGH);
//     delay(1000);
//     digitalWrite(PIN_LED, LOW);
//     delay(1000);
//     digitalWrite(PIN_LED, HIGH);
//     delay(1000);
//     digitalWrite(PIN_LED, LOW);
//     delay(1000);
//     break;
//   case LED_QUICK_BLINK:
//     digitalWrite(PIN_LED, HIGH);
//     delay(500);
//     digitalWrite(PIN_LED, LOW);
//     delay(500);
//     digitalWrite(PIN_LED, HIGH);
//     delay(500);
//     digitalWrite(PIN_LED, LOW);
//     delay(500);
//     break;
//   default:
//     digitalWrite(PIN_LED, LOW);

//     break;
//   }

//   // if (status == LED_OFF)
//   // {
//   //   digitalWrite(PIN_LED, LOW);
//   // }
//   // else if (status == LED_ON)
//   // {
//   //   digitalWrite(PIN_LED, HIGH);
//   // }
//   // else if (status == LED_LOW_BLINK)
//   // {
//   //   digitalWrite(PIN_LED, HIGH);
//   //   delay(1000);
//   //   digitalWrite(PIN_LED, LOW);
//   //   delay(1000);
//   //   digitalWrite(PIN_LED, HIGH);
//   //   delay(1000);
//   //   digitalWrite(PIN_LED, LOW);
//   //   delay(1000);
//   // }
//   // else if (status == LED_QUICK_BLINK)
//   // {
//   //   digitalWrite(PIN_LED, HIGH);
//   //   delay(500);
//   //   digitalWrite(PIN_LED, LOW);
//   //   delay(500);
//   //   digitalWrite(PIN_LED, HIGH);
//   //   delay(500);
//   //   digitalWrite(PIN_LED, LOW);
//   //   delay(500);
//   // }
// }
// // LED DEMO 止

// // 按钮DEMO
// // 按钮的IO引脚
// #define BUTTON_PIN_KEY 5
// // 短按的时长
// #define SHORT_PRESS_TIME 1000

// // 按键是否按下
// bool keyIsPress = false;
// // 按键按下的时间
// unsigned long clickTime = 0;
// bool longPressIsStart = false;

// // 初始化BUTTON引脚
// void initButton()
// {
//   pinMode(BUTTON_PIN_KEY, INPUT);
// }
// // 检测按键是否按下，是否长按
// void keyCheckRun()
// {
//   if (keyIsPress == false)
//   {
//     // 如果按键按下是低电平
//     if (digitalRead(BUTTON_PIN_KEY) == LOW)
//     {
//       // 按键按下需要去除抖动
//       delay(10);
//       if (digitalRead(BUTTON_PIN_KEY) == LOW)
//       {
//         // 按键按下的状态为 按下
//         keyIsPress = true;
//         // 获取当前时间
//         clickTime = millis();
//       }
//     }
//   }

//   // 如果按键按下后松开 就判断按下时间和松开时间 是否长按
//   if (keyIsPress == true)
//   {
//     if (digitalRead(BUTTON_PIN_KEY) == HIGH)
//     {
//       if (millis() - clickTime > SHORT_PRESS_TIME)
//       {
//         Serial.printf("long click free\n");
//         // 按键松开说明 长按结束
//         longPressIsStart = false;
//       }
//       else
//       {
//         Serial.printf("short click \n");
//       }
//       // 按键松开，keyIsPress  就置为false
//       keyIsPress = false;
//     }
//     // 按键一直按下 如果超过 短按时长就认定为长按
//     else
//     {
//       if (millis() - clickTime > SHORT_PRESS_TIME)
//       {
//         // 如果之前按钮没被认定为长按，就把他认定为长按
//         if (longPressIsStart == false)
//         {
//           Serial.printf("long click\n");
//           longPressIsStart = true;
//         }
//       }
//     }
//   }
// }
// // 按钮 DEMO 止

// // 电路检测demo

// // 电量ADC引脚
// #define PIN_BATTERY_ADC 34
// // 分辨率为12bits (0-4095)
// #define BATTERY_ADC_BIT 12

// void adcInit()
// {
//   // 之前没有机械开关，
//   // 所以用了个IO控制mos管来打开电量检测功能，后面加了开关后，这个mos管不需要了，所以这个io可以不用啦
//   // digitalWrite(PIN_ADC_EN, LOW);
//   // 默认分辨率也是12bit，可以不设置
//   //  analogReadResolution(BATTERY_ADC_BIT);
// }

// /**
//  * @brief 获取ADC引脚电压值，可根据需要加入滤波算法
//  *
//  * @return int
//  */
// int getAdcVolts()
// {
//   // int data = 0;
//   // // 根据ADC算出Vout电压ADC值，ADC值/4095 ≈ 电压值/3.3，该方式与实测电压值有误差，需校准
//   // // Vout = analogRead(BAT_PIN)* 3.3/ 4095.0;
//   // // 获取IO口电压值
//   // data = analogReadMilliVolts(PIN_BATTERY_ADC);
//   // return data;

//   int data = 0;
//   int sum = 0;
//   int numReadings = 10; // 读取的次数
//   for (int i = 0; i < numReadings; i++)
//   {
//     sum += analogReadMilliVolts(PIN_BATTERY_ADC);
//     delay(10); // 可以根据需要调整延迟时间
//   }
//   data = sum / numReadings;
//   return data;
// }

// void readBattery()
// {
//   // 根据公式Vout = Vbat * R2 / (R1 + R2)，可以算出Vbat电压 Vbat = Vout*(10+10)/10
//   // 电池满电4.2V，没电按3.3V算，就可以根据比例换算出实际的剩余电量

//   // map为映射函数，把值从一个区间映射到另一个区间
//   // map(long x, long in_min, long in_max, long out_min, long out_max)

//   // const long rise = out_max - out_min;
//   // const long delta = x - in_min;
//   // return (delta * rise) / (in_max - in_min) + out_min;
//   // map(值，原来的范围 最小值，原来的范围 最大值， 想要映射范围的最小值，想要映射范围的最大值)

//   // Vout = Vbat * R2 / (R1 + R2)=> Vbat = Vout*(10+10)/10=> Vbat = Vout*(10+10)/10 => Vbat => getAdcVolts() * 2 =

//   uint8_t battery = map(getAdcVolts() * 2, 3300, 4200, 0, 100);
//   Serial.printf("battery = %d%\n", battery);
// }
// // 电路检测demo  止

// // 蓝牙模块demo
// #define BLE_NAME "Mini-Printer"                                    // 连接蓝牙模块时显示的名字
// #define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"        // 自定义打印服务UUID
// #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // 自定义打印特征UUID

// bool bleConnected = false;

// BLECharacteristic *pCharacteristic;

// void bleReport()
// {
//   if (bleConnected == true)
//   {
//     uint8_t status[4];
//     status[0] = 0;
//     status[1] = 1;
//     status[2] = 2;
//     status[3] = 3;

//     // 接下来，使用 pCharacteristic->setValue() 函数将 status 数组的值设置为BLE特征的值。
//     // 最后，使用 pCharacteristic->notify() 函数发送通知，将特征的值发送给已连接的设备。

//     pCharacteristic->setValue((uint8_t *)&status, sizeof(status));
//     pCharacteristic->notify();
//   }
// }

// // Server回调函数声明
// // 这段代码定义了一个名为 bleServerCallbacks 的类，该类继承自 BLEServerCallbacks 类。
// // 硬件服务端 连入事件
// class bleServerCallbacks : public BLEServerCallbacks
// {
//   void onConnect(BLEServer *pServer)
//   {
//     bleConnected = true;
//     Serial.println("现在有设备接入~");
//   }

//   void onDisconnect(BLEServer *pServer)
//   {
//     bleConnected = false;
//     Serial.println("现在有设备断开连接~");
//     // 在有设备接入后Advertising广播会被停止，所以要在设备断开连接时重新开启广播
//     pServer->startAdvertising();
//   }
// };
// // 客户端 接收参数事件
// class bleCharacteristicCallbacks : public BLECharacteristicCallbacks
// {
//   void onRead(BLECharacteristic *pCharacteristic)
//   { // 客户端读取事件回调函数
//     Serial.println("触发读取事件");
//   }

//   void onWrite(BLECharacteristic *pCharacteristic)
//   { // 客户端写入事件回调函数
//     size_t length = pCharacteristic->getLength();
//     uint8_t *pdata = pCharacteristic->getData();
//     Serial.printf("触发写入事件 length=%d \n", length);
//   }
// };

// void initBle()
// {
//   // 初始化 设备名称
//   BLEDevice::init(BLE_NAME); // 填写自身对外显示的蓝牙设备名称，并初始化蓝牙功能

//   BLEServer *pServer = BLEDevice::createServer(); // 创建服务器，板卡与手机的关系：手机是客户端，板卡蓝牙是服务器
//   // 绑定 服务端 连入事件
//   pServer->setCallbacks(new bleServerCallbacks()); // 绑定回调函数

//   BLEService *pService = pServer->createService(SERVICE_UUID); // 创建服务

//   // createCharacteristic(id,特征权限)
//   //       BLECharacteristic::PROPERTY_READ |
//   // BLECharacteristic::PROPERTY_NOTIFY |
//   //     BLECharacteristic::PROPERTY_WRITE  = >可读可写可订阅
//   pCharacteristic = pService->createCharacteristic( // 创建特征
//       CHARACTERISTIC_UUID,
//       BLECharacteristic::PROPERTY_READ |
//           BLECharacteristic::PROPERTY_NOTIFY |
//           BLECharacteristic::PROPERTY_WRITE);

//   // 绑定 客户端 接收参数事件
//   pCharacteristic->setCallbacks(new bleCharacteristicCallbacks()); // 绑定回调函数

//   pService->start();             // 启动服务
//   BLEDevice::startAdvertising(); // 开启Advertising广播
// }
// // 蓝牙模块demo 止

// // 缺纸模块

// // 缺纸检测引脚
// #define PIN_PAPER 35
// // 打印头电源升压控制引脚
// #define PIN_VHEN 17

// typedef enum
// {
//   PAPER_STATUS_NORMAL = 0,
//   PAPER_STATUS_LACK = 1,
// } paper_state_e;

// paper_state_e status = PAPER_STATUS_NORMAL;

// void readPaperStatue()
// {
//   // if (digitalRead(PIN_PAPER) == PAPER_STATUS_NORMAL)
//   // {
//   //   Serial.printf("PAPER_STATUS_NORMAL\n");
//   //   status = PAPER_STATUS_NORMAL;
//   // }
//   // else
//   // {
//   //   Serial.printf("PAPER_STATUS_LACK\n");
//   //   status = PAPER_STATUS_LACK;
//   // }

//   if (digitalRead(PIN_PAPER) == PAPER_STATUS_LACK)
//   {
//     Serial.printf("PAPER_STATUS_LACK\n");
//     status = PAPER_STATUS_NORMAL;
//   }
// }
// // 这段代码是一个Arduino的中断服务例程（ISR）的定义。
// // ARDUINO_ISR_ATTR 宏来指定中断服务例程的属性。
// void ARDUINO_ISR_ATTR paperIsr()
// {
//   // 此处不可执行耗时操作
//   // Serial.printf("PAPER_STATUS_LACK\n");
//   status = PAPER_STATUS_LACK;
// }

// void initPaperStatus()
// {

//   // 打印机开始打印前，最重要的是判断之一是当前有没有缺打印纸，所以我们需要读取缺纸传感器的信号进行判断。
//   // 从这节课开始，我们需要接上打印模组，打印模组使用前有个注意点，VH电源在不打印时，需要保持关闭。
//   pinMode(PIN_VHEN, OUTPUT);
//   digitalWrite(PIN_VHEN, LOW);

//   // 缺纸IO初始化
//   pinMode(PIN_PAPER, INPUT);
//   // 如果PIN_PAPER 引脚 出现上升沿 就会触发 paperIsr 函数 就是变更 状态为缺纸
//   attachInterrupt(PIN_PAPER, paperIsr, RISING);
// }

// // 缺纸模块 止

// // 打印头温度检测模块

// /**
//  公式法：
// NTC 热敏电阻温度计算公式：Rt = Rp *EXP(B*(1/T1-1/T2))
// 可以得到温度T1与电阻Rt的关系T1=1/（log（Rt/Rp）/B+1/T2）

// T1和T2指的是K度，即开尔文温度,K度=273.15(绝对温度)+摄氏度。
// T2=(273.15+25)
// Rt 是热敏电阻在T1温度下的阻值。
// Rp 是热敏电阻在T2常温下的标称阻值。100K的热敏电阻25℃的值为100K（即R=100K）。T2=(273.15+25)
// B值是热敏电阻的重要参数  B25/50= 3950K ±1%
// 最终对应的摄氏温度t=T1-273.15,同时+0.5的误差矫正。
// ADC采样率12位 串联电阻R1=10K R2=热敏电阻 电压3.3V
// 已知
// Rt = R*(3.3-VR)/VR
// VR = 3.3*ADC_Value/4095
// 得出
// ADC_Value = VR*4095/3.3 =3.3*R/(Rt+R)*4095/3.3 = R/(Rt+R)*1024
// ADC_Value=3.3/(C5+10)*10/3.3*4095
// 最终根据Rt算处温度值
// Rt=100*exp(3950*(1/(273.15+T1)-1/(273.15+25)))
// */

// #define PIN_TEMPERATRUE 36
// // 引脚的分辨率 我们用用的36号引脚
// //  设置分辨率为12bits (0-4095)  12bits = > 2^12 => 取值范围 :0-2^12-1
// #define TEMPERATRUE_ADC_BIT 12
// /**
//  * @brief 阻值转换温度
//  *
//  * @param Rt 热敏电阻阻值
//  * @return float 返回摄氏度温度
//  */
// float emTempCalculate(float Rt)
// {

//   // 根据阻值算温度

//   //   NTC 热敏电阻温度计算公式：Rt = Rp *EXP(B*(1/T1-1/T2))
//   // 可以得到温度T1与电阻Rt的关系T1=1/（log（Rt/Rp）/B+1/T2）

//   // RT我们已经求出来了
//   // Rp 是热敏电阻在T2常温下的标称阻值。热敏电阻 25℃的值为30K（即摄氏度=25度,R=30K）
//   // Rp 哪里来的从文档中查出来的

//   // B值是热敏电阻的重要参数 （文档中查出） B= 3950K ±2%

//   float T2 = 273.15 + 25;
//   float Rp = 30000;   // 30k
//   float Bx = 3950000; // B值
//   float Ka = 273.15;
//   float temp = 0.0f;

//   // 为什么减 Ka？ 因为 K度=273.15(绝对温度)+摄氏度 减掉Ka才能求出摄氏度
//   // 最终对应的摄氏温度t=T1-273.15,同时+0.5的误差矫正。

//   temp = 1 / (log(Rt / Rp) / Bx + 1 / T2) - Ka + 0.5;
//   return temp;
// }

// /**
//  * @brief Get the adc temperatrue object
//  *
//  * @return float
//  */
// float getAdcTemperatrue()
// {
//   float temp = 0.0f;
//   float Rt = 0;
//   float vol = 0;
//   // ADC转换为电压 vol=AD/4095*VCC
//   vol = (float)((analogReadMilliVolts(PIN_TEMPERATRUE)) * (3.3 / 4095));

//   // vol 我们上面读取并转化了范围(0-3.3)
//   // VCC 3.3V
//   // R 是确定的，我们放上去的电阻阻值为  10K

//   // 电压转换为阻值 原理图为10k 1%精度  vol/VCC=Rt/(R+Rt)  vol/3.3=Rt/(10000+Rt)
//   Rt = (vol * 10000) / (3.3 - vol);
//   // 利用Rt 热敏电阻公式 根据阻值计算出温度
//   temp = emTempCalculate(Rt);
//   return temp;
// }

// void emAdcTest()
// {
//   float Rt = 0;
//   Rt = 60000; // 60k 10°C
//   float temp = 0.0f;
//   temp = emTempCalculate(Rt);
//   Serial.printf("temp = %f\n", temp);
// }

// void temperatrueAdcInit()
// {

//   // 初始话引脚bit 我们设置 TEMPERATRUE_ADC_BIT =12 让他的取值范围为（0-4095）
//   analogReadResolution(TEMPERATRUE_ADC_BIT);
// }

// void initVH()
// {
//   // 关闭VH
//   pinMode(PIN_VHEN, OUTPUT);
//   digitalWrite(PIN_VHEN, LOW);
// }
// // 打印头温度检测模块 止步

// // 步进电机模块

// // 电机引脚
// #define PIN_MOTOR_AP 23
// #define PIN_MOTOR_AM 22
// #define PIN_MOTOR_BP 21
// #define PIN_MOTOR_BM 19

// #define MOTOR_WATI_TIME 2 // 电机运行一步的时间 2ms/500Hz

// /*
// step  A  B  A- B-
//       AN BN AP BP
// 1     1  0  0  1
// 2     0  0  0  1
// 3     0  0  1  1
// 4     0  0  1  0
// 5     0  1  1  0
// 6     0  1  0  0
// 7     1  1  0  0
// 8     1  0  0  0
// */
// uint8_t motor_table[8][4] =
//     {
//         {1, 0, 0, 1},
//         {0, 0, 0, 1},
//         {0, 1, 0, 1},
//         {0, 1, 0, 0},
//         {0, 1, 1, 0},
//         {0, 0, 1, 0},
//         {1, 0, 1, 0},
//         {1, 0, 0, 0}};

// uint8_t motor_pos = 0;

// // 定时器
// Ticker timer_motor;
// // 持续运行-定时器回调
// void timerMotorCallbackfun()
// {
//   // 电机转动核心代码
//   digitalWrite(PIN_MOTOR_AP, motor_table[motor_pos][0]);
//   digitalWrite(PIN_MOTOR_AM, motor_table[motor_pos][1]);
//   digitalWrite(PIN_MOTOR_BP, motor_table[motor_pos][2]);
//   digitalWrite(PIN_MOTOR_BM, motor_table[motor_pos][3]);
//   motor_pos++;
//   if (motor_pos >= 8)
//   {
//     motor_pos = 0;
//   }
// }
// // 持续运行-开始
// void motorStart()
// {
//   // 如果 定时器 状态未开启，就开启 定时器
//   if (timer_motor.active() == false)
//     timer_motor.attach_ms(2, timerMotorCallbackfun);
// }
// // 持续运行-关闭
// void motorStop()
// {

//   // 重置电机控制器
//   digitalWrite(PIN_MOTOR_AP, 0);
//   digitalWrite(PIN_MOTOR_AM, 0);
//   digitalWrite(PIN_MOTOR_BP, 0);
//   digitalWrite(PIN_MOTOR_BM, 0);

//   // 如果 定时器 状态开启，就关闭 定时器
//   if (timer_motor.active())
//     timer_motor.detach();
// }

// void motorRun()
// {
//   digitalWrite(PIN_MOTOR_AP, motor_table[motor_pos][0]);
//   digitalWrite(PIN_MOTOR_AM, motor_table[motor_pos][1]);
//   digitalWrite(PIN_MOTOR_BP, motor_table[motor_pos][2]);
//   digitalWrite(PIN_MOTOR_BM, motor_table[motor_pos][3]);
//   motor_pos++;
//   if (motor_pos >= 8)
//   {
//     motor_pos = 0;
//   }
// }

// // 指定步数运行
// void motorRunStep(uint32_t steps)
// {
//   while (steps)
//   {
//     digitalWrite(PIN_MOTOR_AP, motor_table[motor_pos][0]);
//     digitalWrite(PIN_MOTOR_AM, motor_table[motor_pos][1]);
//     digitalWrite(PIN_MOTOR_BP, motor_table[motor_pos][2]);
//     digitalWrite(PIN_MOTOR_BM, motor_table[motor_pos][3]);
//     motor_pos++;
//     if (motor_pos >= 8)
//     {
//       motor_pos = 0;
//     }
//     delay(MOTOR_WATI_TIME);
//     steps--;
//   }
// }

// void initMotor()
// {
//   pinMode(PIN_MOTOR_AP, OUTPUT);
//   pinMode(PIN_MOTOR_AM, OUTPUT);
//   pinMode(PIN_MOTOR_BP, OUTPUT);
//   pinMode(PIN_MOTOR_BM, OUTPUT);

//   digitalWrite(PIN_MOTOR_AP, 0);
//   digitalWrite(PIN_MOTOR_AM, 0);
//   digitalWrite(PIN_MOTOR_BP, 0);
//   digitalWrite(PIN_MOTOR_BM, 0);
// }

// // 电机模块 止

// // 打印头模块
// //////////////////////////////////////////////////SPI部分//////////////////////////////////////////////////
// // 打印的内容是通过SPI接口发送给打印头的，这里用的SPI有两根线，一根时钟，一根数据线
// // 一行有384个点，用384bit来表示，bit为0时不加热，bit为1时加热
// // 一个byte有8个bit，那一行就是发送384/8=48Byte的
// #define SPI_CODE
// #ifdef SPI_CODE
// #include <SPI.h>

// // 打印头数据引脚
// #define PIN_SCK 15
// #define PIN_SDA 13
// static const int spiClk = 1000000; // 1 MHz

// // 新建SPI类
// SPIClass hspi = SPIClass(HSPI);

// // SPISettings 构造函数接受三个参数：
// // 1. 时钟频率（以赫兹为单位）。在这种情况下，设置为1,000,000赫兹（1兆赫）。
// // 2. 数据传输的位顺序。 SPI_MSBFIRST 表示最高有效位先传输。
// // 3. SPI模式。 SPI_MODE0 指定了SPI模式，其中时钟通常为低电平（CPOL = 0），数据在上升沿采样（上升沿过渡，CPOL = 0，CPHA = 0）。
// // 设置SPI类的配置
// SPISettings printerSPISettings = SPISettings(1000000, SPI_MSBFIRST, SPI_MODE0);

// void spiCommand(uint8_t *data_buffer, uint8_t data_len)
// {
//   // use it as you would the regular arduino SPI API
//   hspi.beginTransaction(printerSPISettings);
//   hspi.transfer(data_buffer, data_len);
//   hspi.endTransaction();
// }

// void init_spi()
// {
//   // hspi = SPIClass(HSPI);
//   // alternatively route through GPIO pins
//   // hspi.begin(PIN_SCK, -1, PIN_SDA, -1); // 课程原来的代码与新打印头适配时，初始化为-1时，会导致LAT锁存引脚不受控

//   //  1. 代码开始通过调用 hspi 对象的 begin() 函数来初始化SPI通信。
//   // 2. begin() 函数接受四个参数： PIN_SCK ， 16 ， PIN_SDA 和 -1 。这些参数指定用于SPI通信的引脚。
//   // PIN_SCK 是时钟引脚， 16 是MISO（主进从出）引脚， PIN_SDA 是MOSI（主出从进）引脚， -1 是SS（从选择）引脚。
//   // 3. 在初始化SPI通信之后，代码使用 setFrequency() 函数将SPI通信的频率设置为2,000,000赫兹（2兆赫）。

//   hspi.begin(PIN_SCK, 16, PIN_SDA, -1); // SCLK, MISO, MOSI, SS
//   hspi.setFrequency(2000000);
// }
// #endif

// //////////////////////////////////////////////////打印部分//////////////////////////////////////////////////
// #define PRINTER_CODE
// #ifdef PRINTER_CODE
// // 打印头数据锁存引脚
// #define PIN_LAT 12
// // 通道引脚
// // 原厂 V3
// #define PIN_STB1 26
// #define PIN_STB2 27
// #define PIN_STB3 14
// #define PIN_STB4 32
// #define PIN_STB5 33
// #define PIN_STB6 25

// // 拆机 V2
// //  #define PIN_STB1 14
// //  #define PIN_STB2 27
// //  #define PIN_STB3 26
// //  #define PIN_STB4 25
// //  #define PIN_STB5 33
// //  #define PIN_STB6 32

// #define PRINT_TIME 1700    // 打印加热时间
// #define PRINT_END_TIME 200 // 冷却时间
// #define LAT_TIME 1         // 数据锁存时间
// #define PIN_VHEN 17        // 打印头电源升压控制引脚

// /**
//  * @brief 失能所有通道
//  *
//  */
// static void set_stb_idle()
// {
//   digitalWrite(PIN_STB1, LOW);
//   digitalWrite(PIN_STB2, LOW);
//   digitalWrite(PIN_STB3, LOW);
//   digitalWrite(PIN_STB4, LOW);
//   digitalWrite(PIN_STB5, LOW);
//   digitalWrite(PIN_STB6, LOW);
// }

// /**
//  * @brief 打印前初始化
//  *
//  */
// static void init_printing()
// {
//   set_stb_idle();
//   // PIN_LAT 初始化打印时得 高电平
//   // 传入 锁存数据 得发生上升沿
//   digitalWrite(PIN_LAT, HIGH);
//   // POWER ON
//   digitalWrite(PIN_VHEN, HIGH);
// }

// /**
//  * @brief 打印后停止
//  *
//  */
// static void stop_printing()
// {
//   // POWER OFF
//   digitalWrite(PIN_VHEN, LOW);
//   set_stb_idle();
//   digitalWrite(PIN_LAT, HIGH);
// }

// /**
//  * @brief 发送一行数据
//  *
//  * @param data
//  */
// static void send_one_line_data(uint8_t *data)
// {

//   // 使用SPI 发送数据
//   spiCommand(data, 48);

//   // 发送锁存数据 得产生上升沿
//   /* After send one dot line, send LAT signal low pulse.*/
//   digitalWrite(PIN_LAT, LOW);
//   delayMicroseconds(LAT_TIME);
//   digitalWrite(PIN_LAT, HIGH);
// }

// /**
//  * @brief 通道打印运行
//  *
//  * @param now_stb_num
//  */
// static void run_stb(uint8_t now_stb_num)
// {
//   switch (now_stb_num)
//   {
//   case 0:
//     // 如果是通道一 就先拉高通道一的电平拉高进行加热
//     digitalWrite(PIN_STB1, 1);
//     // 延迟 加热时间
//     delayMicroseconds(PRINT_TIME);

//     // 打印完成就拉低电平，然后冷却
//     digitalWrite(PIN_STB1, 0);
//     // 延迟 冷却时间
//     delayMicroseconds(PRINT_END_TIME);
//     break;
//   case 1:
//     digitalWrite(PIN_STB2, 1);
//     delayMicroseconds(PRINT_TIME);
//     digitalWrite(PIN_STB2, 0);
//     delayMicroseconds(PRINT_END_TIME);
//     break;
//   case 2:
//     digitalWrite(PIN_STB3, 1);
//     delayMicroseconds(PRINT_TIME);
//     digitalWrite(PIN_STB3, 0);
//     delayMicroseconds(PRINT_END_TIME);
//     break;
//   case 3:
//     digitalWrite(PIN_STB4, 1);
//     delayMicroseconds(PRINT_TIME);
//     digitalWrite(PIN_STB4, 0);
//     delayMicroseconds(PRINT_END_TIME);
//     break;
//   case 4:
//     digitalWrite(PIN_STB5, 1);
//     delayMicroseconds(PRINT_TIME);
//     digitalWrite(PIN_STB5, 0);
//     delayMicroseconds(PRINT_END_TIME);
//     break;
//   case 5:
//     digitalWrite(PIN_STB6, 1);
//     delayMicroseconds(PRINT_TIME);
//     digitalWrite(PIN_STB6, 0);
//     delayMicroseconds(PRINT_END_TIME);
//     break;
//   default:
//     break;
//   }
// }

// /**
//  * @brief 移动电机&开始打印
//  *
//  * @param need_stop
//  * @param stbnum
//  */
// bool move_and_start_std(bool need_stop, uint8_t stbnum)
// {
//   // 若是检测异常，缺纸/点击异常 就不打印
//   if (need_stop == true)
//   {
//     motorStop();
//     stop_printing();
//     return true;
//   }
//   // 4step一行

//   // 转动一圈
//   motorRun();
//   // 单通道打印
//   run_stb(stbnum);
//   // 再转动3圈 就刚刚好是一行的高度
//   motorRunStep(3);
//   return false;
// }

// /**
//  * @brief 单通道数组打印
//  *
//  * @param stbnum
//  * @param data
//  * @param len
//  */
// void start_printing_by_onestb(uint8_t stbnum, uint8_t *data, uint32_t len)
// {
//   uint32_t offset = 0;
//   uint8_t *ptr = data;
//   bool need_stop = false;
//   // LAT设置为高 VH电源设置为高
//   init_printing();
//   while (1)
//   {
//     Serial.printf("printer %d\n", offset);
//     if (len > offset)
//     {
//       // 发送一行数据 48byte*8=384bit
//       // 一次发48个byte
//       // ptr 就是数据
//       send_one_line_data(ptr);
//       // 每次偏移48Byte,直至所有数据发送完成
//       offset += 48;
//       ptr += 48;
//     }
//     else
//       need_stop = true;

//     // move_and_start_std 用于打印
//     if (move_and_start_std(need_stop, stbnum))
//       break;
//     // if(printing_error_check(false))
//     //     break;
//   }
//   // 打印完成，就再往后滚动几步
//   motorRunStep(40);
//   // 电机停止
//   motorStop();
// }

// static void setDebugData(uint8_t *print_data)
// {
//   for (uint32_t index = 0; index < 48 * 5; ++index)
//   {
//     // 0X55 = 0101 0101 0为白，1为黑
//     print_data[index] = 0x55;
//   }
// }

// void testSTB()
// {
//   // 每行48byte=>1byte=8bit=>48*8=384bit   打印机有384bit
//   // 48*5=5行
//   uint8_t print_data[48 * 5];
//   uint32_t print_len;
//   Serial.println("开始打印打印头选通引脚测试\n顺序: 1  2  3  4  5  6");
//   print_len = 48 * 5;
//   // 设置打印的数据内容
//   setDebugData(print_data);
//   // 通道0打印5行
//   start_printing_by_onestb(0, print_data, print_len);
//   setDebugData(print_data);
//   // 通道1打印5行
//   start_printing_by_onestb(1, print_data, print_len);
//   setDebugData(print_data);
//   start_printing_by_onestb(2, print_data, print_len);
//   setDebugData(print_data);
//   start_printing_by_onestb(3, print_data, print_len);
//   setDebugData(print_data);
//   start_printing_by_onestb(4, print_data, print_len);
//   setDebugData(print_data);
//   start_printing_by_onestb(5, print_data, print_len);
//   Serial.println("测试完成");
// }

// void init_printer()
// {
//   // 初始化电机IO
//   initMotor();
//   // 初始化数据引脚、通道引脚
//   pinMode(PIN_LAT, OUTPUT);
//   pinMode(PIN_SCK, OUTPUT);
//   pinMode(PIN_SDA, OUTPUT);
//   pinMode(PIN_STB1, OUTPUT);
//   pinMode(PIN_STB2, OUTPUT);
//   pinMode(PIN_STB3, OUTPUT);
//   pinMode(PIN_STB4, OUTPUT);
//   pinMode(PIN_STB5, OUTPUT);
//   pinMode(PIN_STB6, OUTPUT);
//   // 加热通道全部关闭
//   set_stb_idle();
//   // 初始化打印电源控制引脚、并关闭电源
//   pinMode(PIN_VHEN, OUTPUT);
//   digitalWrite(PIN_VHEN, LOW);
//   // 初始化SPI
//   init_spi();
// }
// #endif

// // 打印模块止

// // 多任务
// /**
// 需求：主函数5s运行一次，上报状态1s运行一次，按键检测2s运行一次
// void loop() {
//   delay(5000);
//   Serial.printf("main loop\n");
// }
// 如果都把代码放到loop，则需要多余的各种状态进行计算切换，代码会很臃肿，如果遇到耗时任务，也会导致时间不准
//  */

// void task_report(void *pvParameters)
// {
//   // for (;;) 是一个无限循环的语句，等价于 while(true)。

//   for (;;)
//   {
//     vTaskDelay(1000);
//     Serial.printf("task report loop\n");
//   }
// }

// void task_button(void *pvParameters)
// {
//   for (;;)
//   {
//     vTaskDelay(2000);
//     Serial.printf("task button loop\n");
//   }
// }

// void init_task()
// {
//   // freertos 提供的任务函数
//   xTaskCreate(
//       task_report,  // 任务函数  可以理解为loop 函数
//       "TaskReport", // 任务名 任意名称都行
//       1024 * 10,    // 定义数组时，不能超过这个堆栈的大小  任务栈，根据任务内使用的空间评估，例如任务中有一个10000个字节的数组，那空间最好选择10000+10000*50%
//       NULL,         // 任务参数
//       1,            // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
//       NULL          // 任务句柄
//   );

//   xTaskCreate(
//       task_button,  // 任务函数
//       "TaskButton", // 任务名
//       1024 * 5,     // 任务栈
//       NULL,         // 任务参数
//       0,            // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
//       NULL          // 任务句柄
//   );
// }
// // 多任务 止

// // setup 函数大概率不显示，实际上是运行了的
// void setup()
// {
//   Serial.begin(115200);
//   Serial.print("init steup\n");
//   // initButton();

//   // 初始化蓝牙
//   // initBle();

//   // 初始化VH 为打印机做准备
//   // initVH();

//   // 初始化缺纸检测
//   // initPaperStatus();

//   // 初始化温度检测
//   // temperatrueAdcInit();

//   // 初始化 步进电机
//   // initMotor();

//   // 初始化打印头
//   // init_printer();

//   // 初始化多任务
//   // init_task();
// }

// void loop()
// {
//   // Serial.print("helloworld\n");
//   // delay(1000);

//   // testLedSetStatus(LED_LOW_BLINK);

//   // 检测是否按下/长按按钮
//   // keyCheckRun();

//   // 查看电池电量
//   // delay(1000);
//   // readBattery();

//   // 如果连入蓝牙，就会发送消息
//   // delay(5000);
//   // bleReport();

//   // 读取 缺纸检测模块状态
//   // delay(1000);
//   // readPaperStatue();

//   // 读取打印头初始化
//   //  delay(5000);
//   //  float temperatrue = getAdcTemperatrue();
//   //  Serial.printf("temperature = %f\n", temperatrue);

//   // 电机转动模块
//   // delay(5000);
//   // Serial.printf("run\n");
//   // motorRunStep(50);

//   // 测试打印头
//   // delay(5000);
//   // testSTB();

//   delay(5000);
//   // Serial.printf("main loop\n");
//   test_run();
// }