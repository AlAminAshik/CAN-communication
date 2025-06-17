// #include <Arduino.h>
// #include <CAN.h>


// void setup() {
//   Serial.begin(9600);
//   while (!Serial);
//   pinMode(PA0, INPUT_PULLUP);

//   Serial.println("CAN Sender");
//   CAN.setPins(PA3, PA4);    //CS and INT pin

//   // start the CAN bus at 500 kbps
//   if (!CAN.begin(500E3)) {
//     Serial.println("Starting CAN failed!");
//     while (1);
//   }
// }

// void loop() {
//   // send packet: id is 11 bits, packet can contain up to 8 bytes of data
//   Serial.print("Sending packet ... ");
 
//   CAN.beginPacket(0xabcdef);
//   CAN.write('a');
//   CAN.write('s');
//   CAN.write('h');
//   CAN.write('i');
//   CAN.write('k');
//   CAN.endPacket();

//   Serial.println("done");

//   delay(1000);

//   // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
//   // Serial.print("Sending extended packet ... ");

//   // CAN.beginExtendedPacket(0xabcdef);
//   // CAN.write('A');
//   // CAN.write('S');
//   // CAN.write('H');
//   // CAN.write('I');
//   // CAN.write('K');
//   // CAN.endPacket();

//   // Serial.println("done");

//   // delay(100);
// }