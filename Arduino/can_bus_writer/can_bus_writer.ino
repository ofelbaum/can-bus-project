/****************************************************************************
CAN Write Demo for the SparkFun CAN Bus Shield. 

Written by Stephen McCoy. 
Original tutorial available here: http://www.instructables.com/id/CAN-Bus-Sniffing-and-Broadcasting-with-Arduino
Used with permission 2016. License CC By SA. 

Distributed as-is; no warranty is given.
*************************************************************************/

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

//********************************Setup Loop*********************************//

void setup() {
  Serial.begin(9600);
  Serial.println("CAN Write - Testing transmission of CAN Bus messages");
  delay(1000);
  
  if(Canbus.init(9))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
  delay(5000);
}

//********************************Main Loop*********************************//

void loop()
{
          int msgID = 0x130;
          int data[] = { 0x45, 0x42, 0x69, 0x8F, 0xE2, 0xFE };
          send_message(msgID, data, 6);
          
          msgID = 0x349;
          int data2[] = { 0x76, 0x0F, 0xBE, 0x1A, 0x00 };
          //send_message(msgID, data2, 5);

          msgID = 0x0C0;
          int data3[] = { 0xF4, 0xFF };
          //send_message(msgID, data3, 2);

        Serial.println("Sent");
        delay(100);
}

void send_message(int messageID, int data[], int len)
{
            tCAN message;
            message.id = messageID; //formatted in HEX
            message.header.rtr = 0;
            message.header.length = len; //formatted in DEC
            int i;
            for (i = 0; i < len; i++){
              message.data[i] = data[i];
            }
            
            mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
            mcp2515_send_message(&message);
}

void PrintHex8(uint16_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
     char tmp[16];
       for (int i=0; i<length; i++) { 
         sprintf(tmp, "0x%.2X",data[i]); 
         Serial.print(tmp); Serial.print(" ");
       }
}

