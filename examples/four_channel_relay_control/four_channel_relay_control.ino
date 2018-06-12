#include <multi_channel_relay.h>

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
  relay.turn_off_channel(8);

  relay.channelCtrl(CHANNLE1_BIT | 
                    CHANNLE2_BIT | 
                    CHANNLE3_BIT | 
                    CHANNLE4_BIT);
  Serial.print("Turn all channels on, State: ");
  Serial.println(relay.getChannelState(), BIN);
  
  delay(2000);

  relay.channelCtrl(CHANNLE1_BIT |                   
                    CHANNLE3_BIT);
  Serial.print("Turn 1 3 channels on, State: ");
  Serial.println(relay.getChannelState(), BIN);

  delay(2000);

  relay.channelCtrl(CHANNLE2_BIT | 
                    CHANNLE4_BIT);
  Serial.print("Turn 2 4 channels on, State: ");
  Serial.println(relay.getChannelState(), BIN);
  
  delay(2000);


  relay.channelCtrl(0);
  Serial.print("Turn off all channels, State: ");
  Serial.println(relay.getChannelState(), BIN);
  
  delay(2000);
}