/*
* Generator_output_signals.cpp
*
* Created: 09.06.2016 14:43:33
*  Author: drachevam
*/
#include "Generator_output_signals.h"
#include "arm_math.h"
#include "AD5421.h"



void Generator_output_signals::dacConverter(q31_t * src, uint32_t * dst)
{	
	//uint32_t temp = (uint32_t) src / 2147483648;
	
	uint32_t temp = 1;
	
	//dst = (uint32_t *) ( temp / (16 / 65536 - 16384));	
	
	dst = &temp;	
}


//void Generator_output_signals::Output_Amplitude(iSignal * signal)
//{	
	//
	//uint32_t dacData = 0;	
	//
	//uint8_t result = AD5421::AD5421_Init();
	//
	//for( ;; )
	//{
				//
		//Generator_output_signals::dacConverter(&signal->Amplitude, &dacData);
		//
		//AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		//
	//}
	//
//}


//void Generator_output_signals::Output_RMS(iSignal * signal)
//{
	//uint32_t dacData = 0;	
	//
	//q31_t RMS = 0;
	//
	//uint8_t result = AD5421::AD5421_Init();
	//
	//for( ;; )
	//{				
		//dacConverter(&signal->RMS, &dacData);
		//
		//AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
		//
	//}
	//
//}
//
//void Generator_output_signals::Output_PeakToPeak(iSignal * signal)
//{
	//uint32_t dacData = 0;	
			//
	//q31_t PeakToPeak = 0;
	//
	//uint8_t result = AD5421::AD5421_Init();
	//
	//for( ;; )
	//{		
		//dacConverter(&signal->PeakToPeak, &dacData);
	//
		//AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, dacData);
	//}
//}