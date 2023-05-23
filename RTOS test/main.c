#include "STDTYPE.h"
#include "MTMR_Interface.h"
#include "MDIO_Interface.h"
void APP_ToggleLed1(void){
	static u8 flag =0;
	if(flag == 0){
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_0 , MDIO_U8_HIGH);
		flag =1;
	}else{
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_0 , MDIO_U8_LOW);
		flag =0;
	}
}
void APP_ToggleLed2(void){
	static u8 flag =0;
	if(flag == 0){
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_1 , MDIO_U8_HIGH);
		flag =1;
	}else{
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_1 , MDIO_U8_LOW);
		flag =0;
	}
}
void APP_ToggleLed3(void){
	static u8 flag =0;
	if(flag == 0){
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_2 , MDIO_U8_HIGH);
		flag =1;
	}else{
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_2 , MDIO_U8_LOW);
		flag =0;
	}
}
int main(){
	MDIO_U8INIT();
	/*Create task*/
	RTO_u8CreateTask(0,1000,3000,&APP_ToggleLed1);
	RTO_u8CreateTask(1,3000,0,&APP_ToggleLed2);
	RTO_u8CreateTask(2,5000,0,&APP_ToggleLed3);
	RTO_voidStartScheduler();
	while(1){
		MDIO_u8SetPinValue(MDIO_U8_PORTA , MDIO_U8_PIN_3 , MDIO_U8_HIGH);
	}
	return 0;
}
