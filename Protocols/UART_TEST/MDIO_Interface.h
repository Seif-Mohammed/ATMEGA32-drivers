#ifndef MDIO_Interface_h
#define MDIO_Interface_h
/*Macros for PortIDs*/
#define MDIO_U8_PORTA 0
#define MDIO_U8_PORTB 1
#define MDIO_U8_PORTC 2
#define MDIO_U8_PORTD 3
/*Macros for PinIDs*/
#define MDIO_U8_PIN_0 0
#define MDIO_U8_PIN_1 1
#define MDIO_U8_PIN_2 2
#define MDIO_U8_PIN_3 3
#define MDIO_U8_PIN_4 4
#define MDIO_U8_PIN_5 5
#define MDIO_U8_PIN_6 6
#define MDIO_U8_PIN_7 7
/*Macros for PinDirection*/
#define MDIO_U8_OUTPUT 0
#define MDIO_U8_INPUT_FLOATING 1
#define MDIO_U8_INPUT_PULLED_UP 2
/*Macros for PinDirection*/
#define MDIO_U8_LOW 0
#define MDIO_U8_HIGH 1
/*___________________________________________________________________________________________________________*/
u8 MDIO_u8SetPinDirection(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinDirection);
u8 MDIO_u8SetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinValue);
u8 MDIO_u8GetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 * Copy_Pu8PinValue);
u8 MDIO_u8GetPortDirection(u8 Copy_u8PortID ,  u8 Copy_u8PortDirection);
u8 MDIO_u8SetPortValue(u8 Copy_u8PortID  , u8 Copy_u8PortValue);
u8 MDIO_u8GetPortValue(u8 Copy_u8PortID , u8 * Copy_u8PortValue);
/*___________________________________________________________________________________________________________*/
u8 MDIO_U8INIT(void);

#endif
