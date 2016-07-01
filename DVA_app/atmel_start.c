/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "atmel_start.h"
#include <utils.h>
#include <hal_init.h>
#include <hpl_irq.h>
#include <hri_gclk2_v111.h>
#include <hri_mclk_v101.h>
#include <peripheral_gclk_config.h>

extern struct _irq_descriptor *_irq_table[PERIPH_COUNT_IRQn];
extern void Default_Handler(void);

void MCLK_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void OSCCTRL_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void OSC32KCTRL_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void DMAC_Handler(void)
{
	if (_irq_table[ DMAC_IRQn + 0 ]) {
		_irq_table[ DMAC_IRQn + 0 ]->handler(
				_irq_table[ DMAC_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}

void system_init(void)
{
	init_mcu();
}
