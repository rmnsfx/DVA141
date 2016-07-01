#pragma once
#include "DSP_vector_f32.h"
#include "DSP_vector_q31.h"

namespace DSP
{
	class DSP_converter
	{
	public:
		/*@breif - метод для преобразования числа float в q31_t
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void f32_to_q31(q31_t& dst, float32_t& src)
		{
			arm_float_to_q31(&src, &dst, 1);
		};

		/*@breif - метод для преобразования вектора float в вектор q31_t
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void f32_to_q31(DSP_vector_q31& dst, DSP_vector_f32& src)
		{
			arm_float_to_q31(&src.Vector_data()[0], &dst.Vector_data()[0], src.size());
		};

		/*@breif - метод для преобразования числа float64_t в q31_t
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void f64_to_q31(q31_t& dst, float64_t& src)
		{
			arm_float64_to_q31(&src, &dst, 1);
		};

		/*@breif - метод для преобразования числа q63_t в float32_t
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void q63_to_float(float32_t& dst, q63_t& src)
		{
			arm_q63_to_float(&src, &dst, 1);
		}

		/*@breif - метод для преобразования числа q48_t в float32_t
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void q48_to_float(float32_t& dst, q48_t& src)
		{
			arm_q48_to_float(&src, &dst, 1);
		}

		/*@breif - метод для преобразования числа q31_t в float
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void q31_to_f32(float32_t& dst, q31_t& src)
		{
			arm_q31_to_float(&src, &dst, 1);
		};


		/*@breif - метод для преобразования числа q31_t в float
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void q31_to_f64(float64_t& dst, q31_t& src)
		{
			arm_q31_to_float64(&src, &dst, 1);
		};

		/*@breif - метод для преобразования вектора q31_t в вектор float
		@param dst - куда будет записан результат
		@param src - что будет преобразованно*/
		static void q31_to_f32(DSP_vector_f32& dst, DSP_vector_q31& src)
		{
			arm_q31_to_float(&src.Vector_data()[0], &dst.Vector_data()[0], src.size());
		};
	};
}