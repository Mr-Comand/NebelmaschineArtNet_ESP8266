// Writes the persistence data to the Eeprom
void writeDataToEEPROM() {
  EEPROM.begin(4096);

  // next position for witing data from.
  int position = 0;

  // Writes ArtNet-Data to EEPROM
  EEPROM.put(position, Address);  // 16 bit
  position += 16;
  EEPROM.put(position, Univers);  // 8 bit
  position += 8;
  EEPROM.put(position, dualChenelMode);  // 8 bit
  position += 8;
  EEPROM.put(position, shortname);  //
  position += sizeof(shortname);
  EEPROM.put(position, longname);
  position += sizeof(longname);

  // Write SSIDs to EEPROM
  for (int i = 0; i < 4; ++i) {
    EEPROM.put(position, ssids[i]);
    position += sizeof(ssids[0]);
  }

  // Write passwords to EEPROM
  for (int i = 0; i < 4; ++i) {
    EEPROM.put(position, passwords[i]);
    position += sizeof(passwords[0]);
  }

  EEPROM.commit();
  EEPROM.end();
}
// Reads the persistence data from the Eeprom
void readDataFromEEPROM() {
  EEPROM.begin(4096);

  // next position to read data from.
  int position = 0;
  
  // Read ArtNet-Data from EEPROM.
  EEPROM.get(position, Address);  // 16 bit
  position += 16;
  EEPROM.get(position, Univers);  // 8 bit
  position += 8;
  EEPROM.get(position, dualChenelMode);  // 8 bit
  position += 8;
  EEPROM.get(position, shortname);
  position += sizeof(shortname);
  EEPROM.get(position, longname);
  position += sizeof(longname);

  // Reads SSIDs drom EEPROM
  for (int i = 0; i < 4; ++i) {
    EEPROM.get(position, ssids[i]);
    position += sizeof(ssids[0]);
  }

  // Reads passwords from EEPROM
  for (int i = 0; i < 4; ++i) {
    EEPROM.get(position, passwords[i]);
    position += sizeof(passwords[0]);
  }

  EEPROM.end();
}