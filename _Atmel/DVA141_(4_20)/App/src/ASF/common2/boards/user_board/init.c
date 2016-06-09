/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

static void init_gpio(void)
{
	
	struct port_config pin;
	port_get_config_defaults(&pin);
	
	pin.direction = PORT_PIN_DIR_INPUT;
	pin.input_pull = PORT_PIN_PULL_DOWN;
	port_pin_set_config(PIN_PA00, &pin);
	
	pin.direction = PORT_PIN_DIR_INPUT;
	pin.input_pull = PORT_PIN_PULL_DOWN;
	port_pin_set_config(PIN_PA01, &pin);
	
	pin.direction = PORT_PIN_DIR_INPUT;
	pin.input_pull = PORT_PIN_PULL_NONE;
	port_pin_set_config(PIN_PA02, &pin);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA03, &pin);
	port_pin_set_output_level(PIN_PA03, 0);
	
	//pin.direction = PORT_PIN_DIR_INPUT;
	//pin.input_pull = PORT_PIN_PULL_NONE;
	//port_pin_set_config(PIN_PA03, &pin);
	
	//pin.direction = PORT_PIN_DIR_OUTPUT;
	//port_pin_set_config(PIN_PA04, &pin);
	//port_pin_set_output_level(PIN_PA04, 0);
	//
	//pin.direction = PORT_PIN_DIR_OUTPUT;
	//port_pin_set_config(PIN_PA05, &pin);
	//port_pin_set_output_level(PIN_PA05, 0);
	//
	//pin.direction = PORT_PIN_DIR_INPUT;
	//pin.input_pull = PORT_PIN_PULL_NONE;
	//port_pin_set_config(PIN_PA06, &pin);
	//
	//pin.direction = PORT_PIN_DIR_INPUT;
	//pin.input_pull = PORT_PIN_PULL_UP;
	//port_pin_set_config(PIN_PA07, &pin);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA08, &pin);
	port_pin_set_output_level(PIN_PA08, 1);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA09, &pin);
	port_pin_set_output_level(PIN_PA09, 1);
	
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA10, &pin);
	port_pin_set_output_level(PIN_PA10, 1);
	
	pin.direction = PORT_PIN_DIR_INPUT;
	pin.input_pull = PORT_PIN_PULL_NONE;
	port_pin_set_config(PIN_PA11, &pin);
	
	
	//pin.direction = PORT_PIN_DIR_OUTPUT;
	//port_pin_set_config(PIN_PA16, &pin);
	//port_pin_set_output_level(PIN_PA16, 0);
	//
	//pin.direction = PORT_PIN_DIR_OUTPUT;
	//port_pin_set_config(PIN_PA17, &pin);
	//port_pin_set_output_level(PIN_PA17, 0);
	//
	//pin.direction = PORT_PIN_DIR_OUTPUT;
	//port_pin_set_config(PIN_PA18, &pin);
	//port_pin_set_output_level(PIN_PA18, 0);
	//
	//pin.direction = PORT_PIN_DIR_INPUT;
	//pin.input_pull = PORT_PIN_PULL_NONE;
	//port_pin_set_config(PIN_PA19, &pin);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA22, &pin);
	port_pin_set_output_level(PIN_PA22, 0);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA24, &pin);
	port_pin_set_output_level(PIN_PA24, 0);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA27, &pin);
	port_pin_set_output_level(PIN_PA27, 0);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA30, &pin);
	port_pin_set_output_level(PIN_PA30, 0);
	
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA31, &pin);
	port_pin_set_output_level(PIN_PA31, 0);
	
}

void system_board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	init_gpio();
	
}