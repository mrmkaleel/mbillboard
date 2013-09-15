#include <ATTCloudClient.h>
#include "Timer.h"
// include the library code:
#include <LiquidCrystal.h>

// Longest variable is 32 chars
PROGMEM const prog_uchar   M2MIO_USERNAME[]    = "team2@att.com";
PROGMEM const prog_uchar   M2MIO_PASSWORD[]    = "ff414b86c1e821404958cb97338e3324";
PROGMEM const prog_uchar  M2MIO_DOMAIN[]       = "22be505a5531d134728568e94685e53c";
PROGMEM const prog_uchar  M2MIO_DEVICE_TYPE[]  = "team2";
PROGMEM const prog_uchar  M2MIO_DEVICE_ID[]    = "qas01";

#define REPORTING_INTERVAL_MS  3000

ATTCloudClient acc;
ATT3GModemClient c;

Timer t;

const int TrigPin = 2;
const int EchoPin = 3;
float cm;

int sensorPin = A0;   // Sensing voltage on analog pin 0
int sensorValue = 0;  // sensor reading

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len);

int potPin = 0 ;

void dispMessage(char* msg) {
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");  
  String m = String(msg);
  if (m.length() > 16) {
  String m1 = m.substring(0,16);
  String m2 = m.substring(16);
  lcd.setCursor(0,0);
  lcd.print(m1);
  lcd.setCursor(0,1);
  lcd.print(m2);
  } else {
  lcd.setCursor(0,0);    
  lcd.print(m);
  }
}

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  while(!Serial1);
  delay(1500);

  Serial.begin(9600); // port to communicate to PC
  Serial1.begin(115200); // port that talks to 3G modem

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  Serial.println(F("mBillBoard Starting ..."));
  
  dispMessage("mBillBoard Ready");

  c = ATT3GModemClient();
  acc = ATTCloudClient(cmdCallBack,c);

  if (!acc.connect(M2MIO_DEVICE_ID,M2MIO_USERNAME,M2MIO_PASSWORD) ) {
   Serial.println(F("Unable to connect to network (12)"));
    //return;
  }

  acc.setDomainStuffThing(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID);

  acc.registerForCommands();
  
  int sensorEvent = t.every(REPORTING_INTERVAL_MS, getSensorValue);
}

void loop() {
  delay(200);
  acc.loop();
  t.update();
}

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len) {
  Serial.println(F("In the cmdCallBack()"));
  Serial.println((char*)payload);
  /*lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print((char*)payload);*/
  
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");  
  String m = String((char*)payload);
  if (m.length() > 16) {
  String m1 = m.substring(0,16);
  String m2 = m.substring(16);
  String m3 = m2.substring(0,16);
  lcd.setCursor(0,0);
  lcd.print(m1);
  lcd.setCursor(0,1);
  lcd.print(m3);
  } else {
  lcd.setCursor(0,0);    
  lcd.print(m);
  }
    acc.setDomainStuffThing(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID);

  acc.registerForCommands();

  //dispMessage((char*)payload);
}

void getSensorValue() {
  /*int dat;
  Serial.println(F("sensor read"));

  // read value from sensor
  sensorValue = analogRead(sensorPin);    
  dat = (125*sensorValue)>>8;
  Serial.print("Tep: ");
  Serial.print(dat);
  Serial.println("C");
  */
  
  /*digitalWrite(TrigPin, LOW); //Low high and low level take a short time to TrigPin pulse
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  cm = pulseIn(EchoPin, HIGH) / 58.0; //Echo time conversion into cm
  dat = (int(cm * 100.0)) / 100.0; //Keep two decimal places
  Serial.print(dat);
  Serial.print("cm");
  Serial.println();

*/
/*
  acc.sendKV("sensor_val", dat);*/
}
