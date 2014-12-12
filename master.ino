///////////////////////////////////// SETUP MASTER
void setupMaster(){
  Wire.begin();
}

///////////////////////////////////// UPDATE MASTER
void updateMaster(){
  //read from slave
  masterRead();
  masterWrite();

}

///////////////////////////////////// MASTER READ
void masterRead(){
  if(Wire.requestFrom(2, SLAVE_DATA_BUFFER_LENGTH)){    // request 6 bytes from slave device #2
    disconnected = false;
    paused = false;
    while(Wire.available()){    // slave may send less than requested
      char data_in = Wire.read(); // receive byte per byte
      switch(data_in){
      case PLAYER_X:
        ennemiX = Wire.read();
        break;
      case PLAYER_ATT:
        isSlaveAttak = Wire.read() == '1';
        break;
      case PLAYER_BOUCL:
        isSlaveBouclierOpen = Wire.read() == '1';
        break;
      case SLAVE_PAUSED:
        gb.popup(F("Slave paused"),2);
        paused = true;
        break;
      case I_AM_MASTER:
        gb.popup(F("1 master max"),2);
        paused = true;
        break;
      default:
        gb.popup(F("Wrong slave data"),2);
        paused = true;
        break;
      }
    }
  }
  else{
    gb.popup(F("Slave disconnected"),2);
    paused = true;
    disconnected = true;
  }
}

///////////////////////////////////// MASTER WRITE
void masterWrite(){
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(PLAYER_X); //identifier
  Wire.write(mapostionX); //variable
  Wire.write(PLAYER_ATT);
  Wire.write(isMasterAttak ? '1' : '0');
  Wire.write(PLAYER_BOUCL);
  Wire.write(isMasterBouclierOpen ? '1' : '0');
  Wire.endTransmission();    // stop transmitting
}






