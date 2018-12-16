added 2 libs: 
i2c_lcd_1602 - for display 
i2c_scan - for i2c bus scanner

both libs should work independently remember that you need UART for i2c_scan

!!! hi2c1 value in i2c_lcd_1602 and i2c_scan should be as in the generated value "I2C_HandleTypeDef hi2c1;" in i2c.c file !!!