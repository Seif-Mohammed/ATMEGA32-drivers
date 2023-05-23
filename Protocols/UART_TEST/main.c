#include "STDTYPE.h"
#include "BIT_MATH.h"
#define F_CPU	8000000UL
#include <avr/delay.h>
#include "MDIO_Interface.h"
#include "MUART_Interface.h"
int main(void){
	MDIO_U8INIT();
	MURAT_voidInit();
	while(1){
		u8 CH;
		CH = MURAT_voidRecieveByte();
		_delay_ms(50);
		if(CH == 'A')
			MDIO_u8SetPinValue(MDIO_U8_PORTC , MDIO_U8_PIN_0 , MDIO_U8_HIGH);
		if(CH == 'S')
			MDIO_u8SetPinValue(MDIO_U8_PORTC , MDIO_U8_PIN_0 , MDIO_U8_LOW);

		_delay_ms(200);
	}
	return 0;
}
