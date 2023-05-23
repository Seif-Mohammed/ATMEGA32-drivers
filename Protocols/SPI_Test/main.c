#include "STDTYPE.h"
#include "BIT_MATH.h"
#include <avr/delay.h>
#include "MDIO_Interface.h"
#include "MSPI_Interface.h"

//#define MEXTI_U8_SREG_REG		*((volatile u8*)0X5F)
int main(void){
	//SET_BIT(MEXTI_U8_SREG_REG,7);
	u8 Local_Rx_Data ;
	MDIO_U8INIT();
	MSPI_U8_MASTERInit();
	//MSPI_U8_SlaveInit();
	while(1){
		/*Local_Rx_Data = MSPI_U8_TransRecieve(5);
		if(Local_Rx_Data == 1){
			MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_0 , MDIO_U8_HIGH);
		}
		else if(Local_Rx_Data == 2){
			MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_0 , MDIO_U8_HIGH);
		}*/

		Local_Rx_Data = MSPI_U8_TransRecieve(1);
		_delay_ms(100);
		Local_Rx_Data = MSPI_U8_TransRecieve(2);
		if(Local_Rx_Data == 5){
			MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_0 , MDIO_U8_HIGH);
		}
		_delay_ms(100);

	}
	return 0;
}
