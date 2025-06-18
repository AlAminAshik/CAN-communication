// CAN Send Example as a slave
//

#include <mcp_can.h>      //add the can library
#include <SPI.h>        //add the SPI library/

uint16_t myAddress = 0x100; // Set the address of this node (must be unique in the network)

long unsigned int rxId;   // Used to store the received CAN ID
unsigned char len = 0; // Used to store the length of the received data
unsigned char rxBuf[7]; // Buffer to store the received data

//these two should be interrupt pins
MCP_CAN CAN0(PA3);     // Set CS to pin PA3
#define CAN0_INT PA4   // Set INT to pin PA4

#define Button_pin PA0  // Set the pin for the button as an example

void setup()
{
  Serial.begin(115200);
  pinMode(Button_pin, INPUT_PULLUP);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) 
    Serial.println("MCP2515 Initialized Successfully!");
  else 
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
  pinMode(CAN0_INT, INPUT);   // Configuring pin for /INT input
}

//const char msg[] = "Al Amin";   // 7 bytes of data
//byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
bool SwitchData;    //store the button state

void loop() {
    if(digitalRead(Button_pin) == LOW){
     SwitchData = 1;        //button is pressed
    }
    else SwitchData = 0;    //button is unpressed

    //support maximum 8 bytes of data
  if(!digitalRead(CAN0_INT))                  // If CAN0_INT pin is low, someone is querring data, read receive buffer
  {
    Serial.print("Master is asking data ");
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    if(rxId == myAddress){
     Serial.println("from Me!!");

     byte sndStat1 = CAN0.sendMsgBuf(myAddress, 0, 1, (byte*)SwitchData); //send data with address //len should be equal to data
     Serial.println("I sent data with my address 0x100");
     if (sndStat1 == CAN_OK) {
        Serial.println("Message Sent properly!");
        } else {
        Serial.println("Error Sending Frames...");
        }
    }
    else Serial.println("from someone else!");
  }

  //delay(100);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/