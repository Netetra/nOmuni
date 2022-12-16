#include <Arduino.h>
#include <PS4Controller.h>
#include <MD30C_ESP32.h>
#include <nOmuni.h>

#define DEADZONE 10
#define N 3

nOmuni Omunis[3] = { nOmuni(PI*2/3), nOmuni(PI*4/3), nOmuni(PI*2) };
MD30C Moters[3] = { MD30C(0, 27, 14), MD30C(1, 25, 26), MD30C(2, 32, 33) };

void setup() {
  Serial.begin(9600);
  uint8_t bt_mac[6];
  esp_read_mac(bt_mac, ESP_MAC_BT);
  Serial.printf("Bluetooth MAC Address >> %02X:%02X:%02X:%02X:%02X:%02X\r\n", bt_mac[0], bt_mac[1], bt_mac[2], bt_mac[3], bt_mac[4], bt_mac[5] );
  PS4.begin("40:22:D8:EB:36:5E");
  
  for (uint8_t i = 0; i < 3; i++) {
    Moters[i].init();
  }
}

void loop() {
  //接続まで待つ
  while (!PS4.isConnected()) {}
  Serial.println("PS4 Controller Connected.");
  //再起動防止のdelay
  delay(1000);

  while (PS4.isConnected()) {
    int8_t Lx = PS4.LStickX();
    int8_t Ly = PS4.LStickY();
    if (abs(Lx) > DEADZONE || abs(Ly) > DEADZONE) {
      for (uint8_t i = 0; i < 3; i++) {
        int16_t omuniPower = floor(Omunis[i].OmuniPower(Lx, Ly));
        if (omuniPower > 0) {
          Moters[i].forward(omuniPower);
        } else if (omuniPower < 0) {
          Moters[i].back(-1 * omuniPower);
        }
      }
    } else {
      for (uint8_t i = 0; i < 3; i++) {
        Moters[i].stop();
      }
    }
  }
}
