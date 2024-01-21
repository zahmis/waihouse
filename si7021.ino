// #include <wire.h>
// #define SI7021_addr 0x40
// #define SI7021_TEMP_HOLD 0xE3
// #define SI7021_HUMD_NOHOLD 0xF3
// #define SI7021_RH_HOLD 0xE5
// #define SI7021_RH_NOHOLD 0xF5
// #define SI7021_RESET 0xFE

#include <wifi.h>
#include <Adafruit_Si7021.h>
#include <Ambient.h>

const char* ssid = "FS030W_P76348";
const char* password = "******************";

WifiClient wifi;
Ambient ambient;

unsigned int channelId = 60830;
const char* writeKey = "e797227f8bbc5661";

Adafruit_Si7021 si7021 = Adafruit_Si7021(); // インスタンスを作成

// void reset(void){
//     Wire.beginTransmission(SI7021_addr); // コマンド送信準備
//     Wire.write(SI7021_RESET);　// 送信するコマンドをキューイング
//     Wire.endTransmission(); // キューイングしたコマンドを送信
//     delay(100);
// }

// float readHumidity(void){
//     Wire.beginTransmission(SI7021_addr);
//     Wire.write(SI7021_RH_NOHOLD);
//     Wire.endTransmission(); // 湿度を取得するコマンドを送信

//     while (true){
//         if(Wire.requestForm(SI7021_addr, 3) == 3){ // 3バイトのデータが返却されたら実行
//             unit16_t hum = Wire.read() << 8 | Wire.read(); データを読む
//             unit8_t chxsum = Wire.read();
//             return hum * 125.0 / 65536.0 - 6.0;
//         }
//         delay(6)
//     }
// }

// float readTemperature(void){
//     Wire.beginTransmission(SI7021_addr);
//     Wire.write(SI7021_TEMP_NOHOLD);
//     Wire.endTransmission(); // 湿度を取得するコマンドを送信

//     while (true){
//         if(Wire.requestForm(SI7021_addr, 3) == 3){
//             unit16_t temp = Wire.read() << 8 | Wire.read();
//             unit8_t chxsum = Wire.read();
//             return temp * 125.0 / 65536.0 - 6.0;
//         }
//         delay(6)
//     }
// }

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Wifi.begin(ssid, password);
  while(Wifi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("wifi connected!");
  Serial.println("IP address: ");
  Serial.println(Wifi.localIP());

  ambient.begin(channelId, writeKey, &wifi);
  if(!si7021.begin()){
    Serial.println("Could not find a valid SI7021 sensor, check wiring!");
    while(1);
  }
}

void loop() {
  float temp = si7021.readTemperature();
  float hum = si7021.readHumidity();

  Serial.printf("Humidity: %.2f, temp: %.2f/r/n", hum, temp);

  ambient.set(1, hum);
  ambient.set(2, temp);
  ambient.send();
  delay(60*1000);
}