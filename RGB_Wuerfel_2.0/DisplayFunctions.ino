void DisplayStatic(const byte data[][3][2], const boolean layerSelection[][4], int displayTime, byte numberOfFrames){
  for (int i = 0; i < numberOfFrames; i++){
    if (interrupt_status == 1){
      interrupt_status = 0;
      return;
    }
    // Shift out 2 bytes of data for the red color
    shiftOut(DATA_R, CLOCK, MSBFIRST, data[i][0][0]);
    shiftOut(DATA_R, CLOCK, MSBFIRST, data[i][0][1]);
    // Falling Edge to transfer data to output register of 74hch595
    digitalWrite(RCLK_R, HIGH);
    digitalWrite(RCLK_R, LOW);
    // Shift out 2 bytes of data for the green color
    shiftOut(DATA_G, CLOCK, MSBFIRST, data[i][1][0]);
    shiftOut(DATA_G, CLOCK, MSBFIRST, data[i][1][1]);
    // Falling Edge to transfer data to output register of 74hch595
    digitalWrite(RCLK_G, HIGH);
    digitalWrite(RCLK_G, LOW);
    // Shift out 2 bytes of data for the blue color
    shiftOut(DATA_B, CLOCK, MSBFIRST, data[i][2][0]);
    shiftOut(DATA_B, CLOCK, MSBFIRST, data[i][2][1]);
    // Falling Edge to transfer data to output register of 74hch595
    digitalWrite(RCLK_B, HIGH);
    digitalWrite(RCLK_B, LOW);
  
    // Activate Layers or not
    digitalWrite(A1, layerSelection[i][0]);
    digitalWrite(A2, layerSelection[i][1]);
    digitalWrite(A3, layerSelection[i][2]);
    digitalWrite(A4, layerSelection[i][3]);
    // Delay for a display time of the current frame
    delay(displayTime);
    // Deactivate all Layers
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
  }
}
/*
void PWMStatic(const byte data[][3][2], const boolean layerSelection[][4], int displayTime, byte numberOfFrames, ){
  
}*/