/**	
 * |----------------------------------------------------------------------
 * | Copyright (c) 2016 Tilen Majerle
 * |  
 * | Permission is hereby granted, free of charge, to any person
 * | obtaining a copy of this software and associated documentation
 * | files (the "Software"), to deal in the Software without restriction,
 * | including without limitation the rights to use, copy, modify, merge,
 * | publish, distribute, sublicense, and/or sell copies of the Software, 
 * | and to permit persons to whom the Software is furnished to do so, 
 * | subject to the following conditions:
 * | 
 * | The above copyright notice and this permission notice shall be
 * | included in all copies or substantial portions of the Software.
 * | 
 * | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * | EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * | OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * | AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * | HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * | WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * | FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * | OTHER DEALINGS IN THE SOFTWARE.
 * |----------------------------------------------------------------------
 */
#include "tm_stm32_hd44780.h"
#include "main.h"

/* Private HD44780 structure */
typedef struct
{
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} HD44780_Options_t;

/* Private functions */
static void TM_HD44780_InitPins(void);
static void TM_HD44780_Cmd(uint8_t cmd);
static void TM_HD44780_Cmd4bit(uint8_t cmd);
//void TM_HD44780_Data(uint8_t data);
void TM_HD44780_CursorSet(uint8_t col, uint8_t row);

/* Private variable */
static HD44780_Options_t HD44780_Opts;

/* Pin definitions */
#define HD44780_RS_LOW              HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin,GPIO_PIN_RESET) //TM_GPIO_SetPinLow(HD44780_RS_GPIO_Port, HD44780_RS_Pin)
#define HD44780_RS_HIGH             HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin,GPIO_PIN_SET)
#define HD44780_E_LOW               HAL_GPIO_WritePin(HD44780_E_GPIO_Port, HD44780_E_Pin,GPIO_PIN_RESET) //TM_GPIO_SetPinLow(HD44780_E_GPIO_Port, HD44780_E_Pin)
#define HD44780_E_HIGH              HAL_GPIO_WritePin(HD44780_E_GPIO_Port, HD44780_E_Pin,GPIO_PIN_SET) //TM_GPIO_SetPinHigh(HD44780_E_GPIO_Port, HD44780_E_Pin)

#define HD44780_Delay(x)            HAL_Delay(x)

#define HD44780_E_BLINK             HD44780_E_HIGH; HD44780_Delay(1); HD44780_E_LOW; HD44780_Delay(1)

/* Commands*/
#define HD44780_CLEARDISPLAY        0x01
#define HD44780_RETURNHOME          0x02
#define HD44780_ENTRYMODESET        0x04
#define HD44780_DISPLAYCONTROL      0x08
#define HD44780_CURSORSHIFT         0x10
#define HD44780_FUNCTIONSET         0x20
#define HD44780_SETCGRAMADDR        0x40
#define HD44780_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define HD44780_ENTRYRIGHT          0x00
#define HD44780_ENTRYLEFT           0x02
#define HD44780_ENTRYSHIFTINCREMENT 0x01
#define HD44780_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define HD44780_DISPLAYON           0x04
#define HD44780_CURSORON            0x02
#define HD44780_BLINKON             0x01

/* Flags for display/cursor shift */
#define HD44780_DISPLAYMOVE         0x08
#define HD44780_CURSORMOVE          0x00
#define HD44780_MOVERIGHT           0x04
#define HD44780_MOVELEFT            0x00

/* Flags for function set */
#define HD44780_8BITMODE            0x10
#define HD44780_4BITMODE            0x00
#define HD44780_2LINE               0x08
#define HD44780_1LINE               0x00
#define HD44780_5x10DOTS            0x04
#define HD44780_5x8DOTS             0x00

