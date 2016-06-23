/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <AD5421/ad5421.h>
#include <ADXL/ADXL346.h>
#include <task1.h>

#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )


//AD5421
struct spi_module spi_master_instance_AD5421;
struct spi_slave_inst slave_AD5421;
//ADXL
struct spi_module spi_master_instance_ADXL;
struct spi_module spi_slave_instance_ADXL;
struct spi_slave_inst slave_ADXL;

volatile float X = 1;
volatile float Y = 1;
volatile float Z = 1;

volatile float *XX = 1;
volatile float *YY = 1;
volatile float *ZZ = 1;

volatile uint8_t T = 0;

//DMA
struct dma_resource dma_resource_tx;
struct dma_resource dma_resource_rx;

COMPILER_ALIGNED(16)
DmacDescriptor dma_descriptor_tx;
DmacDescriptor dma_descriptor_rx;

static volatile bool transfer_tx_is_done = false;
static volatile bool transfer_rx_is_done = false;

#define CONF_PERIPHERAL_TRIGGER_TX   SERCOM2_DMAC_ID_TX
#define CONF_PERIPHERAL_TRIGGER_RX   SERCOM0_DMAC_ID_RX

uint8_t buffer_tx[30];
uint8_t buffer_rx[32];


volatile float buffer_x[32];
volatile float buffer_y[32];
volatile float buffer_z[32];



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
	
	//pin.direction = PORT_PIN_DIR_OUTPUT;
	//port_pin_set_config(PIN_PA22, &pin);
	//port_pin_set_output_level(PIN_PA22, 0);
	
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

static void clock_output(void)
{
	/* Configure a GPIO pin as the CPU clock output */
	struct system_pinmux_config clk_out_pin;
	system_pinmux_get_config_defaults(&clk_out_pin);
	clk_out_pin.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	clk_out_pin.mux_position = MUX_PA22H_GCLK_IO6;	
	system_pinmux_pin_set_config(PIN_PA22H_GCLK_IO6, &clk_out_pin);	
	
}


void configure_spi_master_AD5421(void)
{
	//! [config]
	struct spi_config config_spi_master;
	//! [config]
	//! [slave_config]
	struct spi_slave_inst_config slave_dev_config;
	//! [slave_config]
	/* Configure and initialize software device instance of peripheral slave */
	//! [slave_conf_defaults]
	spi_slave_inst_get_config_defaults(&slave_dev_config);
	//! [slave_conf_defaults]
	//! [ss_pin]
	slave_dev_config.ss_pin = PIN_PA18;
	slave_dev_config.address_enabled = false;
	//! [ss_pin]
	//! [slave_init]
	spi_attach_slave(&slave_AD5421, &slave_dev_config);
	//! [slave_init]
	/* Configure, initialize and enable SERCOM SPI module */
	//! [conf_defaults]
	spi_get_config_defaults(&config_spi_master);
	//! [conf_defaults]
	//! [mux_setting]
	config_spi_master.mux_setting = SPI_SIGNAL_MUX_SETTING_D;
	//! [mux_setting]
	
	/* Configure pad 0 for MOSI */
	//! [di]
	config_spi_master.pinmux_pad0 =  PINMUX_PA16D_SERCOM3_PAD0;
	//! [di]
	/* Configure pad 1 for CLOCK */
	//! [ss]
	config_spi_master.pinmux_pad1 = PINMUX_PA17D_SERCOM3_PAD1;
	//! [ss]
	/* Configure pad 2 for CS */
	//! [do]
	config_spi_master.pinmux_pad2 = PINMUX_UNUSED;
	//! [do]
	/* Configure pad 3 for MISO */
	//! [sck]
	config_spi_master.pinmux_pad3 = PINMUX_PA19D_SERCOM3_PAD3;
	//! [sck]
	
	
	config_spi_master.mode             = SPI_MODE_MASTER;
	config_spi_master.data_order       = SPI_DATA_ORDER_MSB;
	config_spi_master.transfer_mode    = SPI_TRANSFER_MODE_2;
	config_spi_master.character_size   = SPI_CHARACTER_SIZE_8BIT;
	config_spi_master.run_in_standby   = false;
	config_spi_master.receiver_enable  = true;
	config_spi_master.generator_source = GCLK_GENERATOR_2;
	config_spi_master.mode_specific.master.baudrate = 1000000;
	config_spi_master.master_slave_select_enable = true;
	config_spi_master.select_slave_low_detect_enable = false;
	
	//! [init]
	spi_init(&spi_master_instance_AD5421, SERCOM3, &config_spi_master);
	//! [init]

	//! [enable]
	spi_enable(&spi_master_instance_AD5421);
	//! [enable]

}

