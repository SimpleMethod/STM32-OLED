/*
 * OLED_WS0010.h
 *
 *  Created on: 30.06.2019
 *      Author: SimpleMethod
 *
 *Copyright 2019 SimpleMethod
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy of
 *this software and associated documentation files (the "Software"), to deal in
 *the Software without restriction, including without limitation the rights to
 *use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *of the Software, and to permit persons to whom the Software is furnished to do
 *so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
******************************************************************************
*/

#ifndef OLED_WS0010_H_
#define OLED_WS0010_H_

#include "stm32f4xx_hal.h"
#include "string.h"
#include "main.h"

#define OLED_CLEAR_DISPLAY 0x01
#define OLED_CURSORSHIFT 0x10
#define OLED_DISPLAYMOVE 0x08
#define OLED_ENTRY_SHIFT_INCREMENT 0x01
#define OLED_ENTRY_SHIFT_INCREMENT0 0x00
#define OLED_ENTRYLEFT 0x02
#define OLED_ENTRYMODESET 0x04
#define OLED_ENTRYRIGHT 0x00
#define OLED_MOVELEFT 0x00
#define OLED_MOVERIGHT 0x04


typedef struct {
	GPIO_TypeDef* rs_port;
	uint16_t rs_pin;

	GPIO_TypeDef* enable_port;
	uint16_t enable_pin;

	GPIO_TypeDef* *data_port;
	uint16_t *data_pin;

} Oled_HandleTypeDef;
Oled_HandleTypeDef Oled_init(GPIO_TypeDef* rs_port, uint16_t rs_pin,
		GPIO_TypeDef* en_port, uint16_t en_pin, GPIO_TypeDef* data_port[],
		uint16_t data_pin[]);
void Oled_autoScroll(Oled_HandleTypeDef *oled);
void Oled_blink(Oled_HandleTypeDef *oled);
void Oled_clear(Oled_HandleTypeDef *oled);
void Oled_cursor(Oled_HandleTypeDef *oled, uint8_t row, uint8_t col);
void Oled_HEX(Oled_HandleTypeDef *oled, int value, uint8_t upper_case);
void Oled_home(Oled_HandleTypeDef *oled);
void Oled_int(Oled_HandleTypeDef *oled, int value);
void Oled_leftToRight(Oled_HandleTypeDef *oled);
void Oled_noAutoScroll(Oled_HandleTypeDef *oled);
void Oled_noBlink(Oled_HandleTypeDef *oled);
void Oled_rightToLeft(Oled_HandleTypeDef *oled);
void Oled_scrollDisplayLeft(Oled_HandleTypeDef *oled);
void Oled_scrollDisplayRight(Oled_HandleTypeDef *oled);
void Oled_setGraphicCursor(Oled_HandleTypeDef *oled, uint8_t x, uint8_t y);
void Oled_string(Oled_HandleTypeDef *oled, char * string);
void Oled_write(Oled_HandleTypeDef *oled, uint8_t data);
void Oled_writeCommand(Oled_HandleTypeDef *oled, uint8_t command);
void Oled_writeData(Oled_HandleTypeDef *oled, uint8_t data);

#endif /* OLED_WS0010_H_ */
