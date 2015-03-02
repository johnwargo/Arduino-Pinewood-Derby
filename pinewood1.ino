/***************************************************
 * Pinewood 1
 * 
 * by John M. Wargo & August M. Wargo
 * January, 2015
 ***************************************************/
//Number of lights the car has
const int numLights = 10;
//====================================================
// Constants used to define the accelerometer input
// pins
//====================================================
const int xPin = 14;
const int yPin = 15;
const int zPin = 16;
//====================================================
// Constants used to identify the device's orientation
//====================================================
const int IS_FLAT = 0;
const int IS_LEFT = 1;
const int IS_RIGHT = 2;
const int IS_SLANT = 3;
//====================================================
// Orientation thresholds
//====================================================
const int T_RIGHT = 400;
const int T_LEFT = 525;
const int T_SLANT = 470;

int blueLights[4] = {0,4,5,9};
int orangeLights[2] = {2,7};
int yellowLights[4] = {1,3,6,8};

int i = 0;

void setup() {  
   //Set all of the pins to output mode
  for (i = 0; i < numLights; i++) {
    pinMode(i, OUTPUT);
  }
  //make sure all of the lights are off
  doAll(LOW); 
  //Grab the initial value off of the accelerometer
  //this will be disgarded. Eliminates a quick light
  //lighting issue when the device is first turned on
  int tempInt = getOrientation();
  //Do a short delay before doing anything else
  delay(500);
  //Flash all of the lights (twice)
  doBlinkBlink();
}

void loop() {
  //make sure all of the lights are off
  doAll(LOW);
  //Read the accelerometer
  int orientation = getOrientation();
  //Now do something based on the orientation
  switch (orientation) {
  case IS_LEFT: 
    doAllRight(100);
    break;
  case IS_RIGHT: 
    doAllLeft(100);
    break;
  case IS_FLAT: 
    doCycle(125);
    break;
  case IS_SLANT:
    doBlend(75);
    break;
  default:
    //This should never execute
    //make sure all of the lights are off
    doAll(LOW);
  }
}

int getOrientation(){
  //  Serial.println("Getting Orientation");
  int x = analogRead(xPin);
  //  Serial.print("X: ");
  //  Serial.println(x);
  int y = analogRead(yPin);
  //  Serial.print("Y: ");
  //  Serial.println(y);
  int z = analogRead(zPin);
  //  Serial.print("Z: ");
  //  Serial.println(z);
  //  delay(500);

  //This is ugly code, I know.
  //Are we flat in the X direction?
  if (y > T_SLANT) {
    //Are we on our right side?
    if (x < T_RIGHT) {
      // Serial.println("Right");
      return IS_RIGHT;
    } 
    //Are we on our left side?
    else if (x > T_LEFT) {
      // Serial.println("Left");
      return IS_LEFT;
    } 
    else {
      //We must be flat
      // Serial.println("Flat");
      return IS_FLAT;
    }
  } 
  else {
    //Return a default value for now
    // Serial.println("Slant");
    return IS_SLANT;
  }
}

//====================================================
// Turn on/off a range of lights
//====================================================
void setLightStatus(int theStart, int theEnd, int theStatus) {
  for (i = theStart; i < theEnd; i++) {
    digitalWrite(i, theStatus);
  }
}

//====================================================
// Turn on/off all of the lights
//====================================================
void doAll(int status){
  setLightStatus(0, 10, status);
}

//====================================================
// Flash all of the lights twice
//====================================================
void doBlinkBlink(){
  doAll(HIGH);
  delay(200);
  doAll(LOW);
  delay(100);
  doAll(HIGH);
  delay(200);
  doAll(LOW);
}

//====================================================
// Turn on all of the right side lights
// then wait a little bit before turning them off
//====================================================
void doAllRight(int timeDel){
  setLightStatus(0, 5, HIGH);
  delay(timeDel);
  doAll(LOW);
  delay(timeDel);
}

//====================================================
// Turn on all of the left side lights
// then wait a little bit before turning them off
//====================================================
void doAllLeft(int timeDel){
  setLightStatus(5, 10, HIGH);
  delay(timeDel);
  doAll(LOW);
  delay(timeDel);
}

//====================================================
// Turn on all of the Blue lights
// then wait a little bit
//====================================================
void doAllBlue(int timeDel){
  for (i = 0; i < 4; i++) {
    digitalWrite(blueLights[i], HIGH);
  }
  delay(timeDel);
}

//====================================================
// Turn on all of the Orange lights
// then wait a little bit
//====================================================
void doAllOrange(int timeDel){
  for (i = 0; i < 2; i++) {
    digitalWrite(orangeLights[i], HIGH);
  }
  delay(timeDel);
}

//====================================================
// Turn on all of the Yellow lights
// then wait a little bit
//====================================================
void doAllYellow(int timeDel){
  for (i = 0; i < 4; i++) {
    digitalWrite(yellowLights[i], HIGH);
  }
  delay(timeDel);
}

//====================================================
// Light the lights in bands, blue first, then
// yellow, to orange and back again. 
//====================================================
void doBlend(int timeDel){
  doAllBlue(timeDel);
  doAll(LOW);
  doAllYellow(timeDel);
  doAll(LOW);
  doAllOrange(timeDel);
  doAll(LOW);
  doAllYellow(timeDel);
  doAll(LOW);
  doAllBlue(timeDel);
}

//====================================================
// Loop through the lights
// timeDel controls how long the each light stays on
//====================================================
void doCycle(int timeDel){
  for (i = 0; i < numLights; i++) {
    //Loop through all of the pins and turn the light on
    digitalWrite(i, HIGH);
    //Then wait for 1 second (1,000 miliseconds)
    delay(timeDel);
    //Then turn the light off
    digitalWrite(i, LOW);
  }   
}

//====================================================
// Same as cycle: Loop through the lights
// timeDel controls how long the each light stays on
// goes forward and backwards
//====================================================
void doDoubleCycle(int timeDel){
  for (i = 0; i < numLights; i++) {
    //Loop through all of the pins and turn the light on
    digitalWrite(i, HIGH);
    //Then wait for 1 second (1,000 miliseconds)
    delay(timeDel);
    //Then turn the light off
    digitalWrite(i, LOW);
  }
  for (i = numLights; i >0; i--) {
    //Loop through all of the pins and turn the light on
    digitalWrite(i, HIGH);
    //Then wait for 1 second (1,000 miliseconds)
    delay(timeDel);
    //Then turn the light off
    digitalWrite(i, LOW);
  }
}
















































