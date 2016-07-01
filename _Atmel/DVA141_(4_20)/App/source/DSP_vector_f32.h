#pragma once

#include "DSP_vector_base.h"
#include "arm_math.h"

namespace DSP
{
	class DSP_vector_f32 : public DSP_vector_base<float32_t>
	{
		//		explicit DSP_vector_f32() : DSP_vector_base<float32_t>(){};
	public:
		explicit DSP_vector_f32(size_t size) : DSP_vector_base<float32_t>(size){};
		explicit DSP_vector_f32(size_t size, float32_t value) : DSP_vector_base<float32_t>(size, value){};
		inline void fill(float32_t value)
		{
			arm_fill_f32(value, &this->Vector_data()[0], this->size());
		};

		DSP_vector_f32& Scale(float32_t value)
		{
			return this->Scale(value, *this);
		}

		DSP_vector_f32& Scale(float32_t value, DSP_vector_base<float32_t>& vec)
		{
			arm_scale_f32(&vec[0], value, &this->Vector_data()[0], this->size());
			return *this;
		}

		DSP_vector_f32& Offset(float32_t value)
		{
			return this->Offset(value, *this);
		}

		DSP_vector_f32& Offset(float32_t value, DSP_vector_base<float32_t>& vec)
		{
			arm_offset_f32(&vec[0], value, &this->Vector_data()[0], this->size());
			return *this;
		}

		/*Element-by-element addition
		 pDst[n] = pSrcA[n] + pSrcB[n],   0 <= n < blockSize.*/
		DSP_vector_f32& Add(DSP_vector_base<float32_t>& vec)
		{
			arm_add_f32(&this->Vector_data()[0], &vec[0], &this->Vector_data()[0], this->size());
			return *this;
		}
		/*
		@breif рассчитывает сумму квадратов вектора.
		Result = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + pSrc[2] * pSrc[2] + ... + pSrc[blockSize-1] * pSrc[blockSize-1];    */
		float32_t Power()
		{
			float32_t result;
			arm_power_f32(&this->Vector_data()[0], this->size(), &result);
			return result;
//			register float32_t summ = 0.0;
//			register float32_t* current = &Vector_data()[0];
//			register float32_t* end = current + this->size();
//			while (current < end)
//			{
//				summ += *current * *current++;
//			}
//			return summ;
		}

		/*@breif расчитывает СКЗ
		Result = sqrt(((vector[0] * vector[0] + vector[1] * vector[1] + ... + vector[blockSize-1] * vector[vectorSize-1]) / vectorSize));*/
		float32_t RMS()
		{
		    float32_t result;
		    arm_rms_f32(&this->Vector_data()[0],this->size(),&result);
		    return result;
//			register float32_t* current = &Vector_data()[0];
//			register float32_t* end = current + this->size();
//			register float32_t summ = 0;
//			while (current < end)
//			{
//				summ += pow(*current++, 2);
//			}
//			float32_t result = sqrt(summ / this->size());
//			return result;
		}

		DSP_vector_f32& operator=(DSP_vector_f32& vec)
		{
			arm_copy_f32(&vec.Vector_data()[0], &Vector_data()[0], Vector_data().size());
			return *this;
		}

		/*@breif рассчитывает среднее значение
		Result = (vector[0] + vector[1] + vector[2] + ... + vector[vectorSize-1]) / vectorSize; */
		float32_t Mean()
		{
			float32_t result;
			arm_mean_f32(&this->Vector_data()[0],this->size(),&result);
			return result;
		}

		float32_t& Maximum(size_t& index)
		{
			float32_t result;
			arm_max_f32(&this->Vector_data()[0], this->size(), &result, &index);
			return result;
		}

		float32_t& Minimum(size_t& index)
		{
			float32_t result;
			arm_min_f32(&this->Vector_data()[0], this->size(), &result, &index);
			return result;
		}


		virtual ~DSP_vector_f32(){};
	};
}