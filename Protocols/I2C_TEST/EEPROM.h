#ifndef EEPROM_H_
#define EEPROM_H_

u8 EEPROM_INIT();
u8 HEEPROM_WriteByte(u32 address , u8 data);
u8 HEEPRPM_ReadByte(u32 address , u8 * data);


#endif /* EEPROM_H_ */
