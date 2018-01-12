#include <SPI.h>
#include <MFRC522.h>
 
#define SS 10
#define RST 2

String content;
byte letter;
  
MFRC522 RFID(SS, RST);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  
  SPI.begin();      // Initiate  SPI bus
  
  RFID.PCD_Init();   // Initiate MFRC522
  
  //Serial.println("Approximate your card to the reader...");
  //Serial.println();

}


void loop() 
{
  content = "";
  
  // Look for new cards
  if ( !(RFID.PICC_IsNewCardPresent())) 
  {
    return;
  }
  
  // Select one of the cards
  if ( !(RFID.PICC_ReadCardSerial()))
  {
    return;
  }
  
  //Show UID on serial monitor
  //Serial.print("UID tag :");

  
  //loop for printing UID
  
  for (byte i = 0; i < RFID.uid.size; i++) 
  {
     Serial.print(RFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(RFID.uid.uidByte[i], HEX);
     content.concat(String(RFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(RFID.uid.uidByte[i], HEX));
  }
  
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  // Our UID
  if (content.substring(1) == "AC E4 94 35") //change here the UID of the card/cards that you want to give access
  {
    
    Serial.println("Hello Galal!\n");
    delay(1000);
  }
 
 else if (content.substring(1) == "76 2B 19 7E")
 {
    Serial.println("Hello Mido!\n");
    delay(1000);
 }

 else
 {
  Serial.println("Denied Access!\n");
  Serial.println("Dialling 911...\n");
  delay(1000);
 }
} 
