/*
 * i2c_lcd_1602.c
 *
 *  Created on: Dec 15, 2018
 *      Author: shuran
 */
#include "i2c_lcd_1602.h"

HAL_StatusTypeDef LCD_SendInternal(uint8_t lcd_addr, uint8_t data,
		uint8_t flags) {
	HAL_StatusTypeDef res;
	for (;;) {
		res = HAL_I2C_IsDeviceReady(&hi2c1, lcd_addr, 1, HAL_MAX_DELAY);
		if (res == HAL_OK)
			break;
	}

	uint8_t up = data & 0xF0;
	uint8_t lo = (data << 4) & 0xF0;

	uint8_t data_arr[4];
	data_arr[0] = up | flags | _backlightval | PIN_EN;
	data_arr[1] = up | flags | _backlightval;
	data_arr[2] = lo | flags | _backlightval | PIN_EN;
	data_arr[3] = lo | flags | _backlightval;

	res = HAL_I2C_Master_Transmit(&hi2c1, lcd_addr, data_arr, sizeof(data_arr),
	HAL_MAX_DELAY);
	HAL_Delay(LCD_DELAY_MS);
	return res;
}

void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd) {
	LCD_SendInternal(lcd_addr, cmd, 0);
}

void LCD_SendData(uint8_t lcd_addr, uint8_t data) {
	LCD_SendInternal(lcd_addr, data, PIN_RS);
}

void LCD_Init(uint8_t lcd_addr) {
	_backlightval = BACKLIGHT;
	// 4-bit mode, 2 lines, 5x7 format
	LCD_SendCommand(lcd_addr, 0b00110000);
	// display & cursor home (keep this!)
	LCD_SendCommand(lcd_addr, 0b00000010);
	// display on, right shift, underline off, blink off
	LCD_SendCommand(lcd_addr, 0b00001100);
	// clear display (optional here)
	LCD_SendCommand(lcd_addr, 0b00000001);
}

//changes only var, takes effect only after any display change
void backlight_disable(){
	_backlightval = NO_BACKLIGHT;
}

//changes only var, takes effect only after any display change
void backlight_enable(){
	_backlightval = BACKLIGHT;
}

void lcd_clear(uint8_t lcd_addr) {
	LCD_SendCommand(lcd_addr, 0b00000001);
}

void LCD_SendString(uint8_t lcd_addr, char *str) {
	while (*str) {
		LCD_SendData(lcd_addr, (uint8_t) (*str));
		str++;
	}
}

void init() {
	LCD_Init(LCD_ADDR);

	// set address to 0x00
	LCD_SendCommand(LCD_ADDR, 0b10000000);
	LCD_SendString(LCD_ADDR, "..screen init...");

	// set address to 0x40
	LCD_SendCommand(LCD_ADDR, 0b11000000);
	LCD_SendString(LCD_ADDR, "  over I2C bus");
}

void lcd_send_string(uint8_t lcd_addr, char *str, int line) {
	if (line == 0) {
		LCD_SendCommand(lcd_addr, 0b10000000);
		LCD_SendString(lcd_addr, str);
	} else {
		LCD_SendCommand(lcd_addr, 0b11000000);
		LCD_SendString(lcd_addr, str);
	}
}

