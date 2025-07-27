// CAN Master Example

//connection
//stm32f411 blackpill-----------MCP2515
//5V --------------- 5V
//GND -------------- GND    
//A5 ------------- SCK
//A6 ------------- MISO   
//A7 ------------- MOSI
//A3 ------------- CS (Chip Select)


#include <mcp_can.h>      //add the can library
#include <SPI.h>          //add SPI communication

long unsigned int rxId;   //varibale to store the slave address when responded
unsigned char len = 0;    //varibale to store the length of data sent by slave
unsigned char rxBuf[7];   //varibale to store the data bytes send by the slaves

char msgString[128];      // Array to store serial string
int receivedIndex = 0;    // Current write index


#define CAN0_INT PA8        // Set INT to pin PA8
MCP_CAN CAN0(PA4);         // Set CS to pin PA4


void askSlave(uint16_t Addresss){
  byte sndStat1 = CAN0.sendMsgBuf(Addresss, 0, 1, (byte*)1); //request with address through the bus //len should be equal to data

  if (sndStat1 == CAN_OK) {
    Serial.println("Message Sent!");    //message sent without any error (line is OK)
  } else {
    Serial.println("Error Sending Frames..."); //if there is something wrong with can bus
  }
}

void responseFromSlave(){
    //when any particular slave responds
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

    sprintf(msgString, "Standard ID: 0x%.3lX length: %d ", rxId, len);
    Serial.print(msgString); //print ID and length of data
  
    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } 
    else if(rxId == 0x100){             // Check if the message is from the slave with address 0x100
      for(int i = 0; i<len; i++){
        msgString[receivedIndex++] = (byte)rxBuf[i]; // Store received data in msgString
      }
      msgString[receivedIndex] = '\0'; // Null-terminate the string
      Serial.print("Data: "); // Print the received data string

      for (int i = 0; i < len; i++) {
        Serial.print((char)rxBuf[i]); // Print each byte of data by converting it to char
      }
      Serial.println(); // Print a newline after the data
    }
    else{
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);    //print the data in bytes
    }
  }
}


void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);     // Configuring pin for /INT input //this is low when the line is active (someone is seeking data)
}

void loop()
{
  Serial.println("Asking First Slave.");
  askSlave(0x100);                      //asking from first slave with address 0x100
  delay(10);                            //important otherwise data will propagate by one step.
  if(!digitalRead(CAN0_INT))            // If CAN0_INT pin is low, read receive buffer
  {
    Serial.println("Slave responded");
    responseFromSlave();
  }
  else Serial.println("Slave did not respond.");
  delay(2000);                          // wait for 2 seconds before asking again
  Serial.println();


  
  Serial.println("Asking second Slave.");
  askSlave(0x200);                      //asking from second slave with address 0x200
  delay(10);
  if(!digitalRead(CAN0_INT))            // If CAN0_INT pin is low, read receive buffer
  {
    Serial.println("Slave responded");
    responseFromSlave();
  }
  else Serial.println("Slave did not respond.");
  delay(2000);                          // wait for 2 seconds before asking again
  Serial.println();



  Serial.println("Asking Third Slave.");
  askSlave(0x300);                      //asking from third slave with address 0x300
  delay(10);
  if(!digitalRead(CAN0_INT))            // If CAN0_INT pin is low, read receive buffer
  {
    Serial.println("Slave responded");
    responseFromSlave();
  }
  else Serial.println("Slave did not respond.");
  delay(2000);
  Serial.println();
  //Repeat
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/