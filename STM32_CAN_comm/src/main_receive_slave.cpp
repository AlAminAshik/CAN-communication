// CAN Send Example

// connection
// stm32f103 bluepill-----------MCP2515
// 5V --------------- 5V
// GND -------------- GND
// A5 ------------- SCK
// A6 ------------- MISO
// A7 ------------- MOSI
// A4 ------------- CS (Chip Select)

#include <mcp_can.h>
#include <SPI.h>
#include <U8g2lib.h>    // Graphics library for monochrome displays

uint16_t myAddress = 0x100;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[7];

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, PA3);

MCP_CAN CAN0(PA4);  // Set CS to pin PA4
#define CAN0_INT PA8 // Set INT to pin PA8

const char myString[] = "Hi"; // 2 bytes of data

// run when interrupt is triggered
void canInterrupt()
{
  Serial.println("CAN Interrupt Triggered!");
  if (!digitalRead(CAN0_INT)) // If CAN0_INT pin is low, read receive buffer
  {
    Serial.print("Master is asking data ");
    CAN0.readMsgBuf(&rxId, &len, rxBuf); // Read data: len = data length, buf = data byte(s)
    if (rxId == myAddress)
    {
      Serial.println("from Me!!");

      // send only button state (0 or 1)///
        byte sndStat1 = CAN0.sendMsgBuf(myAddress, 0, 2, (byte*)&myString); //address, data length, data pointer
        Serial.println("I sent data with my address 0x100");
        if (sndStat1 == CAN_OK) {
           Serial.println("Message Sent properly!");
           } else {
           Serial.println("Error Sending Frames...");
           }
       }

    else
      Serial.println("from someone else!");
  }
}

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);                                                // Change to normal mode to allow messages to be transmitted
  attachInterrupt(digitalPinToInterrupt(CAN0_INT), canInterrupt, FALLING); // Attach interrupt to CAN0_INT pin
  // pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input

  u8g2.begin(); // Initialize the display
}

void loop()
{
      u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_8x13B_tr); // Large bold font
        u8g2.setCursor(5, 25);
        u8g2.print("Steeltech");
        u8g2.setCursor(4, 40);
        u8g2.print("Industries");
        u8g2.setCursor(5, 55);
        u8g2.print("Limited");
    } while (u8g2.nextPage());
    delay(1000); // Delay to allow the display to refresh
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/