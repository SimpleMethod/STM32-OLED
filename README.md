
# STM32 OLED

Library written in C to STM32 language with HAL support for OLED displays with WS0010/RS0010 controller.


## Display control

**Display operates in 4-bit mode with disabled R/W operation.**



![Salease Logic ](https://raw.githubusercontent.com/SimpleMethod/STM32-OLED/master/images/Logic.png "Salease Logic")

## Circuit diagram
![Connection diagram](https://raw.githubusercontent.com/SimpleMethod/STM32-OLED/master/images/Sketch.png "Connection diagram")


## STM32 configuration

```markdown
| PERIPHERALS | MODES        | FUNCTIONS      | PINS              |
|-------------|--------------|----------------|-------------------|
| SYS         | SysTick      | SYS_VS_Systick | VP_SYS_VS_Systick |
| USART2      | Asynchronous | USART2_RX      | PA3               |
| USART2      | Asynchronous | USART2_TX      | PA2               |
```

```markdown
| Pin Nb | PINs           | FUNCTIONs   | LABELs               |
|--------|----------------|-------------|----------------------|
| 2      | PC13-ANTI_TAMP | GPIO_EXTI13 | B1 [Blue PushButton] |
| 8      | PC0            | GPIO_Output | OLED_RS              |
| 9      | PC1            | GPIO_Output | OLED_E               |
| 14     | PA0-WKUP       | GPIO_Output | OLED_D7              |
| 15     | PA1            | GPIO_Output | OLED_D6              |
| 16     | PA2            | USART2_TX   | USART_TX             |
| 17     | PA3            | USART2_RX   | USART_RX             |
| 20     | PA4            | GPIO_Output | OLED_D5              |
| 21     | PA5            | GPIO_Output | LD2 [Green Led]      |
| 26     | PB0            | GPIO_Output | OLED_D4              |
```



## Example of use

	Oled_HandleTypeDef oled;

	GPIO_TypeDef* data_ports[] = { OLED_D4_GPIO_Port, OLED_D5_GPIO_Port,
	OLED_D6_GPIO_Port, OLED_D7_GPIO_Port };

	uint16_t data_pins[] ={ OLED_D4_Pin, OLED_D5_Pin, OLED_D6_Pin, OLED_D7_Pin };

	oled= Oled_init(OLED_RS_GPIO_Port, OLED_RS_Pin,
	OLED_E_GPIO_Port, OLED_E_Pin, data_ports, data_pins);
	
	Oled_cursor(&oled, 0, 2);
	Oled_string(&oled, "Hello ");

	Oled_cursor(&oled, 1, 8);
	Oled_string(&oled, "world!");

	Oled_cursor(&oled, 1, 14);
	Oled_blink(&oled);


## List of available functions 

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
