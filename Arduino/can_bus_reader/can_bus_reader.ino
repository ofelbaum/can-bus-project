/****************************************************************************
CAN Read Demo for the SparkFun CAN Bus Shield. 

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

byte incomingByte;
char message[255] = {};
int index = 0;
int messageId;

//********************************Setup Loop*********************************//

void setup() {
  Serial.begin(9600); // For debug use
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  delay(1000);
  
  if(Canbus.init(9))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
  delay(1000);
}

//********************************Main Loop*********************************//

void loop(){
//  printBuffer();
  initFilter();
  tCAN message;
if (mcp2515_check_message()) 
  {
    if (mcp2515_get_message(&message)) 
    {
        if(message.id == messageId || messageId == NULL)
        {
               
               Serial.print("ID: ");
               Serial.print(message.id,HEX);
               Serial.print(", ");
               Serial.print("Data [");
               Serial.print(message.header.length,DEC);
               Serial.print(" bytes]: ");
               for(int i=0;i<message.header.length;i++) 
                { 
                  Serial.print(message.data[i],HEX);
                  Serial.print(" ");
                }
               Serial.println("");
        }
     }
  }
}

void initFilter() {
if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if ((int)incomingByte == 10) {
        // ignore space
    } else if ((char)incomingByte == '!') {
        memset(message, 0, sizeof(message));
        index = 0;
        messageId = NULL;
        Serial.println("=============================");
        Serial.println("=== Filter disabled =========");
        Serial.println("=============================");
    } else if ((char)incomingByte == '*') {
        message[index] = '\0';
        sscanf(message, "%x", &messageId);

        memset(message, 0, sizeof(message));
        index = 0;
        Serial.println("=== Filter enabled ==============");
        Serial.print("=== Filter on message ID: ");
        Serial.print(messageId, HEX);
        Serial.println(" ===");
        Serial.println("===============================");
    } else {
        message[index] = (char)incomingByte;
        index++;
    }    
  }  
}

void printBuffer() {
  int i;
  for(i = 0; i < sizeof(message); i++) {
    Serial.print(message[i]);
    }
    Serial.println();
}
