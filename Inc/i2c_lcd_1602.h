/*
 * i2c_lcd_1602.h
 *
 *  Created on: Dec 15, 2018
 *      Author: shuran
 */

#ifndef I2C_LCD_1602_H_
#define I2C_LCD_1602_H_

#endif /* I2C_LCD_1602_H_ */

#include "i2c.h"
#include "gpio.h"
#include <string.h>

#define LCD_ADDR (0x27 << 1)

#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3) //0x00001000 = on, 0x00000000 = off
#define NO_BACKLIGHT 0x00

#define LCD_DELAY_MS 5

uint8_t _backlightval;

HAL_StatusTypeDef LCD_SendInternal(uint8_t lcd_addr, uint8_t data, uint8_t flags);

void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd);

void LCD_SendData(uint8_t lcd_addr, uint8_t data);

void LCD_Init(uint8_t lcd_addr);

void lcd_clear(uint8_t lcd_addr);

void LCD_SendString(uint8_t lcd_addr, char *str);

void init();

void lcd_send_string(uint8_t lcd_addr, char *str, int line);

void backlight_disable();

void backlight_enable();
