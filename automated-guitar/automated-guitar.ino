
int nE3   = A0;
int nF3   = A1;
int nFS3  = A2;
int nG3   = A3;
int nA4   = A4;
int nBb4  = A5;


  

void setup() {
  //  Set MIDI baud rate:
  Serial.begin(31250);
  //Serial.begin(115200);
  pinMode(nE3, OUTPUT);
  pinMode(nF3, OUTPUT);
  pinMode(nFS3,OUTPUT);
  pinMode(nG3, OUTPUT);
  pinMode(nA4, OUTPUT);
  pinMode(nBb4,OUTPUT);

  digitalWrite(nE3,LOW);
  digitalWrite(nF3,LOW);
  digitalWrite(nFS3,LOW);
  digitalWrite(nG3,LOW);
  digitalWrite(nA4,LOW);
  digitalWrite(nBb4,LOW);
}

int doHit(int note)
{
  digitalWrite(note,HIGH);
  delay(50);
  digitalWrite(note,LOW);
}

void loop() {
  /*
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
//    noteOn(0x90, note, 0x00);   
    delay(100);
  }
  */
  
  int note = 0;
//  int low = 90; // desired edge of servo (0 - 180)
//  int high = 80; // other desired edge of servo (0 - 180)

  int servoDelay = 50; //desired delay between servo rotation

  
  if (Serial.available() > 0) 
  {
     int velos = 0;
     int FLAG_NOTE_PRESSED = 0;

     
     while(Serial.available() > 0)
     {
      int FLAG_NO_NOTE = 1;

      while(1 == FLAG_NO_NOTE)        /// No note flag
      {
        while(Serial.available() > 0)  /// Keep reading
        {
          note = Serial.read();
          if(((byte)note >= 0x90) & ((byte)note <= 0x9F))
          {
            while(Serial.available() == 0);
            byte note2 = Serial.read();
            while(Serial.available() == 0);
            byte velos2 = Serial.read();
            FLAG_NOTE_PRESSED = 1;
            //Serial.println(note2, HEX);
            FLAG_NO_NOTE = 0;


            int val = map(note2*4, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
            //myservo.write(val);                  // sets the servo position according to the scaled value
            
            if (note2 == 0x40) doHit(nE3);
            else if (note2 == 0x41) doHit(nF3);
            else if (note2 == 0x42) doHit(nFS3);
            else if (note2 == 0x43) doHit(nG3);
            else if (note2 == 0x44) doHit(nA4);
            else if (note2 == 0x45) doHit(nBb4);
            
            while(Serial.available()){  // Flush all remaining notes in queue 
              Serial.read();
            }
            
            break;
          }
        }
      }
     }
      delay(20);
  }
  
}
//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.print(cmd);
  Serial.print(pitch);
  Serial.print(velocity);
}



