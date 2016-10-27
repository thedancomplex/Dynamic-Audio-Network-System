//Taimur Sohrab, Kishn Parbadia 10/20/2016   -- Worked on making note C (0x40) bring servo between two ranges
                                           //-- also implemented flushing the notes to prevent key presses
                                           //-- from backing up the servo

#include <Servo.h>


Servo myservo0;  // create servo object to control a servo
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
Servo myservo5;  // create servo object to control a servo

int low0 = 80; // desired edge of servo (0 - 180)
int high0 = 70; // other desired edge of servo (0 - 180)
int low1 = 84; // desired edge of servo (0 - 180)
int high1 = 74; // other desired edge of servo (0 - 180)
int low2 = 90; // desired edge of servo (0 - 180)
int high2 = 80; // other desired edge of servo (0 - 180)
int low3 = 84; // desired edge of servo (0 - 180)
int high3 = 74; // other desired edge of servo (0 - 180)
int low4 = 90; // desired edge of servo (0 - 180)
int high4 = 80; // other desired edge of servo (0 - 180)
int low5 = 86; // desired edge of servo (0 - 180)
int high5 = 76; // other desired edge of servo (0 - 180)
  

void setup() {
  //  Set MIDI baud rate:
  Serial1.begin(31250);
  Serial.begin(115200);

  // Servo Setup
  myservo0.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo0.write(low0); //initial value for servo angle

  myservo1.attach(5);  // attaches the servo on pin 9 to the servo object
  myservo1.write(low1); //initial value for servo angle

  myservo2.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo2.write(low2); //initial value for servo angle

  myservo3.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo3.write(low3); //initial value for servo angle

  myservo4.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo4.write(low4); //initial value for servo angle

  myservo5.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo5.write(low5); //initial value for servo angle
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

  
  if (Serial1.available() > 0) 
  {
     int velos = 0;
     int FLAG_NOTE_PRESSED = 0;

     
     while(Serial1.available() > 0)
     {
      int FLAG_NO_NOTE = 1;

      while(1 == FLAG_NO_NOTE)        /// No note flag
      {
        while(Serial1.available() > 0)  /// Keep reading
        {
          note = Serial1.read();
          if(((byte)note >= 0x90) & ((byte)note <= 0x9F))
          {
            while(Serial1.available() == 0);
            byte note2 = Serial1.read();
            while(Serial1.available() == 0);
            byte velos2 = Serial1.read();
            FLAG_NOTE_PRESSED = 1;
            //Serial.println(note2, HEX);
            FLAG_NO_NOTE = 0;


            int val = map(note2*4, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
            //myservo.write(val);                  // sets the servo position according to the scaled value
            
            if (note2 == 0x40){  // C flat played
                myservo0.write(low0);
                delay(servoDelay);
                myservo0.write(high0);
                delay(servoDelay);
                myservo0.write(low0);    
            }

            else if (note2 == 0x41){  // C flat played
                myservo1.write(low1);
                delay(servoDelay);
                myservo1.write(high1);
                delay(servoDelay);
                myservo1.write(low1);    
            }
            else if (note2 == 0x42){  // C flat played
                myservo2.write(low2);
                delay(servoDelay);
                myservo2.write(high2);
                delay(servoDelay);
                myservo2.write(low2);    
            }


            else if (note2 == 0x43){  // C flat played
                myservo3.write(low3);
                delay(servoDelay);
                myservo3.write(high3);
                delay(servoDelay);
                myservo3.write(low3);    
            }

            else if (note2 == 0x44){  // C flat played
                myservo4.write(low4);
                delay(servoDelay);
                myservo4.write(high4);
                delay(servoDelay);
                myservo4.write(low4);    
            }

            else if (note2 == 0x45){  // C flat played
                myservo5.write(low5);
                delay(servoDelay);
                myservo5.write(high5);
                delay(servoDelay);
                myservo5.write(low5);    
            }
            
            while(Serial1.available()){  // Flush all remaining notes in queue 
              Serial1.read();
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
