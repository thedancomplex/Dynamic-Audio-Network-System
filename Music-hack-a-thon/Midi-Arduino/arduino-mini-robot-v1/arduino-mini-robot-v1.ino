void setup() {
  //  Set MIDI baud rate:
  Serial1.begin(31250);
  Serial.begin(115200);
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

  if (Serial1.available() > 0) 
  {
     int velos = 0;
     int FLAG_NOTE_PRESSED = 0;
     
     while(Serial1.available() > 0)
     {
      note = Serial1.read();
      Serial.println(note, HEX);
/*
      if(((byte)note >= 0x90) & ((byte)note <= 0x9F))
      {
        note = Serial1.read();
        //Serial.println((byte)note, HEX);
        velos = Serial1.read();
        //Serial.println((byte)note, HEX);
        FLAG_NOTE_PRESSED = 1;
      }
      else
      {
        Serial1.read();
      }

     }
     //note  = Serial.read();
     if(FLAG_NOTE_PRESSED == 1)
     {
       Serial.println((byte)note, HEX);
       //Serial.println((byte)velos, HEX);
     }
     FLAG_NOTE_PRESSED = 0;
     note = 0x65;
      delay(10);
     noteOn(0x90, note, 0x45);
      delay(10);
      */
     }
      delay(20);
  }
  
}
//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn2(int cmd, int pitch, int velocity) {
  Serial.print(cmd);
  Serial.print(pitch);
  Serial.print(velocity);
}


//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial1.print(cmd);
  Serial1.print(pitch);
  Serial1.print(velocity);
}
