/*
 * Oled_WS0010.c
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

#include "Oled_WS0010.h"

Oled_HandleTypeDef Oled_init(GPIO_TypeDef* rs_port, uint16_t rs_pin,
		GPIO_TypeDef* en_port, uint16_t en_pin, GPIO_TypeDef* data_port[],
		uint16_t data_pin[]) {
	Oled_HandleTypeDef oled;
	oled.rs_pin = rs_pin;
	oled.rs_port = rs_port;
	oled.enable_pin = en_pin;
	oled.enable_port = en_port;
	oled.data_pin = data_pin;
	oled.data_port = data_port;

	Oled_writeCommand(&oled, 0x33);
	Oled_writeCommand(&oled, 0x32);
	Oled_writeCommand(&oled, 0x28);
	Oled_writeCommand(&oled, 0x01);
	Oled_writeCommand(&oled, 0x08 | 0x04);
	Oled_writeCommand(&oled, 0x04 | 0x02);

	//WS0010
	Oled_writeCommand(&oled, 0x08);
	Oled_writeCommand(&oled, 0x17);
	Oled_writeCommand(&oled, 0x01);
	Oled_writeCommand(&oled, 0x04 | 0x08);
	Oled_writeCommand(&oled, OLED_CLEAR_DISPLAY);

	return oled;
}

void Oled_int(Oled_HandleTypeDef *oled, int value) {
	char buf[17];
	sprintf(buf, "%d", value);
	Oled_string(oled, buf);
}

void Oled_cursor(Oled_HandleTypeDef *oled, uint8_t row, uint8_t col) {
	uint8_t ROW[] = { 0x00, 0x40, 0x10, 0x50 };
	Oled_writeCommand(oled, 0x80 + ROW[row] + col);
}

void Oled_autoScroll(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, OLED_ENTRYMODESET | OLED_ENTRY_SHIFT_INCREMENT);
}

void Oled_blink(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, 0x08 | 0x04 | 0x02 | 0x01);
}

void Oled_clear(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, OLED_CLEAR_DISPLAY);
}


void Oled_HEX(Oled_HandleTypeDef *oled, int value, uint8_t upper_case) {
	char buf[17];
	if (upper_case)
		sprintf(buf, "%X", value);
	else
		sprintf(buf, "%x", value);
	Oled_string(oled, buf);
}

void Oled_home(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, 0x03);
}

void Oled_leftToRight(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, OLED_ENTRYMODESET | OLED_ENTRYRIGHT);
}

void Oled_noAutoScroll(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, OLED_ENTRYMODESET | OLED_ENTRY_SHIFT_INCREMENT0);
}

void Oled_noBlink(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, 0x08 | 0x04);
}

void Oled_rightToLeft(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled, OLED_ENTRYMODESET | OLED_ENTRYLEFT);
}

void Oled_scrollDisplayLeft(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled,
	OLED_CURSORSHIFT | OLED_DISPLAYMOVE | OLED_MOVELEFT);
}

void Oled_scrollDisplayRight(Oled_HandleTypeDef *oled) {
	Oled_writeCommand(oled,
	OLED_CURSORSHIFT | OLED_DISPLAYMOVE | OLED_MOVERIGHT);
}

void Oled_setGraphicCursor(Oled_HandleTypeDef *oled, uint8_t x, uint8_t y) {
	if (0 <= x && x <= 100) {
		Oled_writeCommand(oled, 0x80 | x);
	}
	if (0 <= y && y <= 1) {
		Oled_writeCommand(oled, 0x80 | y);
	}
}

void Oled_string(Oled_HandleTypeDef *oled, char * string) {
	char temp;
	while ((temp = *string++)) {
		Oled_writeData(oled, temp);
	}
}

void Oled_write(Oled_HandleTypeDef *oled, uint8_t data) {

	HAL_GPIO_WritePin(oled->data_port[0], oled->data_pin[0], data & (1 << 0));
	HAL_GPIO_WritePin(oled->data_port[1], oled->data_pin[1], data & (1 << 1));
	HAL_GPIO_WritePin(oled->data_port[2], oled->data_pin[2], data & (1 << 2));
	HAL_GPIO_WritePin(oled->data_port[3], oled->data_pin[3], data & (1 << 3));
	HAL_GPIO_WritePin(oled->enable_port, oled->enable_pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(oled->enable_port, oled->enable_pin, 0);
}

void Oled_writeCommand(Oled_HandleTypeDef *oled, uint8_t command) {
	HAL_GPIO_WritePin(oled->rs_port, oled->rs_pin, 0);
	Oled_write(oled, (command >> 4));
	Oled_write(oled, command & 0x0F);

}

void Oled_writeData(Oled_HandleTypeDef *oled, uint8_t data) {
	HAL_GPIO_WritePin(oled->rs_port, oled->rs_pin, 1);
	Oled_write(oled, data >> 4);
	Oled_write(oled, data & 0x0F);

}