void configure_spi_master_ADXL(void)
{
	
	struct spi_config config_spi_master_adxl;
	
	struct spi_slave_inst_config slave_dev_config_adxl;
	
	spi_slave_inst_get_config_defaults(&slave_dev_config_adxl);
	
	slave_dev_config_adxl.ss_pin = PIN_PA06;
	slave_dev_config_adxl.address_enabled = false;
	
	spi_attach_slave(&slave_ADXL, &slave_dev_config_adxl);
	
	spi_get_config_defaults(&config_spi_master_adxl);
	
	config_spi_master_adxl.mux_setting = SPI_SIGNAL_MUX_SETTING_D;	
	config_spi_master_adxl.pinmux_pad0 =  PINMUX_PA04D_SERCOM0_PAD0;	
	config_spi_master_adxl.pinmux_pad1 = PINMUX_PA05D_SERCOM0_PAD1;	
	config_spi_master_adxl.pinmux_pad2 = PINMUX_UNUSED;	
	
	
	config_spi_master_adxl.pinmux_pad3 = PINMUX_PA07D_SERCOM0_PAD3;
		
	config_spi_master_adxl.mode             = SPI_MODE_MASTER;
	config_spi_master_adxl.data_order       = SPI_DATA_ORDER_MSB;
	config_spi_master_adxl.transfer_mode    = SPI_TRANSFER_MODE_3;
	config_spi_master_adxl.character_size   = SPI_CHARACTER_SIZE_8BIT;
	config_spi_master_adxl.run_in_standby   = false;
	config_spi_master_adxl.receiver_enable  = true;
	config_spi_master_adxl.generator_source = GCLK_GENERATOR_2;
	config_spi_master_adxl.mode_specific.master.baudrate = 4000000;
	config_spi_master_adxl.master_slave_select_enable = true;
	config_spi_master_adxl.select_slave_low_detect_enable = false;
		
	spi_init(&spi_master_instance_ADXL, SERCOM0, &config_spi_master_adxl);
		
	spi_enable(&spi_master_instance_ADXL);
	

}

void SPI_Write_AD5421(uint8_t* data)
{
	port_pin_set_output_level(PIN_PA18, 0);
	spi_write_buffer_wait(&spi_master_instance_AD5421, data, 3);
	port_pin_set_output_level(PIN_PA18, 1);
}

void SPI_Read_AD5421(uint8_t* data)
{
	port_pin_set_output_level(PIN_PA18, 0);
	//spi_read_buffer_wait(&spi_master_instance_AD5421, data, 3, 0);
	spi_transceive_buffer_wait(&spi_master_instance_AD5421, data, data, 3);
	port_pin_set_output_level(PIN_PA18, 1);	
}

void SPI_Write_ADXL(uint8_t* data)
{
	port_pin_set_output_level(PIN_PA06, 0);
	spi_write_buffer_wait(&spi_master_instance_ADXL, data, 2);	
	port_pin_set_output_level(PIN_PA06, 1);
}

void SPI_Read_ADXL(uint8_t* data)
{	
	port_pin_set_output_level(PIN_PA06, 0);
	//spi_read_buffer_wait(&spi_master_instance_ADXL, data, 2, 0);
	spi_transceive_buffer_wait(&spi_master_instance_ADXL, data, data, 2);
	port_pin_set_output_level(PIN_PA06, 1);
}




void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;

	extint_chan_get_config_defaults(&config_extint_chan);

	config_extint_chan.gpio_pin           = PIN_PA02A_EIC_EXTINT2;
	config_extint_chan.gpio_pin_mux       = PINMUX_PA02A_EIC_EXTINT2;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;

	extint_chan_set_config(2, &config_extint_chan);
}


