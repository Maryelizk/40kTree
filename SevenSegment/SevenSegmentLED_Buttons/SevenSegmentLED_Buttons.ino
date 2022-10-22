/*
  Showing numbers, chars and phrases
                             A (seg[0] in this project)
                            ---
F (seg[5] in this project) |   | B (seg[1] in this project)
                           |   | 
                            --- G (seg[6] in this project)
E (seg[4] in this project) |   | 
                           |   | C (seg[2] in this project)
                            ---  . dot or dicimal (seg[7] in this project)
                             D (seg[3] in this project)

 */
#define A 8
#define B 7
#define C 6
#define D 5
#define E 4
#define F 3
#define G 2
#define DP 9 // decimal
#define common_cathode 0
#define common_anode 1

//define buttons
const int buttonUP = 11;
const int buttonDOWN = 12; 

//start the count at 0
int score = 5;

bool segMode = common_cathode; // set this to your segment type, my segment is common_cathode
int seg[] {A,B,C,D,E,F,G,DP}; // segment pins
byte chars = 11; // max value in the array "Chars"

byte Chars[11][9] { 
            {'0',1,1,1,1,1,1,0,0},//0
            {'1',0,1,1,0,0,0,0,0},//1
            {'2',1,1,0,1,1,0,1,0},//2
            {'3',1,1,1,1,0,0,1,0},//3
            {'4',0,1,1,0,0,1,1,0},//4
            {'5',1,0,1,1,0,1,1,0},//5
            {'6',1,0,1,1,1,1,1,0},//6
            {'7',1,1,1,0,0,0,0,0},//7
            {'8',1,1,1,1,1,1,1,0},//8
            {'9',1,1,1,1,0,1,1,0},//9
            {'.',0,0,0,0,0,0,0,1},//./10
            };

void setup() {
  // set segment pins as OUTPUT
pinMode(seg[0],OUTPUT);
pinMode(seg[1],OUTPUT);
pinMode(seg[2],OUTPUT);
pinMode(seg[3],OUTPUT);
pinMode(seg[4],OUTPUT);
pinMode(seg[5],OUTPUT);
pinMode(seg[6],OUTPUT);
pinMode(seg[7],OUTPUT);
//Setup buttons
//INPUT_PULLUP reverses input values, meaning a pressed button registers as 0 or LOW and an unpressed button registers as 1 or HIGH
//The conditionals based on these inputs have been reversed to account for this (e.g. if(!buttonUp) instead of if(buttonUP))
pinMode(buttonUP, INPUT_PULLUP);
pinMode(buttonDOWN, INPUT_PULLUP);

Serial.begin(9600);
}



void setState(bool mode) //sets the hole segment state to "mode"
{ for(int i = 0;i<=6;i++)
{
  digitalWrite(seg[i],mode);
}
}

//fix bounce of keys
void debounceScoreButton(int buttonPin) {
      int lastButtonState = 1;
      int buttonState = digitalRead(buttonPin);
      while(!digitalRead(buttonPin)){
        // compare the buttonState to its previous state
        if (buttonState != lastButtonState) {
      
          // if the state has changed, increment the counter
          if (buttonState == LOW) {
      
            // if the current state is HIGH then the button      
            // went from off to on:      
            if (buttonPin==buttonUP){
              score++;    
            }
            if (buttonPin==buttonDOWN){
              score--;
            }
              
            Serial.println(score);
            Print(score);      
          }      
          // Delay a little bit to avoid bouncing      
          delay(50);      
        }
      
        // save the current state as the last state for next time through the loop
      
        lastButtonState = buttonState;
      }
}

void Print(char Char) // print any character on the segment ( Note : you can't use capital characters )
{ 
  int charNum = -1;// set search result to -1
  setState(segMode);//turn off the segment
  
for(int i = 0; i < chars ;i++){//search for the enterd character
  if(Char == Chars[i][0]){//if the character found
    charNum = i;//set the resault number into charNum ( because this function prints the character using it's number in the array )
  }
}
 
if(charNum == -1 )// if the character not found
{
  for(int i = 0;i <= 6;i++)
  {
  digitalWrite(seg[i],HIGH);
  delay(100);
  digitalWrite(seg[i],LOW);
  }
  for(int i = 0;i <= 2;i++)
{
  delay(100);
  setState(HIGH);
  delay(100);
  setState(LOW); 
}
}else // else if the character found print it
 {
for(int i = 0;i<8;i++)
    {digitalWrite(seg[i],Chars[charNum][i+1]);
    }
 }

}

void Print(int num) // print any number on the segment
{ 
  setState(segMode);//turn off the segment
  

 
if(num > chars || num < 0 )// if the number is not declared
{
  for(int i = 0;i <= 6;i++)
  {
  digitalWrite(seg[i],HIGH);
  delay(100);
  digitalWrite(seg[i],LOW);
  }
  for(int i = 0;i <= 2;i++)
{
  delay(100);
  setState(HIGH);
  delay(100);
  setState(LOW); 
}
}else // else if the number declared, print it
 {
  if(segMode == 0){ //for segment mode
for(int i = 0;i<8;i++)
    {digitalWrite(seg[i],Chars[num][i+1]);
    }
 }
 else{
  for(int i = 0;i<8;i++)
    {digitalWrite(seg[i],!Chars[num][i+1]);
    }
 }
 }
}

void loop() {  
  Print(score);
    Serial.println(score);
    Serial.println(digitalRead(buttonUP));
    Serial.println(digitalRead(buttonDOWN));
    if (!digitalRead(buttonUP)) {
      debounceScoreButton(buttonUP);
  }
    if (!digitalRead(buttonDOWN)) {
      debounceScoreButton(buttonDOWN);
    }

  //Print(number or character); // print any number or character on the segment ( Note : you can't use capital characters )
  //setState(state); //sets the hole segment state to "state"

}
