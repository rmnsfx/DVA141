#pragma once
#include "DSP_vector_f32.h"
#include "DSP_vector_q31.h"

namespace DSP
{
	class DSP_converter
	{
	public:
		/*@breif - ����� ��� �������������� ����� float � q31_t
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void f32_to_q31(q31_t& dst, float32_t& src)
		{
			arm_float_to_q31(&src, &dst, 1);
		};

		/*@breif - ����� ��� �������������� ������� float � ������ q31_t
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void f32_to_q31(DSP_vector_q31& dst, DSP_vector_f32& src)
		{
			arm_float_to_q31(&src.Vector_data()[0], &dst.Vector_data()[0], src.size());
		};

		/*@breif - ����� ��� �������������� ����� float64_t � q31_t
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void f64_to_q31(q31_t& dst, float64_t& src)
		{
			arm_float64_to_q31(&src, &dst, 1);
		};

		/*@breif - ����� ��� �������������� ����� q63_t � float32_t
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void q63_to_float(float32_t& dst, q63_t& src)
		{
			arm_q63_to_float(&src, &dst, 1);
		}

		/*@breif - ����� ��� �������������� ����� q48_t � float32_t
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void q48_to_float(float32_t& dst, q48_t& src)
		{
			arm_q48_to_float(&src, &dst, 1);
		}

		/*@breif - ����� ��� �������������� ����� q31_t � float
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void q31_to_f32(float32_t& dst, q31_t& src)
		{
			arm_q31_to_float(&src, &dst, 1);
		};


		/*@breif - ����� ��� �������������� ����� q31_t � float
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void q31_to_f64(float64_t& dst, q31_t& src)
		{
			arm_q31_to_float64(&src, &dst, 1);
		};

		/*@breif - ����� ��� �������������� ������� q31_t � ������ float
		@param dst - ���� ����� ������� ���������
		@param src - ��� ����� ��������������*/
		static void q31_to_f32(DSP_vector_f32& dst, DSP_vector_q31& src)
		{
			arm_q31_to_float(&src.Vector_data()[0], &dst.Vector_data()[0], src.size());
		};
	};
}