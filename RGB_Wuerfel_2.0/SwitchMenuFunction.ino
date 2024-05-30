int adcVal;
float voltage;

float getVoltage(){
  adcVal = analogRead(ANALOG_PIN);    //adcVal read in
  voltage = adcVal * 0.0048875;     //10 bit ADC thus 5V/1023 = 0.0048875
}

void switchMenu(void)
{
  voltage = getVoltage();
  
  if(Serial1.available() > 0){
    char data = Serial1.read();

    switch (data){
      case '1':
        //Serial.println("Sub Menu ++");
        subMenu++; 
        break;

      case '2':
        //Serial.println("Menu ++");
        menu++; 
        subMenu = 1; 
        break;

      case '3':
        //Serial.println("Menu --");
        menu--; 
        subMenu = 1; 
        break;

      default: 
        break;
    }

    interrupt_status = 1;
    EEPROM.update(ADDRESS_SUB_MENU, subMenu);
    EEPROM.update(ADDRESS_MENU, menu);
  }
  
  
  if(voltage > 1){
     if(voltage > 1 && voltage < 2){       //voltagesbereiche des voltagesteilers
        while(voltage > 1 && voltage < 2){
           voltage = getVoltage();

           if(voltage >= 0 && voltage <= 1){
              subMenu++;
           }
        }
     }
    
     if(voltage > 2 && voltage < 4){       //voltagesbereiche des voltagesteilers
        while(voltage > 2 && voltage < 4){
           voltage = getVoltage();
           
           if(voltage >= 0 && voltage <= 1){
              subMenu = 1;
              menu++;
           }
        }
     }
    
     if(voltage <= 5 && voltage > 4){       //voltagesbereiche des voltagesteilers
        while(voltage <= 5 && voltage > 4){
           voltage = getVoltage();

           if(voltage >= 0 && voltage <= 1){
              subMenu = 1;
              menu--;   
           }
        }
     }

     interrupt_status = 1;
     EEPROM.update(ADDRESS_SUB_MENU, subMenu);
     EEPROM.update(ADDRESS_MENU, menu);
  }
}