void extint_detection_callback_1(void)
{
	
	
	//volatile bool state = false;
	//state = port_pin_get_output_level(PIN_PA22);
	//
	//if (state == false) port_pin_set_output_level(PIN_PA22, 1);
	//else port_pin_set_output_level(PIN_PA22, 0);
	
	//delay_us(1);
	//port_pin_set_output_level(PIN_PA22, 0);
	
	//T = ADXL345_GetRegisterValue(0x30);
	//port_pin_set_output_level(PIN_PA27, T<<6);
	//
	//port_pin_set_output_level(PIN_PA22, 1);
	//
	//for(int i=0; i<32; i++)
	//{			
		//buffer_x[i] = ADXL345_GetX();					 
		//buffer_y[i] = ADXL345_GetY();
		//buffer_z[i] = ADXL345_GetZ();		
	//}
	//
	//port_pin_set_output_level(PIN_PA22, 0);
	
	//X = ADXL345_GetX();
	//Y = ADXL345_GetY();
	//Z = ADXL345_GetZ();
	
}

void configure_extint_callbacks(void)
{
	extint_register_callback(extint_detection_callback_1, 2, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(2, EXTINT_CALLBACK_TYPE_DETECT);
}




static void configure_dma_resource_tx(struct dma_resource *tx_resource)
{	
	struct dma_resource_config tx_config;	
	
	dma_get_config_defaults(&tx_config);	

	tx_config.peripheral_trigger = CONF_PERIPHERAL_TRIGGER_TX;
	tx_config.trigger_action = DMA_TRIGGER_ACTION_BEAT;	

	dma_allocate(tx_resource, &tx_config);	
}

static void configure_dma_resource_rx(struct dma_resource *rx_resource)
{
	struct dma_resource_config rx_config;
	dma_get_config_defaults(&rx_config);
	rx_config.peripheral_trigger = CONF_PERIPHERAL_TRIGGER_RX;
	rx_config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	dma_allocate(rx_resource, &rx_config);
}


static void setup_transfer_descriptor_tx(DmacDescriptor *tx_descriptor)
{
	struct dma_descriptor_config tx_descriptor_config;	
	dma_descriptor_get_config_defaults(&tx_descriptor_config);	
	tx_descriptor_config.beat_size = DMA_BEAT_SIZE_BYTE;
	tx_descriptor_config.dst_increment_enable = false;
	tx_descriptor_config.block_transfer_count = sizeof(buffer_tx)/sizeof(uint8_t);
	tx_descriptor_config.source_address = (uint32_t)buffer_tx + sizeof(buffer_tx);
	tx_descriptor_config.destination_address = (uint32_t)(&spi_master_instance_ADXL.hw->SPI.DATA.reg);	
	dma_descriptor_create(tx_descriptor, &tx_descriptor_config);	
}



static void setup_transfer_descriptor_rx(DmacDescriptor *rx_descriptor)
{
	struct dma_descriptor_config rx_descriptor_config;
	
	dma_descriptor_get_config_defaults(&rx_descriptor_config);	
	
	rx_descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;	
	rx_descriptor_config.src_increment_enable = false;	
	rx_descriptor_config.block_transfer_count = 64;
	///rx_descriptor_config.block_transfer_count = sizeof(buffer_rx)/sizeof(buffer_rx);
	rx_descriptor_config.source_address = (uint32_t)(ADXL345_DATAX0 | ADXL345_SPI_READ);
	//rx_descriptor_config.source_address = (uint32_t)(&spi_master_instance_ADXL.hw->SPI.DATA.reg);
	rx_descriptor_config.destination_address = (uint32_t)buffer_x;
	//rx_descriptor_config.destination_address = (uint32_t)buffer_rx + sizeof(buffer_rx);
	
	dma_descriptor_create(rx_descriptor, &rx_descriptor_config);	
}

static void transfer_tx_done(struct dma_resource* const resource )
{
	transfer_tx_is_done = true;
}

static void transfer_rx_done(struct dma_resource* const resource )
{
	transfer_rx_is_done = true;
}



int main (void)
{
	volatile char temp = 1;
	volatile uint16_t temp1 = 1;
	volatile uint16_t temp2 = 1;
	volatile bool state = false;
	
	system_init();
	
	init_gpio();

	clock_output();
	
	delay_init();	
		
	configure_spi_master_AD5421();
	configure_spi_master_ADXL();
	
	AD5421_Init();	
	ADXL345_Init();
	
	//configure_extint_channel();		
	//configure_extint_callbacks();	
	//system_interrupt_enable_global();
	

	
	xTaskCreate(Testtask, "Testtask", configMINIMAL_STACK_SIZE, (void *)100, mainQUEUE_SEND_TASK_PRIORITY, NULL);
	vTaskStartScheduler();
	

	
	
	//X = ADXL345_GetX();
 	//Y = ADXL345_GetY();
 	//Z = ADXL345_GetZ();
	
}