void TM_HD44780_Init(uint8_t cols, uint8_t rows)
{
	/* Initialize delay */
	//TM_DELAY_Init();
	/* Init pinout */
	TM_HD44780_InitPins();

	/* At least 40ms */
	HD44780_Delay(45);

	/* Set LCD width and height */
	HD44780_Opts.Rows = rows;
	HD44780_Opts.Cols = cols;

	/* Set cursor pointer to beginning for LCD */
	HD44780_Opts.currentX = 0;
	HD44780_Opts.currentY = 0;

	HD44780_Opts.DisplayFunction = HD44780_4BITMODE | HD44780_5x8DOTS
			| HD44780_1LINE;
	if (rows > 1)
	{
		HD44780_Opts.DisplayFunction |= HD44780_2LINE;
	}

	/* Try to set 4bit mode */
	TM_HD44780_Cmd4bit(0x03);
	HD44780_Delay(45);

	/* Second try */
	TM_HD44780_Cmd4bit(0x03);
	HD44780_Delay(45);

	/* Third goo! */
	TM_HD44780_Cmd4bit(0x03);
	HD44780_Delay(45);

	/* Set 4-bit interface */
	TM_HD44780_Cmd4bit(0x02);
	HD44780_Delay(1);

	/* Set # lines, font size, etc. */
	TM_HD44780_Cmd(HD44780_FUNCTIONSET | HD44780_Opts.DisplayFunction);

	/* Turn the display on with no cursor or blinking default */
	HD44780_Opts.DisplayControl = HD44780_DISPLAYON;
	TM_HD44780_DisplayOn();

	/* Clear lcd */
	TM_HD44780_Clear();

	/* Default font directions */
	HD44780_Opts.DisplayMode = HD44780_ENTRYLEFT | HD44780_ENTRYSHIFTDECREMENT;
	TM_HD44780_Cmd(HD44780_ENTRYMODESET | HD44780_Opts.DisplayMode);

	/* Delay */
	HD44780_Delay(45);
}

void TM_HD44780_Clear(void)
{
	TM_HD44780_Cmd(HD44780_CLEARDISPLAY);
	HD44780_Delay(30);
}

void TM_HD44780_Puts(uint8_t x, uint8_t y, char* str)
{
	TM_HD44780_CursorSet(x, y);
	while (*str)
	{
		if (HD44780_Opts.currentX >= HD44780_Opts.Cols)
		{
			HD44780_Opts.currentX = 0;
			HD44780_Opts.currentY++;
			TM_HD44780_CursorSet(HD44780_Opts.currentX, HD44780_Opts.currentY);
		}
		if (*str == '\n')
		{
			HD44780_Opts.currentY++;
			TM_HD44780_CursorSet(HD44780_Opts.currentX, HD44780_Opts.currentY);
		}
		else if (*str == '\r')
		{
			TM_HD44780_CursorSet(0, HD44780_Opts.currentY);
		}
		else
		{
			TM_HD44780_Data(*str);
			HD44780_Opts.currentX++;
		}
		str++;
	}
}

