int LeftDirection () {
  digitalWrite(dirPin,LOW); //Enables the motor to move in a particular direction
  digitalWrite(stepPin, HIGH);
  delay(StepDelay);
  digitalWrite(stepPin, LOW);
  delay(StepDelay);
}

