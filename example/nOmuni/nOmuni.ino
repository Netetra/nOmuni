#include <Arduino.h>
#include <PS4Controller.h>
#include <MD30C_ESP32.h>
#include <nOmuni.h>

#define DEADZONE 10
#define N 3

nOmuni Omunis[N] = { nOmuni(PI*2/3), nOmuni(PI*4/3), nOmuni(PI*2) };
uint8_t dir_pins[N] = { 14, 26, 33 };
uint8_t pwm_pins[N] = { 27, 25, 32 };
MD30C Moters[N] = { MD30C(0, pwm_pins[0], dir_pins[0]), MD30C(1, pwm_pins[1], dir_pins[1]), MD30C(2, pwm_pins[2], dir_pins[2]) };

void setup() {
  Serial.begin(9600);
  uint8_t bt_mac[6];
  esp_read_mac(bt_mac, ESP_MAC_BT);
  Serial.printf("Bluetooth MAC Address >> %02X:%02X:%02X:%02X:%02X:%02X\r\n", bt_mac[0], bt_mac[1], bt_mac[2], bt_mac[3], bt_mac[4], bt_mac[5] );
  PS4.begin("C0:49:EF:E4:B1:9A");
  
  for (uint8_t i = 0; i < N; i++) {
    pinMode(dir_pins[i], OUTPUT);
    Moters[i].init();
  }
}

void loop() {
  //接続まで待つ
  Serial.println("Connect Waiting...");
  while (!PS4.isConnected()) {}
  Serial.println("PS4 Controller Connected.");
  //再起動防止のdelay
  delay(1000);

  while (PS4.isConnected()) {
    int8_t Lx = PS4.LStickX();
    int8_t Ly = PS4.LStickY() * -1;
    if (abs(Lx) > DEADZONE || abs(Ly) > DEADZONE) {
      for (uint8_t i = 0; i < N; i++) {
        int16_t omuniPower = floor(Omunis[i].OmuniPower(Lx, Ly));
        if (omuniPower > 0) {
          Moters[i].forward(omuniPower);
        } else if (omuniPower < 0) {
          Moters[i].back(-1 * omuniPower);
        } else {
          Moters[i].stop();
        }
      }
    } else {
      for (uint8_t i = 0; i < N; i++) {
        Moters[i].stop();
      }
    }
  }
}
