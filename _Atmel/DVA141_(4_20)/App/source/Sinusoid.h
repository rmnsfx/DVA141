/*
 * Sinusoid.h
 *
 * Created: 14.06.2016 13:52:04
 *  Author: savchenkors
 */ 


#ifndef SINUSOID_H_
#define SINUSOID_H_



class Sinusoid
{
	
	public:
	
	Sinusoid(void);
	virtual ~Sinusoid(void);
	
	static void Sinus(void *pvParameters);

	static void Sinus_double (void *pvParameters);	
	
	static void Sinus_make32points(void *pvParameters);
	
	static void Sinus_filter32points(void *pvParameters);
	
};


#endif /* SINUSOID_H_ */