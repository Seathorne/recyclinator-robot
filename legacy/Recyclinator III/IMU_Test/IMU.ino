
void IMU() {
// Get a new sensor event
  sensors_event_t event;
  bno.getEvent(&event);

  // Display the floating point data
  Serial.print("Theta = ");
  Serial.println(event.orientation.x, 2);

  delay(100);  
}
