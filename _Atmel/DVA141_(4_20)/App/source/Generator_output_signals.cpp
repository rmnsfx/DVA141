/*
* Generator_output_signals.cpp
*
* Created: 09.06.2016 14:43:33
*  Author: drachevam
*/
#include "Generator_output_signals.h"
#include "AD5421.h"
#include "arm_math.h"

#include "os_wrapper.h"


void Generator_output_signals::SetCurrent(uint16_t value)
{
		port_pin_set_output_level(PIN_PA24, 0);
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, value);
		port_pin_set_output_level(PIN_PA24, 1);
}

Generator_output_signals::Generator_output_signals(void)
{
	AD5421::AD5421_Init();
}

Generator_output_signals::~Generator_output_signals(void)
{

}

uint32_t Generator_output_signals::dacConverter(q31_t &src)
{
	return 0;
	float32_t temp1 = 0.0;
	float32_t temp2 = 0.0;
	
	arm_q31_to_float(&src, &temp1, 1);
	
	temp1 *= sampleScale;
	
	temp2 = sampleScale / (float32_t) 65535;
	//temp2 = 16 / (float32_t) (65536 - 16384);
	return (uint32_t) (temp1 / temp2);
}

void Generator_output_signals::main()
{
	os_wrapper& os = *os_wrapper::getInstance();
	Axelerometr& axel = *Axelerometr::getInstance();
	q31_t value;
	uint16_t val_reg = 0;
	uint16_t dacData = 32768;
	AD5421::AD5421_SetRegisterValue(AD5421_REG_OFFSET, dacData);
	dacData = 65535;
	AD5421::AD5421_SetRegisterValue(AD5421_REG_GAIN, dacData);
	for (;;)
	{
		os.delay(100);
		value = axel.Z().A().Amplitude();
		dacData = Generator_output_signals::dacConverter(value) ; 
		SetCurrent(dacData);		
		val_reg = AD5421::AD5421_GetRegisterValue(AD5421_REG_OFFSET);
		val_reg = AD5421::AD5421_GetRegisterValue(AD5421_REG_GAIN);
		val_reg = AD5421::AD5421_GetRegisterValue(AD5421_REG_DAC_DATA);		
	}
}



void Generator_output_signals::loadDAC()
{
	port_pin_set_output_level(PIN_PA24, 0);
	//os_wrapper& os = *os_wrapper::getInstance();
	//os.delay(1);
	for(int i=0; i<2500; i++){};
	port_pin_set_output_level(PIN_PA24, 1);
}


void Generator_output_signals::outputAmplitude(iSignal &signal)
{
	
	uint32_t dacData = 0;
	
	uint8_t result = AD5421::AD5421_Init();
	q31_t value;
	for( ;; )
	{
		value = signal.Amplitude();
		dacData = Generator_output_signals::dacConverter(value);
		
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		loadDAC();
	}
	
}


void Generator_output_signals::outputRMS(iSignal &signal)
{
	uint32_t dacData = 0;
	
	uint8_t result = AD5421::AD5421_Init();
	q31_t value = 0;
	for( ;; )
	{
		value = signal.RMS();
		dacData = Generator_output_signals::dacConverter(value);
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		loadDAC();
	}
	
}



void Generator_output_signals::outputPeakToPeak(iSignal &signal)
{
	uint32_t dacData = 0;
	
	uint8_t result = AD5421::AD5421_Init();
	q31_t value = 0;
	for( ;; )
	{
		value = signal.PeakToPeak();
		dacData = Generator_output_signals::dacConverter(value);
		
		AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		
		loadDAC();
	}
}