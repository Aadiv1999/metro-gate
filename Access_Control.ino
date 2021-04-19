#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
int servoPin1 = 6;
int servoPin2 = 7;

int ledpin = 13;

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  pinMode(ledpin,OUTPUT);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);

}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    servo1.writeMicroseconds(1500);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "47 6E D7 64") //enter the correct token here
  {
    Serial.println("Authorized access");
    digitalWrite(ledpin,HIGH);
    servo1.writeMicroseconds(2500);
    servo2.writeMicroseconds(2500);
    Serial.println();
    delay(2000);
  }

  else   {
    servo1.writeMicroseconds(500);
    servo2.writeMicroseconds(500);
    Serial.println(" Access denied");
    delay(2000);
  }

}
