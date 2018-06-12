#include <multi_channel_relay.h>

#define USE_8_CHANNELS (1)

Multi_Channel_Relay relay;

void setup()
{
  Serial.begin(9600);
  while(!Serial);   

   /* Scan I2C device detect device address */
  uint8_t old_address = relay.scanI2CDevice();
  if((0x00 == old_address) || (0xff == old_address)) {
    while(1);
  }

  Serial.println("Start write address");
  relay.changeI2CAddress(0x11, old_address);  /* Set I2C address and save to Flash */  
  Serial.println("End write address");

  /* Read firmware  version */
  Serial.print("firmware version: ");
  Serial.print("0x");
  Serial.print(relay.getFirmwareVersion(), HEX);
  Serial.println();
}

void loop()
{

  /** 
   *  channle: 8 7 6 5 4 3 2 1
   *  state: 0b00000000 -> 0x00  (all off)
   *  state: 0b11111111 -> 0xff  (all on)
  */  

  /* Begin Controlling Relay */ 
  Serial.println("Channel 1 on");
  relay.turn_on_channel(1);  
  delay(500);
  Serial.println("Channel 2 on");
  relay.turn_off_channel(1);
  relay.turn_on_channel(2);
  delay(500);
  Serial.println("Channel 3 on");
  relay.turn_off_channel(2);
  relay.turn_on_channel(3);  
  delay(500);
  Serial.println("Channel 4 on");
  relay.turn_off_channel(3);
  relay.turn_on_channel(4);  
  delay(500);
#if(1==USE_8_CHANNELS)  
  Serial.println("Channel 5 on");
  relay.turn_off_channel(4);
  relay.turn_on_channel(5);  
  delay(500);
  Serial.println("Channel 6 on");
  relay.turn_off_channel(5);
  relay.turn_on_channel(6);  
  delay(500);
  Serial.println("Channel 7 on");
  relay.turn_off_channel(6);
  relay.turn_on_channel(7);  
  delay(500);
  Serial.println("Channel 8 on");
  relay.turn_off_channel(7);
  relay.turn_on_channel(8);  
  delay(500);
  relay.turn_off_channel(8);
#endif

  relay.channelCtrl(CHANNLE1_BIT | 
                    CHANNLE2_BIT | 
                    CHANNLE3_BIT | 
                    CHANNLE4_BIT | 
                    CHANNLE5_BIT | 
                    CHANNLE6_BIT |
                    CHANNLE7_BIT |
                    CHANNLE8_BIT);
  Serial.print("Turn all channels on, State: ");
  Serial.println(relay.getChannelState(), BIN);
  
  delay(2000);

  relay.channelCtrl(CHANNLE1_BIT |                   
                    CHANNLE3_BIT | 
                    CHANNLE5_BIT | 
                    CHANNLE7_BIT);
  Serial.print("Turn 1 3 5 7 channels on, State: ");
  Serial.println(relay.getChannelState(), BIN);

  delay(2000);

  relay.channelCtrl(CHANNLE2_BIT | 
                    CHANNLE4_BIT | 
                    CHANNLE6_BIT |
                    CHANNLE8_BIT);
  Serial.print("Turn 2 4 6 8 channels on, State: ");
  Serial.println(relay.getChannelState(), BIN);
  
  delay(2000);


  relay.channelCtrl(0);
  Serial.print("Turn off all channels, State: ");
  Serial.println(relay.getChannelState(), BIN);
  
  delay(2000);
}