void TM_HD44780_DisplayOn(void)
{
	HD44780_Opts.DisplayControl |= HD44780_DISPLAYON;
	TM_HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void TM_HD44780_DisplayOff(void)
{
	HD44780_Opts.DisplayControl &= ~HD44780_DISPLAYON;
	TM_HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void TM_HD44780_BlinkOn(void)
{
	HD44780_Opts.DisplayControl |= HD44780_BLINKON;
	TM_HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void TM_HD44780_BlinkOff(void)
{
	HD44780_Opts.DisplayControl &= ~HD44780_BLINKON;
	TM_HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void TM_HD44780_CursorOn(void)
{
	HD44780_Opts.DisplayControl |= HD44780_CURSORON;
	TM_HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void TM_HD44780_CursorOff(void)
{
	HD44780_Opts.DisplayControl &= ~HD44780_CURSORON;
	TM_HD44780_Cmd(HD44780_DISPLAYCONTROL | HD44780_Opts.DisplayControl);
}

void TM_HD44780_ScrollLeft(void)
{
	TM_HD44780_Cmd(
	HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVELEFT);
}

void TM_HD44780_ScrollRight(void)
{
	TM_HD44780_Cmd(
	HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVERIGHT);
}

void TM_HD44780_CreateChar(uint8_t location, uint8_t *data)
{
	uint8_t i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	TM_HD44780_Cmd(HD44780_SETCGRAMADDR | (location << 3));

	for (i = 0; i < 8; i++)
	{
		TM_HD44780_Data(data[i]);
	}
}

void TM_HD44780_PutCustom(uint8_t x, uint8_t y, uint8_t location)
{
	TM_HD44780_CursorSet(x, y);
	TM_HD44780_Data(location);
}

/* Private functions */
static void TM_HD44780_Cmd(uint8_t cmd)
{
	/* Command mode */
	HD44780_RS_LOW;

	/* High nibble */
	TM_HD44780_Cmd4bit(cmd >> 4);
	/* Low nibble */
	TM_HD44780_Cmd4bit(cmd & 0x0F);
}

void TM_HD44780_Data(uint8_t data)
{
	/* Data mode */
	HD44780_RS_HIGH;

	/* High nibble */
	TM_HD44780_Cmd4bit(data >> 4);
	/* Low nibble */
	TM_HD44780_Cmd4bit(data & 0x0F);
}

static void TM_HD44780_Cmd4bit(uint8_t cmd)
{
	/* Set output port */
//	TM_GPIO_SetPinValue(HD44780_D7_GPIO_Port, HD44780_D7_Pin, (cmd & 0x08));
//	TM_GPIO_SetPinValue(HD44780_D6_GPIO_Port, HD44780_D6_Pin, (cmd & 0x04));
//	TM_GPIO_SetPinValue(HD44780_D5_GPIO_Port, HD44780_D5_Pin, (cmd & 0x02));
//	TM_GPIO_SetPinValue(HD44780_D4_GPIO_Port, HD44780_D4_Pin, (cmd & 0x01));
//
	HAL_GPIO_WritePin(HD44780_D7_GPIO_Port, HD44780_D7_Pin, (cmd & 0x08));
	HAL_GPIO_WritePin(HD44780_D6_GPIO_Port, HD44780_D6_Pin, (cmd & 0x04));
	HAL_GPIO_WritePin(HD44780_D5_GPIO_Port, HD44780_D5_Pin, (cmd & 0x02));
	HAL_GPIO_WritePin(HD44780_D4_GPIO_Port, HD44780_D4_Pin, (cmd & 0x01));

	HD44780_E_BLINK
	;
}

void TM_HD44780_CursorSet(uint8_t col, uint8_t row)
{
	uint8_t row_offsets[] =
	{ 0x00, 0x40, 0x14, 0x54 };

	/* Go to beginning */
	if (row >= HD44780_Opts.Rows)
	{
		row = 0;
	}

	/* Set current column and row */
	HD44780_Opts.currentX = col;
	HD44780_Opts.currentY = row;

	/* Set location address */
	TM_HD44780_Cmd(HD44780_SETDDRAMADDR | (col + row_offsets[row]));
}

static void TM_HD44780_InitPins(void)
{
	/* Init all pins */
//	TM_GPIO_Init(HD44780_RS_GPIO_Port, HD44780_RS_Pin, TM_GPIO_Mode_OUT,
//			TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
//	TM_GPIO_Init(HD44780_E_GPIO_Port, HD44780_E_Pin, TM_GPIO_Mode_OUT,
//			TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
//	TM_GPIO_Init(HD44780_D4_GPIO_Port, HD44780_D4_Pin, TM_GPIO_Mode_OUT,
//			TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
//	TM_GPIO_Init(HD44780_D5_GPIO_Port, HD44780_D5_Pin, TM_GPIO_Mode_OUT,
//			TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
//	TM_GPIO_Init(HD44780_D6_GPIO_Port, HD44780_D6_Pin, TM_GPIO_Mode_OUT,
//			TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
//	TM_GPIO_Init(HD44780_D7_GPIO_Port, HD44780_D7_Pin, TM_GPIO_Mode_OUT,
//			TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
	/* Set pins low */

//	TM_GPIO_SetPinLow(HD44780_RS_GPIO_Port, HD44780_RS_Pin);
//	TM_GPIO_SetPinLow(HD44780_E_GPIO_Port, HD44780_E_Pin);
//	TM_GPIO_SetPinLow(HD44780_D4_GPIO_Port, HD44780_D4_Pin);
//	TM_GPIO_SetPinLow(HD44780_D5_GPIO_Port, HD44780_D5_Pin);
//	TM_GPIO_SetPinLow(HD44780_D6_GPIO_Port, HD44780_D6_Pin);
//	TM_GPIO_SetPinLow(HD44780_D7_GPIO_Port, HD44780_D7_Pin);
	HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HD44780_E_GPIO_Port, HD44780_E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HD44780_D4_GPIO_Port, HD44780_D4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HD44780_D5_GPIO_Port, HD44780_D5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HD44780_D6_GPIO_Port, HD44780_D6_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HD44780_D7_GPIO_Port, HD44780_D7_Pin, GPIO_PIN_SET);

//	TM_GPIO_SetPinLow(HD44780_RS_GPIO_Port, HD44780_RS_Pin);
//	TM_GPIO_SetPinLow(HD44780_E_GPIO_Port, HD44780_E_Pin);
//	TM_GPIO_SetPinLow(HD44780_D4_GPIO_Port, HD44780_D4_Pin);
//	TM_GPIO_SetPinLow(HD44780_D5_GPIO_Port, HD44780_D5_Pin);
//	TM_GPIO_SetPinLow(HD44780_D6_GPIO_Port, HD44780_D6_Pin);
//	TM_GPIO_SetPinLow(HD44780_D7_GPIO_Port, HD44780_D7_Pin);
	asm("NOP");

	HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HD44780_E_GPIO_Port, HD44780_E_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HD44780_D4_GPIO_Port, HD44780_D4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HD44780_D5_GPIO_Port, HD44780_D5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HD44780_D6_GPIO_Port, HD44780_D6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HD44780_D7_GPIO_Port, HD44780_D7_Pin, GPIO_PIN_RESET);

	asm("NOP");

}

void CreateFonts()
{
	uint8_t fontData7[] =
	{ 0b00000, 0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 0b11111, 0b00000 };

	uint8_t fontData5[] =
	{ 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00 };

	TM_HD44780_CreateChar(5, fontData5);
	TM_HD44780_CreateChar(7, fontData7);
}

void LcdInit()
{
	TM_HD44780_Init(16, 2);
	CreateFonts();
}

//static const unsigned char MenuListMain[9][16] =
//	{   "01.RAINBOW     \0", "02.PATTERN - 02\0", "03.PATTERN - 03\0",
//		"04.PATTERN - 04\0", "05.PATTERN - 05\0", "06.PATTERN - 06\0",
//		"07.PATTERN - 07\0", "08.PATTERN - 08\0", "09.PATTERN - 09\0"};
//
//void ShowMenu()
//{
//	gSpeed = 0;
//	TM_HD44780_Clear();
//
//	snprintf(gLCDStrSpeedbuffer, 16, "SPEED - %.3d +\0", gSpeed);
//	TM_HD44780_Puts(0, 1, gLCDStrSpeedbuffer);
//
//	for (uint8_t i = 0; i < 8; i += 1)
//	{
//		TM_HD44780_Puts(0, 0, MenuListMain[i]);
//		//TM_HD44780_Puts(0, 1, MenuListMain[i+1]);
//		HAL_Delay(10);
//	}
//
//	//int value = 100;
//
//	for (int j = 0; j < 20; ++j)
//	{
//		gSpeed++;
//		snprintf(gLCDStrSpeedbuffer, 16, "SPEED - %.3d +\0", gSpeed);
//		TM_HD44780_Puts(0, 1, gLCDStrSpeedbuffer);
//		HAL_Delay(10);
//	}
//
//}
//
//void LCD_Update_Pattern()
//{
//	TM_HD44780_Puts(0, 0, "                ");
//	TM_HD44780_Puts(0, 0, MenuListMain[gCurMenu - 1]);
//}
//
//void LCD_Update_Speed()
//{
//	TM_HD44780_Puts(0, 1, "                ");
//	snprintf(gLCDStrSpeedbuffer, 16, "SPEED - %.3d +", gSpeed);
//	TM_HD44780_Puts(0, 1, gLCDStrSpeedbuffer);
//}
//
//void TestHD477801()
//{
//	HAL_Delay(200);
//	TM_HD44780_Init(16, 2);
//	CreateFonts();
//	TM_HD44780_Puts(0, 0, "   EVERSHINE    ");
//	TM_HD44780_Puts(0, 1, "   CREATORS     ");
//	HAL_Delay(2000);
//
//	TM_HD44780_Puts(0, 0, "   LOADING..    ");
//	TM_HD44780_Puts(0, 1, "                ");
//
//	HAL_Delay(2000);
//
//	TM_HD44780_Puts(0, 0, "    WELCOME  ");
//	TM_HD44780_Puts(0, 1, "REDSUN PVT. LTD.");
//
//	HAL_Delay(1000);
//
//	gCurMenu = 1;
//	gSpeed = 10;
//
//
//}
