

//-------------------------------------------------
int getGyroValues(){
  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  int zz = ((zMSB << 8) | zLSB);
   
  return zz;
}

//------------------------------------------------
void setupL3G4200D(int scale){
  // Enable Z-axis only and turn off power down
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001100);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:
  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
    SC = SC250;
  }
  else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
    SC = SC500;
  }
  else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
    SC = SC2000;
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

//----------------------------------------------------------------
void writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

//------------------------------------------------------------------
int readRegister(int deviceAddress, byte address){
    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) {
       //wait for sensor value
    }

    v = Wire.read();
    return v;
}

