/*
 * Sinusoid.cpp
 *
 * Created: 10.06.2016 16:18:43
 *  Author: savchenkors
 */ 

#include "Device.h"
#include "Sinusoid.h"
#include "arm_math.h"
#include "AD5421.h"

#define sampleSize 64

 
float32_t fArrSrc[sampleSize];
float32_t fArrDst[sampleSize];
q31_t qArrSrc[sampleSize];
q31_t qArrDst[sampleSize];



//в знаменателе необходимо инвертировать знаки
const float32_t pCoeffs [10] = {	

0.6413771412884,	 0,					-0.6413771412884,
					 1.972233500942,	-0.9726187287542,

0.6413771412884,	0,					-0.6413771412884,
					-0.4569532855558,	-0.2117293533411,
	
};

void Sinusoid::Sinus(void *pvParameters)
{
	
	float32_t param = 20;
	float32_t pSrc[500];
	float32_t pDst[500];
	
	arm_biquad_casd_df1_inst_f32 S;
	uint8_t numStages = 2;	
	float32_t pStates[8];
	uint32_t blockSize = 500;
	float32_t rmsResult = 0;
	
	
	TickType_t xTimeNow1;
	TickType_t xTimeNow2;
	TickType_t xTimeDiff;
	
	
	for (;;)
	{
		
		for (int i=0; i<500; i++) pSrc[i] = arm_sin_f32(param*2*PI*i/3200);	
						
		arm_rms_f32 (pSrc, blockSize, (float32_t *) &rmsResult);
		arm_biquad_cascade_df1_init_f32(&S, numStages, (float32_t *) &pCoeffs, pStates);
		arm_biquad_cascade_df1_f32(&S, pSrc, pDst, blockSize);		
		
		xTimeNow1 = xTaskGetTickCount();				
		
		arm_biquad_cascade_df1_f32(&S, pSrc, pDst, blockSize);			
		
		xTimeNow2 = xTaskGetTickCount();
		xTimeDiff = (xTimeNow2 - xTimeNow1);
		
		
		arm_rms_f32 (pDst, blockSize, (float32_t *) &rmsResult);
			
		vTaskDelay(100);
	}	
	
}


void Sinusoid::Sinus_double(void *pvParameters)
{
	
		float32_t param = 20;
		float32_t pSrc[500];
		float32_t pDst[500];
		q31_t pSrc_q31[500];
		q31_t pDst_q31[500];
		
		float32_t pCoeffs2 [10];
		q31_t pCoeffs2_q31 [10];
		
		arm_biquad_cas_df1_32x64_ins_q31 S1;		
		
		uint8_t numStages = 2;
		q63_t pStates[8];
		uint32_t blockSize = 500;
		float32_t rmsResult = 0;
		float32_t rmsResult2 = 0;
		q31_t rmsResult_q31 = 0;
		
		
		TickType_t xTimeNow1;
		TickType_t xTimeNow2;
		TickType_t xTimeDiff;
		
	
				
		for (;;)
		{
			
			for (int i=0; i<500; i++) pSrc[i] = arm_sin_f32(param*2*PI*i/3200);			
			
			for (int i=0; i<10; i++) pCoeffs2[i] = pCoeffs[i] / 2;
			
			//СКЗ исходного сигнала
			arm_rms_f32(pSrc, blockSize, (float32_t *) &rmsResult);			
			
			//Конвертируем сигнал и коэф. в q31
			arm_float_to_q31(pSrc, pSrc_q31, blockSize);			
			arm_float_to_q31(pCoeffs2, pCoeffs2_q31, 10);	
				
			
			//Масштабируем
			arm_scale_q31(pSrc_q31, 0x7FFFFFFF, -3, pSrc_q31, blockSize);			
			
			//arm_rms_q31(pSrc_q31, 80, &rmsResult_q31);		
			//arm_scale_q31((q31_t*)&rmsResult_q31, 0x7FFFFFFF, 3, &rmsResult_q31, 1);										
			//arm_q31_to_float(&rmsResult_q31, &rmsResult2, 1);						
			
			//Иниц. фильтра и первый проход
			arm_biquad_cas_df1_32x64_init_q31(&S1, numStages, (q31_t *) &pCoeffs2_q31, pStates, 1);
			arm_biquad_cas_df1_32x64_q31(&S1, pSrc_q31, pDst_q31, blockSize);							
						
			xTimeNow1 = xTaskGetTickCount();	
			
			//Фильтруем
			arm_biquad_cas_df1_32x64_q31(&S1, pSrc_q31, pDst_q31, blockSize);													
			
			xTimeNow2 = xTaskGetTickCount();
			xTimeDiff = (xTimeNow2 - xTimeNow1);
			
			//Масштабируем обратно
			arm_scale_q31(pDst_q31, 0x7FFFFFFF, 3, pDst_q31, blockSize);			
			
			//Конвертируем обратно в float
			arm_q31_to_float(pDst_q31, pDst, blockSize);
									
			//СКЗ отфильтрованного сигнала									
			arm_rms_f32 (pDst, blockSize, (float32_t *) &rmsResult2);			
			
			vTaskDelay(100);
		}
	
}

