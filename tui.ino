/*
   color  meaning input light
   green  yes     A2    2
   red    no      A1    3
   white  pick    A3    4
   blue   place   A4    5
   yellow basket  A5    6
*/

//#define USE_USBCON
#include <ros.h>

#include <TUI_msgs/btn_state.h>
#include <TUI_msgs/led_state.h>

#define RedL 3
#define RedB A1

#define GreenL 2
#define GreenB A2

#define WhiteL 4
#define WhiteB A3

#define BlueL 5
#define BlueB A4

#define YellowL 6
#define YellowB A5

#define X A6
#define Y A7

#define Switch A0

int x, y;
int8_t btnVal[6];
int joyVal[2];
TUI_msgs::btn_state btns;

void updateLed(const TUI_msgs::led_state& led) {
  digitalWrite(RedL, led.leds[0]);
  digitalWrite(GreenL, led.leds[1]);
  digitalWrite(WhiteL, led.leds[2]);
  digitalWrite(BlueL, led.leds[3]);
  digitalWrite(YellowL, led.leds[4]);
}



ros::NodeHandle nh;
ros::Subscriber<TUI_msgs::led_state> sub("/led_state", &updateLed);
ros::Publisher btnState("btnState", &btns);

void setup() {

  nh.advertise(btnState);
  nh.subscribe(sub);

  pinMode(RedL, OUTPUT);
  pinMode(GreenL, OUTPUT);
  pinMode(WhiteL, OUTPUT);
  pinMode(BlueL, OUTPUT);
  pinMode(YellowL, OUTPUT);

  pinMode(RedB, INPUT_PULLUP);
  pinMode(GreenB, INPUT_PULLUP);
  pinMode(WhiteB, INPUT_PULLUP);
  pinMode(BlueB, INPUT_PULLUP);
  pinMode(YellowB, INPUT_PULLUP);
  pinMode(Switch, INPUT_PULLUP);

  pinMode(X, INPUT);
  pinMode(Y, INPUT);

  digitalWrite(RedL, HIGH);
  digitalWrite(GreenL, HIGH);
  digitalWrite(WhiteL, HIGH);
  digitalWrite(BlueL, HIGH);
  digitalWrite(YellowL, HIGH);

}

void loop() {
  while (1) {
    if (digitalRead(Switch)) {
      btnVal[0] = !digitalRead(RedB);
      btnVal[1] = !digitalRead(GreenB);
      btnVal[2] = !digitalRead(WhiteB);
      btnVal[3] = !digitalRead(BlueB);
      btnVal[4] = !digitalRead(YellowB);

      joyVal[0] = analogRead(X);
      joyVal[1] = analogRead(Y);

      for (int i = 0; i < 5; i++) {
        btns.button[i] = btnVal[i];
      }

      for (int i = 0; i < 2; i++) {
        btns.joy[i] = joyVal[i];
      }

      btnState.publish(&btns);
    }
  }
}
