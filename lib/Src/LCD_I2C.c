/******************************************************************************************************************
File:  	LCD I2C dùng Chip PCF8574

Nếu dùng F103 thì mở thư viện chip F1 bên .h

Hướng dẫn Setup:
	LCD_Init(&LCD, &hi2c1, 0x4e, 20, 4);

	LCD_Clear(&LCD);
	LCD_SetCursor(&LCD, 0, 0);
	LCD_WriteString(&LCD, "XIN CHAO");

******************************************************************************************************************/
#include "LCD_I2C.h"

//************************** Low Level Function ****************************************************************//
static void LCD_Delay(uint16_t Time)
{
	HAL_Delay(Time);
}
static void LCD_WriteI2C(LCD_I2C_Name* LCD, uint8_t Data, uint8_t Mode)
{
	char Data_H;
	char Data_L;
	uint8_t Data_I2C[4];
	Data_H = Data&0xF0;
	Data_L = (Data<<4)&0xF0;
	if(LCD->BACKLIGHT)
	{
		Data_H |= LCD_BACKLIGHT; 
		Data_L |= LCD_BACKLIGHT; 
	}
	if(Mode == LCD_DATA)
	{
		Data_H |= LCD_RS;
		Data_L |= LCD_RS;
	}
	else if(Mode == LCD_COMMAND)
	{
		Data_H &= ~LCD_RS;
		Data_L &= ~LCD_RS;
	}
	Data_I2C[0] = Data_H|LCD_EN;
	LCD_Delay(1);
	Data_I2C[1] = Data_H;
	Data_I2C[2] = Data_L|LCD_EN;
	LCD_Delay(1);
	Data_I2C[3] = Data_L;
	HAL_I2C_Master_Transmit(LCD->I2C, LCD->ADDRESS, (uint8_t *)Data_I2C, sizeof(Data_I2C), 1000);
}


//************************** High Level Function ****************************************************************//
void LCD_Init(LCD_I2C_Name* LCD, I2C_HandleTypeDef* hi2c_CLCD, uint8_t Address, uint8_t Colums, uint8_t Rows)
{
	LCD->I2C = hi2c_CLCD;
	LCD->ADDRESS = Address;
	LCD->COLUMS = Colums;
	LCD->ROWS = Rows;
	
	LCD->FUNCTIONSET = LCD_FUNCTIONSET|LCD_4BITMODE|LCD_2LINE|LCD_5x8DOTS;
	LCD->ENTRYMODE = LCD_ENTRYMODESET|LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT;
	LCD->DISPLAYCTRL = LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSOROFF|LCD_BLINKOFF;
	LCD->CURSORSHIFT = LCD_CURSORSHIFT|LCD_CURSORMOVE|LCD_MOVERIGHT;
	LCD->BACKLIGHT = LCD_BACKLIGHT;

	LCD_Delay(50);
	LCD_WriteI2C(LCD, 0x33, LCD_COMMAND);
//	LCD_Delay(5);
	LCD_WriteI2C(LCD, 0x33, LCD_COMMAND);
	LCD_Delay(5);
	LCD_WriteI2C(LCD, 0x32, LCD_COMMAND);
	LCD_Delay(5);
	LCD_WriteI2C(LCD, 0x20, LCD_COMMAND);
	LCD_Delay(5);
	
	LCD_WriteI2C(LCD, LCD->ENTRYMODE,LCD_COMMAND);
	LCD_WriteI2C(LCD, LCD->DISPLAYCTRL,LCD_COMMAND);
	LCD_WriteI2C(LCD, LCD->CURSORSHIFT,LCD_COMMAND);
	LCD_WriteI2C(LCD, LCD->FUNCTIONSET,LCD_COMMAND);
	
	LCD_WriteI2C(LCD, LCD_CLEARDISPLAY,LCD_COMMAND);
	LCD_WriteI2C(LCD, LCD_RETURNHOME,LCD_COMMAND);
}
void LCD_SetCursor(LCD_I2C_Name* LCD, uint8_t Xpos, uint8_t Ypos)
{
	uint8_t DRAM_ADDRESS = 0x00;
	if(Xpos >= LCD->COLUMS)
	{
		Xpos = LCD->COLUMS - 1;
	}
	if(Ypos >= LCD->ROWS)
	{
		Ypos = LCD->ROWS -1;
	}
	if(Ypos == 0)
	{
		DRAM_ADDRESS = 0x00 + Xpos;
	}
	else if(Ypos == 1)
	{
		DRAM_ADDRESS = 0x40 + Xpos;
	}
	else if(Ypos == 2)
	{
		DRAM_ADDRESS = 0x14 + Xpos;
	}
	else if(Ypos == 3)
	{
		DRAM_ADDRESS = 0x54 + Xpos;
	}
	LCD_WriteI2C(LCD, LCD_SETDDRAMADDR|DRAM_ADDRESS, LCD_COMMAND);
}
void LCD_WriteChar(LCD_I2C_Name* LCD, char character)
{
	LCD_WriteI2C(LCD, character, LCD_DATA);
}
void LCD_WriteString(LCD_I2C_Name* LCD, char *String)
{
	while(*String)LCD_WriteChar(LCD, *String++);
}
void LCD_Clear(LCD_I2C_Name* LCD)
{
	LCD_WriteI2C(LCD, LCD_CLEARDISPLAY, LCD_COMMAND);
	LCD_Delay(5);
}
void LCD_ReturnHome(LCD_I2C_Name* LCD)
{
	LCD_WriteI2C(LCD, LCD_RETURNHOME, LCD_COMMAND);
	LCD_Delay(5);
}
void LCD_CursorOn(LCD_I2C_Name* LCD)
{
	LCD->DISPLAYCTRL |= LCD_CURSORON;
	LCD_WriteI2C(LCD, LCD->DISPLAYCTRL, LCD_COMMAND);
}
void LCD_CursorOff(LCD_I2C_Name* LCD)
{
	LCD->DISPLAYCTRL &= ~LCD_CURSORON;
	LCD_WriteI2C(LCD, LCD->DISPLAYCTRL, LCD_COMMAND);
}
void LCD_BlinkOn(LCD_I2C_Name* LCD)
{
	LCD->DISPLAYCTRL |= LCD_BLINKON;
	LCD_WriteI2C(LCD, LCD->DISPLAYCTRL, LCD_COMMAND);
}
void LCD_BlinkOff(LCD_I2C_Name* LCD)
{
	LCD->DISPLAYCTRL &= ~LCD_BLINKON;
	LCD_WriteI2C(LCD, LCD->DISPLAYCTRL, LCD_COMMAND);
}
