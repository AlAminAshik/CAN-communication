// // CAN Send Example
// //

// #include <mcp_can.h>
// #include <SPI.h>

// MCP_CAN CAN0(PA3);     // Set CS to pin 10
// #define CAN0_INT PA4   // Set INT to pin 2

// void setup()
// {
//   Serial.begin(115200);

//   // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
//   if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) 
//     Serial.println("MCP2515 Initialized Successfully!");
//   else 
//     Serial.println("Error Initializing MCP2515...");

//   CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
// }

// const char msg[] = "Al Amin";   // 7 bytes of data
// //byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

// void loop() {
//     //support maximum 8 bytes of data
//     byte sndStat1 = CAN0.sendMsgBuf(0x100, 0, 7, (byte*)msg); //len should be equal to data

//   if (sndStat1 == CAN_OK) {
//     Serial.println("Message Sent!");
//   } else {
//     Serial.println("Error Sending Frames...");
//   }

//   delay(1000);
// }

// /*********************************************************************************************************
//   END FILE
// *********************************************************************************************************/