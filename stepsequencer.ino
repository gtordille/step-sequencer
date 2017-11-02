// this is a step sequencer
#include <EEPROM.h>

int buttonPinArray[4] = { 32, 31, 30, 29 };
int buttonPin1 = 27;
int buttonPin2 = 28;
int ledPinArray[4] = { 38, 37, 36, 35 };
int totalLeds = 4;
int currentStep = 0;
int tempo = 0;
int channel = 0;
unsigned long lastStepTime = 0;
boolean lastButtonState[4] = { LOW, LOW, LOW, LOW };
boolean buttonState[4] = { LOW, LOW, LOW, LOW };
boolean lastButtonState1 = LOW;
boolean buttonState1 = LOW;
boolean lastButtonState2 = LOW;
boolean buttonState2 = LOW;
boolean stepState[3][4] = {
  { false, false, false, false },
  { false, false, false, false },
  { false, false, false, false },
};

void setup() {

  for (int i = 0; i < totalLeds; i++) {
    pinMode(ledPinArray[i], OUTPUT);
    pinMode(buttonPinArray[i], INPUT);
  }

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  setChannel();
  sequence();
  checkButtons();
  setLeds();
}

void sequence() {

  tempo = analogRead(A6);

  if (millis() > lastStepTime + tempo) {   //if its time to go to the next step...
    currentStep = currentStep + 1;         //increment to the next step
    if (currentStep > 3) {
      currentStep = 0;
    }
    if (stepState[0][currentStep] == true) {
      usbMIDI.sendNoteOn(36, 127, 1);
    } else if (stepState[channel][currentStep] == false) {
      usbMIDI.sendNoteOff(36, 0, 1);
    }

    if (stepState[1][currentStep] == true) {
      usbMIDI.sendNoteOn(38, 127, 1);
    } else if (stepState[channel][currentStep] == false) {
      usbMIDI.sendNoteOff(38, 0, 1);
    }

    if (stepState[2][currentStep] == true) {
      usbMIDI.sendNoteOn(39, 127, 1);
    } else if (stepState[channel][currentStep] == false) {
      usbMIDI.sendNoteOff(39, 0, 1);
    }

    lastStepTime = millis();               //set lastStepTime to the current time
  }
}
void checkButtons() {

  for (int i = 0; i < 4; i++) {
    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttonPinArray[i]);

    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      if (stepState[channel][i] == false) {
        stepState[channel][i] = true;
      } else if (stepState[channel][i] == true) {
        stepState[channel][i] = false;
      }
    }

    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      if (stepState[channel][i] == false) {
        stepState[channel][i] = true;
      } else if (stepState[channel][i] == true) {
        stepState[channel][i] = false;
      }
    }

    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      if (stepState[channel][i] == false) {
        stepState[channel][i] = true;
      } else if (stepState[channel][i] == true) {
        stepState[channel][i] = false;
      }
    }
  }
}

void setLeds() {    //this lets it know which LEDs should be lit
  for (int i = 0; i < 4; i++) {
    if (currentStep == i) {
      analogWrite(ledPinArray[i], 255);
    } else if (stepState[channel][i] == HIGH) {
      analogWrite(ledPinArray[i], 50);
    }
    else  {
      analogWrite(ledPinArray[i], 0);
    }

    if (currentStep == i) {
      analogWrite(ledPinArray[i], 255);
    } else if (stepState[channel][i] == HIGH) {
      analogWrite(ledPinArray[i], 50);
    }
    else  {
      analogWrite(ledPinArray[i], 0);
    }

    if (currentStep == i) {
      analogWrite(ledPinArray[i], 255);
    } else if (stepState[channel][i] == HIGH) {
      analogWrite(ledPinArray[i], 50);
    }
    else  {
      analogWrite(ledPinArray[i], 0);
    }
  }
}

void setChannel() {         // this sets which channel is shown on the LEDs
  lastButtonState1 = buttonState1;
  buttonState1 = digitalRead(buttonPin1);

  if (buttonState1 == HIGH && lastButtonState1 == LOW) {
    channel++;
    if (channel > 2) {
      channel = 0;
    }
  }


  lastButtonState2 = buttonState2;
  buttonState2 = digitalRead(buttonPin2);

  if (buttonState2 == HIGH && lastButtonState2 == LOW) {
    channel--;
    if (channel < 0) {
      channel = 2;
    }
  }
}


