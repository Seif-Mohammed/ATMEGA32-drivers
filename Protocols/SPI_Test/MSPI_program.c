#include "BIT_MATH.h"
#include "STDTYPE.h"
#include "MDIO_Interface.h"
#include "MSPI_Interface.h"
#include "MSPI_Config.h"
#include "MSPI_Private.h"

u8 MSPI_U8_MASTERInit(){
	u8 LocalErrorState = STD_TYPES_OK;
	/*Enable SPI protocol pins*/
	SET_BIT(MSPI_SPCR_REG , 6);
	/*Choose data order option MSB OR LSB*/
	//MSPI_SPCR_REG = MSPI_SPCR_REG | MSPI_DataOrderOption
	SET_BIT(MSPI_SPCR_REG , 5);
	/*Master mode*/
	SET_BIT(MSPI_SPCR_REG , 4);
	/*clk polarity raising ==> falling*/
	SET_BIT(MSPI_SPCR_REG , 3);
	/*clock phase setup ==>sample*/
	SET_BIT(MSPI_SPCR_REG , 2);
	/*Select clk ==> foc/128*/
	SET_BIT(MSPI_SPCR_REG , 1);
	SET_BIT(MSPI_SPCR_REG , 0);
	return LocalErrorState;

}
u8 MSPI_U8_SlaveInit(){
	u8 LocalErrorState = STD_TYPES_OK;
	/*Enable SPI protocol pins*/
	SET_BIT(MSPI_SPCR_REG , 6);
	/*Choose data order option MSB OR LSB*/
	//MSPI_SPCR_REG = MSPI_SPCR_REG | MSPI_DataOrderOption
	SET_BIT(MSPI_SPCR_REG , 5);
	/*Slave mode*/
	CLEAR_BIT(MSPI_SPCR_REG , 4);
	/*clk polarity raising ==> falling*/
	SET_BIT(MSPI_SPCR_REG , 3);
	/*clock phase setup ==>sample*/
	SET_BIT(MSPI_SPCR_REG , 2);
	return LocalErrorState;
}
u8 MSPI_U8_TransRecieve(u8 CopyData){

	/*Write data on Data register*/
	MSPI_SPDR_REG = CopyData;
	while((!GET_BIT(MSPI_SPDR_REG , 7)));

	return MSPI_SPDR_REG;
}
