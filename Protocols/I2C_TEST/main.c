#include "STDTYPE.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#include "MDIO_Interface.h"
#include "MTWI_Interface.h"

#define MEXTI_U8_SREG_REG		*((volatile u8*)0X5F)
int main(void){
	u8 reading ;
	SET_BIT(MEXTI_U8_SREG_REG,7);
	HEEPROM_WriteByte(500 , 'A');
	_delay_ms(1000);
	HEEPRPM_ReadByte(500 , &reading);
	_delay_ms(1000);
	if(reading == 'A'){
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_0 , MDIO_U8_HIGH);
	}
	while(1){

	}
	return 0;
}
