#pragma once
#include "DSP_vector_base.h"
#include "arm_math.h"

typedef float float32_t;

namespace DSP
{
	class DSP_vector_q31 : public DSP_vector_base<q31_t>
	{
		const q31_t scaleFract = 0x7FFFFFFF; //дробная часть значения шкалы (fractional portion of the scale value)
		/*стандартные функции деления вектора заменяем на специфичные для типа q31_t*/
		public:
		explicit DSP_vector_q31(size_t size) : DSP_vector_base<q31_t>(size){};
		explicit DSP_vector_q31(size_t size, q31_t value) : DSP_vector_base<q31_t>(size)
		{
			for(int i = 0; i < size; i++)
			{
				 vector_data[i] = value;
			}
		};
		inline void fill(float32_t value)
		{
			arm_fill_q31(value, &this->Vector_data()[0], this->size());
		};

		/*@param shift - количество бит на которое необходимо сдвинуть результат.
		вектор умножается на число: 2^shift. */
		DSP_vector_base& Scale(int8_t shift)
		{
			return this->Scale(shift, *this);
		}

		/*@param shift - количество бит на которое необходимо сдвинуть результат.
		@param vec - исходный вектор которой необходимо умножить на коэффициент и результат присвоится текущему вектору.
		вектор умножается на число: 2^shift. */
		DSP_vector_base& Scale(int8_t shift, DSP_vector_base<q31_t>& vec)
		{
			arm_scale_q31(&vec[0], scaleFract, shift, &this->Vector_data()[0], vec.size());
		}

		q63_t Power()
		{
			q63_t result;
			arm_power_q31(&this->Vector_data()[0], this->size(), &result);
			return result;
		}

		/*@breif рассчитывает среднее значение
		Result = (vector[0] + vector[1] + vector[2] + ... + vector[vectorSize-1]) / vectorSize; */
		q31_t Mean()
		{
			q31_t result;
			arm_mean_q31(&this->Vector_data()[0], this->size(), &result);
			return result;
		}

		/*@breif расчитывает СКЗ
		Result = sqrt(((vector[0] * vector[0] + vector[1] * vector[1] + ... + vector[blockSize-1] * vector[vectorSize-1]) / vectorSize));*/
		q31_t RMS()
		{
			q31_t result;
			arm_rms_q31(&Vector_data()[0], this->size(), &result);
			return result;
		}

		q31_t& Maximum(size_t& index)
		{
			q31_t result;
			arm_max_q31(&this->Vector_data()[0], this->size(), &result, (uint32_t*)&index);
			return result;
		}

		q31_t& Minimum(size_t& index)
		{
			q31_t result;
			arm_min_q31(&this->Vector_data()[0], this->size(), &result, (uint32_t*)&index);
			return result;
		}

		DSP_vector_q31& operator=(DSP_vector_q31& vec)
		{
			arm_copy_q31(&vec.Vector_data()[0], &Vector_data()[0], this->size());
			return *this;
		}




		virtual ~DSP_vector_q31(){};
	};


}
using namespace DSP;
