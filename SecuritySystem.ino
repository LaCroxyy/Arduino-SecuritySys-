boolean softwareIsArmed = false;
boolean softwareTripped = false;
boolean softwareScanning = false;
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int speakerPin = 5;

int numTones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//            mid C  C#   D    D#   E    F    F#   G    G#   A
void setup()
{
  pinMode( 2, INPUT); // NORMAALISTI INPUT_PULLUP
  pinMode( 3, INPUT);// NORMAALISTI INPUT_PULLUP
  pinMode( 4, INPUT);// NORMAALISTI INPUT_PULLUP
  pinMode( 5, OUTPUT);
  Serial.begin(9600);
  pinMode( 9   , OUTPUT);
  pinMode( 8 , OUTPUT);
  pinMode( 11 , OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(8, HIGH);
    digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  softwareArmed(false);

  buttonState = digitalRead(2);
  buttonState2 = digitalRead(3);
  buttonState3 = digitalRead(4);
}

void loop()
{
  //CALLS
  if (softwareScanning)
  {
    scanningSystem();
  }
  // PRINT BUTTON OUTPUTS
  Serial.print("Pushbutton 2:");
  Serial.print(digitalRead(2));
  Serial.println();
  Serial.print("Pushbutton 3:");
  Serial.print(digitalRead(3));
  Serial.println();
  Serial.print("Pushbutton 4:");
  Serial.print(digitalRead(4));
  Serial.println();
  /*
  Serial.print("SensorValue: ");
  Serial.print(analogRead(A0));
  Serial.println();*/

  if(buttonState == HIGH)
  {
    softwareArmed(true);
  }

  if(buttonState2 == HIGH)
  {
    softwareTrippedMode(false);
    softwareArmed(false);
  }

  if(buttonState3 == HIGH)
  {
    softwareScanning = true;
  }
}

void scanningSystem()
{
  //LED SOFTWARE TRIPPED MODE
  if(analogRead(A0) <= 520)
  {
    delay(5000);
      Serial.print("[ScanningSystem] Movement detected, alarm Tripped!");
    Serial.println();
    delay(5000);
    softwareTrippedMode(true);
  }

  //
}

void softwareTrippedMode(boolean state)
{
  if ( state )
  {
    softwareTripped = true;
      securitySystem();
      softwareArmed(false);
  } else if ( !state ) {
    softwareTripped = false;
	securitySystem();
  }

  if(softwareTripped)
  {
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    delay(100);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    delay(100);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    delay(2000);
  }
  while(softwareTripped)
  {
      digitalWrite(9, HIGH);
      digitalWrite(11, HIGH);
      delay(10);
      digitalWrite(9, LOW);
      digitalWrite(11, LOW);
      delay(10);
      digitalWrite(9, HIGH);
      digitalWrite(11, HIGH);
      delay(10);

      // SIREN CALL
  }
}

void securitySystem()
{
  if (softwareTripped)
  {
      for (int i = 0; i < numTones; i++)
      {
        tone(speakerPin, tones[i]);
        delay (500);
      }
  }

  if (!softwareTripped)
  {
    noTone(speakerPin);
  }
}

boolean softwareArmed(boolean state)
{
  if ( state )
  {
    softwareIsArmed = true;

    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
  } else if ( !state ) {
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
  }


  while(softwareIsArmed)
  {
    Serial.print("[SoftwareArmed] :: Software is Armed");
    Serial.println();
    digitalWrite(8, HIGH);
    delay(400);
    digitalWrite(8, LOW);
    delay (2000);

      //LED SOFTWARE TRIPPED MODE
  if(analogRead(A0) <= 520)
  {
    delay(5000);
    Serial.print("[ScanningSystem] :: Movement detected, alarm Tripped!");
    Serial.println();
    softwareTrippedMode(true);
  }

  }
  if (!softwareIsArmed)
  {
    Serial.print("[SoftwareArmed] :: Software is Unarmed");
    Serial.println();

    digitalWrite(8, HIGH);
  }

}


