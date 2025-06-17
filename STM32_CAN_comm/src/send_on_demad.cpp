// #include <CAN.h>
// char Comman_Data;

// void onReceive(int packetSize) {
//   // received a packet
//     Serial.print("Data requested from: ");
//     Serial.println(CAN.packetId(), HEX);

//     //print what was sent
//     while (CAN.available()) {
//     Serial.print((char)CAN.read());
//     Comman_Data = (char)CAN.read();
//     }
//     Serial.println();
    
//     if(Comman_Data == '1'){
//         Serial.println("Sending Data");
//         if(digitalRead(PA0) == LOW){
//             CAN.beginPacket(1);
//             CAN.write('Pressed');
//             CAN.endPacket();
//             delay(10);
//         }
//         else{
//             CAN.beginPacket(1);
//             CAN.write('Unpressed');
//             CAN.endPacket();
//             delay(10);
//         }
//         Serial.println("DONE");
//         delay(1000);
//     }
// }

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);
//   CAN.setPins(PA3, PA4);    //CS and INT pin
//   pinMode(PA0, INPUT_PULLUP);

//   // start the CAN bus at 500 kbps
//   if (!CAN.begin(500E3)) {
//     Serial.println("Starting CAN failed!");
//     while (1);
//   }

//   // register the receive callback
//   CAN.onReceive(onReceive);
// }

// void loop() {
//   // do nothing
// }
