void setup_mcp(){
  mcp.begin();      // use default address 0
  mcp.pinMode(bs[0], INPUT);
  mcp.pullUp(bs[0], HIGH);
  mcp.pinMode(bs[1], INPUT);
  mcp.pullUp(bs[1], HIGH);
  mcp.pinMode(bs[2], INPUT);
  mcp.pullUp(bs[2], HIGH);
  mcp.pinMode(bs[3], INPUT);
  mcp.pullUp(bs[3], HIGH);
  mcp.pinMode(bs[4], INPUT);
  mcp.pullUp(bs[4], HIGH);
  mcp.pinMode(bs[5], INPUT);
  mcp.pullUp(bs[5], HIGH);
  mcp.pinMode(bs[6], INPUT);
  mcp.pullUp(bs[6], HIGH);
  mcp.pinMode(bs[7], INPUT);
  mcp.pullUp(bs[7], HIGH);
  lastbtnStat[0]=mcp.digitalRead(bs[0]);
  lastbtnStat[1]=mcp.digitalRead(bs[1]);
  lastbtnStat[2]=mcp.digitalRead(bs[2]);
  lastbtnStat[3]=mcp.digitalRead(bs[3]);
  lastbtnStat[4]=mcp.digitalRead(bs[4]);
  lastbtnStat[5]=mcp.digitalRead(bs[5]);
  lastbtnStat[6]=mcp.digitalRead(bs[6]);
  lastbtnStat[7]=mcp.digitalRead(bs[7]);
  mcp.pinMode(relay[0], OUTPUT);  // use the p13 LED as debugging
  mcp.pinMode(relay[1], OUTPUT);
  mcp.pinMode(relay[2], OUTPUT);
  mcp.pinMode(relay[3], OUTPUT);
  mcp.pinMode(relay[4], OUTPUT);
  mcp.pinMode(relay[5], OUTPUT);
  mcp.pinMode(relay[6], OUTPUT);
  mcp.pinMode(relay[7], OUTPUT);
}


void button1(){
   bstatek[0] = mcp.digitalRead(bs[0]);
  if (bstatek[0] && !lastbtnStat[0]){
     delay(300); // защита от дребезга
    bstatek[0] = mcp.digitalRead(bs[0]);
    if (bstatek[0])
    {
      oldState[0]=!oldState[0];    
      mcp.digitalWrite(relay[0], oldState[0]);
      client.publish(relays_topic1, String(oldState[0]).c_str(), true);
      }
  }
  lastbtnStat[0] = bstatek[0];
}
void button2(){
   bstatek[1] = mcp.digitalRead(bs[1]);
  if (bstatek[1] && !lastbtnStat[1]){
    delay(300); // защита от дребезга
    bstatek[1] = mcp.digitalRead(bs[1]);
    if (bstatek[1])
    {
      oldState[1]=!oldState[1];     
      mcp.digitalWrite(relay[1], oldState[1]);
      client.publish(relays_topic2, String(oldState[1]).c_str(), true);
    }
  }
  lastbtnStat[1] = bstatek[1];
}
void button3(){
   bstatek[2] = mcp.digitalRead(bs[2]);
  if (bstatek[2] && !lastbtnStat[2]){
    delay(300); // защита от дребезга
    bstatek[2] = mcp.digitalRead(bs[2]);
    if (bstatek[2])
    {
      oldState[2]=!oldState[2]; 
      mcp.digitalWrite(relay[2], oldState[2]);
      client.publish(relays_topic3, String(oldState[2]).c_str(), true);
    }
  }
  lastbtnStat[2] = bstatek[2];
}
void button4(){
   bstatek[3] = mcp.digitalRead(bs[3]);
  if (bstatek[3] && !lastbtnStat[3]){
    delay(300); // защита от дребезга
    bstatek[3] = mcp.digitalRead(bs[3]);
    if (bstatek[3])
    {
      oldState[3]=!oldState[3];      
      mcp.digitalWrite(relay[3], oldState[3]);
      client.publish(relays_topic4, String(oldState[3]).c_str(), true);
    }
  }
  lastbtnStat[3] = bstatek[3];
}
void button5(){
   bstatek[4] = mcp.digitalRead(bs[4]);
  if (bstatek[4] && !lastbtnStat[4])
  { 
    delay(300); // защита от дребезга
    bstatek[4] = mcp.digitalRead(bs[4]);
    if (bstatek[4])
    {
      oldState[4]=!oldState[4];      
      mcp.digitalWrite(relay[4], oldState[4]);
      client.publish(relays_topic5, String(oldState[4]).c_str(), true);
    }
  }
  lastbtnStat[4] = bstatek[4];
}
void button6(){
   bstatek[5] = mcp.digitalRead(bs[5]);
  if (bstatek[5] && !lastbtnStat[5])
  {
    delay(300); // защита от дребезга
    bstatek[5] =mcp.digitalRead(bs[5]);
    if (bstatek[5])
    {
      oldState[5]=!oldState[5];      
      mcp.digitalWrite(relay[5], oldState[5]);
      client.publish(relays_topic6, String(oldState[5]).c_str(), true);
    }
  }
  lastbtnStat[5] = bstatek[5];
}
void button7(){
   bstatek[6] = mcp.digitalRead(bs[6]);
  if (bstatek[6] && !lastbtnStat[6])
  {
    delay(300); // защита от дребезга
    bstatek[6] =mcp.digitalRead(bs[6]);
    if (bstatek[6])
    {
      oldState[6]=!oldState[6];      
      mcp.digitalWrite(relay[6], oldState[6]);
      client.publish(relays_topic7, String(oldState[6]).c_str(), true);
    }
  }
  lastbtnStat[6] = bstatek[6];
}
void button8(){
   bstatek[7] = mcp.digitalRead(bs[7]);
   if (bstatek[7] && !lastbtnStat[7])
      {
    delay(300); // защита от дребезга
    bstatek[7] = mcp.digitalRead(bs[7]);
    if (bstatek[7])
    {
      oldState[7]=!oldState[7];      
      mcp.digitalWrite(relay[7], oldState[7]);
      client.publish(relays_topic8, String(oldState[7]).c_str(), true);
    }
  }
   lastbtnStat[7] = bstatek[7];
}
