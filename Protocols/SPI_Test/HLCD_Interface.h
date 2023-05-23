#ifndef HLCD_Interface_h
#define HLCD_Interface_h
/*prototypes of LCD*/
u8 HLCD_U8Init(void);
u8 HLCD_U8WriteChar(u8 Copy_u8Char);
u8 HLCD_U8WriteCommand(u8 Copy_u8Cmnd);
u8 HLCD_U8SetCursor(u8 Copy_u8LineNumber , u8 Copy_u8CharacterNumber);
u8 HLCD_U8WriteString(u8 * Copy_u8String);
void HLCD_U8ClearLCD(void);
void HLCD_U8DrawChar(u8 Copy_u8LineNumber , u8 Copy_u8CharacterNumber , u8 Copy_CharIndex , u8 * Copy_CustomChar);
u8 HLCD_U8WriteNumber(u8 Copy_u8Number);

#endif
