#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int nE3   = A0;
int nF3   = A1;
int nFS3  = A2;
int nG3   = A3;
int nA4   = A4;
int nBb4  = A5;

#define NUM_NOTES 0xff
#define COUNT_DOWN 100

byte note[NUM_NOTES];
bool note_enable[NUM_NOTES];

      

int i_note[NUM_NOTES];


int doHit()
{
  for(int i = 0; i < NUM_NOTES; i++)
  {
    if(note_enable[i]){
      if(i_note[i] >0) digitalWrite(note[i],HIGH);
      else { digitalWrite(note[i] ,LOW); i_note[i] = 0;}
    }
  }
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    //doHit(nF3);

    i_note[pitch] = COUNT_DOWN;
    doHit();
    /*
    switch(pitch){
      case 0x40: doHit(nE3); i_note[pitch] = COUNT_DOWN; break;
      case 0x41: doHit(nF3); i_note[pitch] = COUNT_DOWN;break;
      case 0x42: doHit(nFS3);i_note[pitch] = COUNT_DOWN;break;
      case 0x43: doHit(nG3); i_note[pitch] = COUNT_DOWN;break;
      case 0x44: doHit(nA4); i_note[pitch] = COUNT_DOWN;break;
      case 0x45: doHit(nBb4);i_note[pitch] = COUNT_DOWN;break;
    default:
    break;
    }
    */
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}

void setup() {
  /* Midi Setup */
      // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);


  /* Set note itterator */
  for (int i = 0; i < NUM_NOTES; i++) i_note[i] = 0; 

  /* Set enable flags */
  for( int i = 0; i < NUM_NOTES; i++) note_enable[i] = false;

  /* Setup note Values */
  note[0x40] = A0; note_enable[0x40] = true; // E3 
  note[0x41] = A1; note_enable[0x41] = true;// F3  
  note[0x42] = A2; note_enable[0x42] = true;// F#3
  note[0x43] = A3; note_enable[0x43] = true;// G3 
  note[0x44] = A4; note_enable[0x44] = true;// A4 
  note[0x45] = A5; note_enable[0x45] = true;// Bb4 

    
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


void loop() {
  MIDI.read();
  doHit();
  for(int i = 0; i < NUM_NOTES; i++) i_note[i]--;
}
//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.print(cmd);
  Serial.print(pitch);
  Serial.print(velocity);
}