void Sinusoid::Sinus_make32points(void *pvParameters)
{
	float32_t param = 20;
	float32_t rmsResult = 0;
	
	for (int i=0; i<sampleSize; i++) fArrSrc[i] = arm_sin_f32(param*2*PI*i/3200);
		
	arm_rms_f32 (fArrSrc, sampleSize, &rmsResult);	
	
	//Конвертируем сигнал и коэф. в q31
	arm_float_to_q31(fArrSrc, qArrSrc, sampleSize);
		
	
	for (;;)
	{	
	
		//Посылает уведомление
		xTaskNotifyGive( Device::xTask2 );
		
		//Принимает
		//ulTaskNotifyTake(pdTRUE, portMAX_DELAY);	
		
		vTaskDelay(20);
	}
	
}

void Sinusoid::Sinus_filter32points(void *pvParameters)
{
	//arm_biquad_cas_df1_32x64_ins_q31 S;		
	arm_biquad_casd_df1_inst_q31 S;
	q31_t coef_q31[10];
	float32_t coef_float[10];
	q63_t pStates[8];
	q31_t pStates_q31[8];
	q31_t rms_q31 = 0;
	float32_t rms_float = 0;
	q31_t maxValue_q31 = 0;
	q31_t minValue_q31 = 0;
	float32_t maxValue_float = 0;
	float32_t minValue_float = 0;	
	uint32_t maxValueIndex = 0;
	uint32_t minValueIndex = 0;
	uint32_t fault_reg = 0;
	
	for (int i=0; i<10; i++) coef_float[i] = pCoeffs[i] / 2;
	arm_float_to_q31(coef_float, coef_q31, 10);		
	//arm_biquad_cas_df1_32x64_init_q31(&S, 2, (q31_t*)&coef_q31, pStates, 1);
	arm_biquad_cascade_df1_init_q31(&S, 2, (q31_t*)&coef_q31, pStates_q31, 1);
	
	
	
	for( ;; )
    {        
      			
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		
		//xTaskNotifyGive( Device::xTask1 );				  
		
		
		//Масштабируем
		arm_scale_q31(qArrSrc, 0x7FFFFFFF, -3, qArrSrc, sampleSize);	
		
		//Иниц. фильтра		
		arm_biquad_cascade_df1_fast_q31(&S, qArrSrc, qArrSrc, sampleSize);
		//arm_biquad_cas_df1_32x64_q31(&S, qArrSrc, qArrSrc, sampleSize);
		//arm_biquad_cas_df1_32x64_q31(&S, qArrSrc, qArrSrc, sampleSize);
		
		//Считаем СКЗ
		arm_rms_q31(qArrSrc, sampleSize/5, &rms_q31);
		//arm_q31_to_float(&rms_q31, &rms_float, 1);
		
		//Считаем ПИК
		arm_max_q31(qArrSrc, sampleSize, &maxValue_q31, &maxValueIndex);
		//arm_q31_to_float(&maxValue_q31, &maxValue_float, 1);
		arm_min_q31(qArrSrc, sampleSize, &minValue_q31, &minValueIndex);
		//arm_q31_to_float(&minValue_q31, &minValue_float, 1);
		
		//Масштабируем обратно
		arm_scale_q31(qArrSrc, 0x7FFFFFFF, 3, qArrSrc, sampleSize);		
		
		
		
		//AD5421
		//maxValueIndex = AD5421::AD5421_GetTemperature();
		//AD5421::AD5421_SetRegisterValue(AD5421_REG_DAC_DATA, 0);		
		//fault_reg = AD5421::AD5421_GetRegisterValue(AD5421_REG_FAULT);
		//fault_reg = AD5421::AD5421_GetRegisterValue(AD5421_REG_CTRL);		
		//AD5421::AD5421_SetRegisterValue(AD5421_REG_LOAD_DAC, 0x1);
		
				
	}
	
}