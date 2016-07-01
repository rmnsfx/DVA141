#pragma once
#include <stddef.h>
#include <math.h>
//#include "iDSP_vector.h"
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
typedef float float32_t;

namespace DSP
{
	template<class T>
	class DSP_vector_base  //: public iDSP_vector<T>
	{
		private:
		DSP_vector_base()
		{
		};
		protected:
		size_t vector_size;
		T* vector_data; // стандартный ветктор с данными
		T temp_value; //переменная для рахранения временных данных и прочего можно писать что угодоно, когда угодно

		/*@param size - размер вектора который необходимо создать*/
		DSP_vector_base(size_t size)
		{
			vector_data = new T[size];
			if (vector_data == NULL)
			{
				vector_size = 0;
				return;
			}
			vector_size = size;
		};

		/*@param size - размер вектора
		@param value - значение которым необходимо заполнить*/
		DSP_vector_base(size_t size, T value)
		{
			vector_data = new T[size];
			if (vector_data == NULL)
			{
				vector_size = 0;
				return;
			}
			vector_size = size;
			for(int i=0; i < size; i++)
			{
				vector_data[i] = value;
			}
		};

		public:
		/*@return - стандартный вектор vector<T>*/
		inline T* Vector_data()
		{
			return vector_data;
		}

		/*@return возвращает размер вектора*/
		inline size_t size()
		{
			return vector_size;
		}

		T& operator [](size_t i)
		{
			if (i >= this->size())
			{
				return this->temp_value;
			}
			return vector_data[i];
		};

		virtual ~DSP_vector_base()
		{

		};
	};



	//	template<class T>
	//	class DSP_vector_base : public iDSP_vector<T>
	//	{
	//	private:
	//		DSP_vector_base() :begin(NULL), end(NULL)
	//		{
	//		};
	//	    protected:
	//		T* begin;
	//		T* end;
	//		T temp_value; //переменная для рахранения временных данных и прочего
	//
	//
	//		/*@param size - размер вектора который необходимо создать*/
	//		DSP_vector_base(size_t size)
	//		{
	//			end = NULL;
	//			begin = new T[size];
	//			if (begin == NULL)
	//			{
	//				return;
	//			}
	//			end = begin + size;
	//		};
	//
	//		/*@param size - размер вектора
	//		@param value - значение которым необходимо заполнить*/
	//		DSP_vector_base(size_t size, T value)
	//		{
	//			end = NULL;
	//			begin = new T[size];
	//			if (begin == NULL)
	//			{
	//				return;
	//			}
	//			end = begin + size;
	//			this->fill(value);
	//		};
	//
	//	public:
	//		/*@return возвращает размер вектора*/
	//		size_t size()
	//		{
	//			return end - begin;
	//		}
	//
	//		/*@breif заполняет вектор постоянными значениями
	//		@param value - значение которым будет заполнен вектор*/
	//		void fill(T value)
	//		{
	//			T* current = begin;
	//			while (current < end)
	//			{
	//				*current++ = value;
	//			}
	//		}
	//
	//		/*@breif метод для смещения значения
	//		@param value - значение которое необходимо добавить к каждому элементу вектора
	//		рассчитывается по формуле:
	//		vector[n] = vector[n] + value,  0 < n < vectorSize*/
	//		void inline offset(T value)
	//		{
	//			this->offset(value, *this);
	//		}
	//
	//		/*@breif метод для смещения значения, учитывается размер каждого вектора.
	//		@param value - значение которое необходимо добавить к каждому элементу вектора
	//		@param vec - вектор с исходными значениями
	//		рассчитывается по формуле:
	//		vector[n] = vec[n] + value,  0 < n < vectorSize*/
	//		void offset(T value, iDSP_vector<T>& vec)
	//		{
	//			T* current = this->begin;
	//			T* ending = current;
	//			T* source = &vec[0];
	//			ending = this->size() <= vec.size() ? this->end : this->begin + vec.size();
	//			while (current < ending)
	//			{
	//				*current++ = *source++ + value;
	//			}
	//		}
	//
	//		/*метод для умножения значения вектора на скаляр
	//		vector[n] = vector[n]*value; */
	//		DSP_vector_base& Scale(T value)
	//		{
	//			return this->Scale(value, *this);
	//		}
	//
	//		DSP_vector_base& Scale(T value, iDSP_vector<T>& vec)
	//		{
	//			register T* current = begin;
	//			register T* ending = current;
	//			register T* source = &vec[0];
	//			ending = this->size() <= vec.size() ? this->end : this->begin + vec.size();
	//			while (current < ending)
	//			{
	//				*current++ = *source++ * value;
	//			}
	//			return *this;
	//		}
	//
	//		/*@breif расчитывает СКЗ
	//		Result = sqrt(((vector[0] * vector[0] + vector[1] * vector[1] + ... + vector[blockSize-1] * vector[vectorSize-1]) / vectorSize));*/
	//		T RMS()
	//		{
	//			register T* current = begin;
	//			register T summ = 0;
	//			while (current < end)
	//			{
	//				summ += pow(*current++, 2);
	//			}
	//			T result = sqrt(summ / this->size());
	//			return result;
	//		}
	//
	//		T& Maximum(size_t& index)
	//		{
	//			register T* current = begin;
	//			register T* max = current;
	//			index = 0;
	//			while (current < end)
	//			{
	//				if (*max < *current)
	//				{
	//					index = (current - begin);
	//					max = current;
	//				}
	//				current++;
	//			}
	//			return *max;
	//		}
	//
	//		T& Minimum(size_t& index)
	//		{
	//			register T* current = begin;
	//			register T* max = current;
	//			index = 0;
	//			while (current < end)
	//			{
	//				if (*max > *current)
	//				{
	//					index = (current - begin);
	//					max = current;
	//				}
	//				current++;
	//			}
	//			return *max;
	//		}
	//
	//
	//
	//		/*@breif рассчитывает среднее значение
	//		Result = (vector[0] + vector[1] + vector[2] + ... + vector[vectorSize-1]) / vectorSize; */
	//		T Mean()
	//		{
	//			register T summ = 0.0;
	//			T* current = begin;
	//			while (current < end)
	//			{
	//				summ += *current++;
	//			}
	//			return summ / this->size();
	//		}
	//
	//		/*
	//		@breif рассчитывает сумму квадратов вектора.
	//		Result = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + pSrc[2] * pSrc[2] + ... + pSrc[blockSize-1] * pSrc[blockSize-1];    */
	//		T Power()
	//		{
	//			register T summ = 0.0;
	//			T* current = begin;
	//			while (current < end)
	//			{
	//				summ += *current * *current++;
	//			}
	//			return summ;
	//		}
	//
	//		T& operator [](size_t i)
	//		{
	//			if (i >= this->size())
	//			{
	//				return this->temp_value;
	//			}
	//			return *(this->begin + i);
	//		};
	//
	//		virtual ~DSP_vector_base()
	//		{
	//			if (begin != NULL)
	//			{
	//				delete[] begin;
	//			}
	//		};
	//	};
}
