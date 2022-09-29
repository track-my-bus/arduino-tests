
#include "sensors/accli/DFRobot_LIS2DW12.cpp"

DFRobot_LIS2DW12_I2C acce;

#if defined(ESP32) || defined(ESP8266)
  #define LIS2DW12_CS  D3
  #elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
  #define LIS2DW12_CS 3
  #elif (defined NRF5)
  #define LIS2DW12_CS 2 
#endif

void setup(void){

  Serial.begin(9600);
  while(!acce.begin()){
     Serial.println("Communication failed, check the connection and I2C address setting when using I2C communication.");
     delay(1000);
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Chip soft reset
  acce.softReset();
  //Set whether to collect data continuously
  acce.continRefresh(true);
  

  acce.setDataRate(DFRobot_LIS2DW12::eRate_50hz);
  
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**！
    Set bandwidth：
        eRateDiv_2  /<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>/
        eRateDiv_4  /<Rate/4 (High Power/Low power)>*
        eRateDiv_10 /<Rate/10 (HP/LP)>/
        eRateDiv_20 /< Rate/20 (HP/LP)>/
  */
  
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise2_14bit);
  Serial.print("Acceleration:\n");
  delay(100);
}

void loop(void){
    //Request a measurement under single data conversion on demand mode
    //acce.demandData();
    //The mearsurement range is ±2g,±4g,±8g or ±16g, set by the setRange() function.
    Serial.print("x: ");
    //Read the acceleration in the x direction
    Serial.print(acce.readAccX());
    Serial.print(" mg \ty: ");
    //Read the acceleration in the y direction
    Serial.print(acce.readAccY());
    Serial.print(" mg \tz: ");
    //Read the acceleration in the z direction
    Serial.print(acce.readAccZ());
    Serial.println(" mg");
}