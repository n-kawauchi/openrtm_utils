// -*- C++ -*-
/*!
 * @file  RTMath.h
 * @brief 
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef RTMATH_H
#define RTMATH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <coil/stringutil.h>
#include <coil/TimeMeasure.h>
#include <cmath>
#include <random>


template <class T>
class ValueAndTime
{
public:
	ValueAndTime(coil::TimeValue tm, T value)
	{
		m_tm = tm;
		m_value = value;
	};
	coil::TimeValue m_tm;
	T m_value;
};

template <class T>
class RTMath
{
public:
	RTMath()
	{
		setSamplingTime(0.01);
		realTime = false;
		resetTime();
	};
	virtual void setSamplingTime(double s)
	{
		if(samplingTime_low < s)
		{
			samplingTime = s;
			
		}
		else
		{
			samplingTime = samplingTime_low;
		}
		
	};
	virtual void setConfig(bool c)
	{
		realTime = c;
	};
	virtual bool getDiffTime(double &ans)
	{
		if(realTime)
		{
			if(dataList.size() < 2)
			{
				return false;
			}
			else
			{
				ans = (double)(dataList[dataList.size()-1].m_tm - dataList[dataList.size()-2].m_tm);
			}
		}
		else
		{
			ans = samplingTime;
		}
		return true;
	}
	virtual void resetTime()
	{
		dataList.clear();
		first_time = coil::TimeValue(coil::gettimeofday());
		now_time = 0;
	};
	virtual void addData(T data)
	{
		coil::TimeValue t0(coil::gettimeofday());
		dataList.push_back(ValueAndTime<T>(t0,data));
	};
	virtual double getTime()
	{
		if(realTime)
		{
			coil::TimeValue t0(coil::gettimeofday());
			now_time = (double)(t0-first_time);
		}
		else
		{
			now_time += samplingTime;
		}
		return now_time;
	};
	const double samplingTime_low = 0.000001;
	coil::TimeValue first_time;
	double now_time;
	bool realTime;
	double samplingTime;
	std::vector<ValueAndTime<T>> dataList;
};



template <class T>
class RTIntegrator : public RTMath<T>
{
public:
	RTIntegrator()
	{
		initialCondition = 0;
		reset();
	};
	void reset()
	{
		resetTime();
		intValue = initialCondition;
	};
	void setInitialCondition(T c)
	{
		initialCondition = c;
		intValue = initialCondition;
	};
	bool calc(T &ans)
	{
		if(dataList.size() < 2)
		{
			return false;
		}
		double stepTime;
		if(!getDiffTime(stepTime))
		{
			return false;
		};
		
		T tmp = (dataList[dataList.size()-1].m_value + dataList[dataList.size()-2].m_value)*stepTime/2;
		intValue += tmp;
		ans = intValue;
		return true;
	};
	T intValue;
	T initialCondition;
};




template <class T>
class RTDerivative : public RTMath<T>
{
public:
	RTDerivative()
	{
		reset();
	};
	void reset()
	{
		resetTime();
	};
	bool calc(T &ans)
	{
		if(dataList.size() < 2)
		{
			return false;
		}
		double stepTime;
		if(!getDiffTime(stepTime))
		{
			return false;
		};
		
		//T tmp = (dataList[dataList.size()-1].m_value + dataList[dataList.size()-2].m_value)*stepTime/2;
		ans = (dataList[dataList.size()-1].m_value - dataList[dataList.size()-2].m_value)/stepTime;
		return true;
	};
};

template <class T>
class RTBacklash
{
public:
	RTBacklash()
	{
		reset();
	};
	void reset()
	{
		now_Output = m_initialOutput;
	};
	void setDeadbandWidth(T width)
	{
		m_width = width;
	};
	void setInitialOutput(T io)
	{
		m_initialOutput = io;
		//now_Output = io;
	};
	T calc(T input)
	{
		double low_output = now_Output-m_width/(T)2.0;
		double high_output = now_Output+m_width/(T)2.0;
		//std::cout << high_output << "\t" << low_output << "\t" << m_width << std::endl;
		if(input < high_output && input > low_output)
		{

		}
		else if(input > high_output)
		{
			now_Output = input - m_width/(T)2.0;
			
		}
		else if(input < low_output)
		{
			now_Output = input + m_width/(T)2.0;
			
		}
		return now_Output;
	};
	T now_Output;
	T m_width;
	T m_initialOutput;
};

template <class T>
T RTSaturation(T input, T upperLimit, T lowerLimit)
{
	T val = input;
	if(val > upperLimit)
	{
		val = upperLimit;
	}
	else if(val < lowerLimit)
	{
		val = lowerLimit;
	}
	return val;
};

template <class T>
bool getValueInString(std::string str, std::vector<T> &ans)
{
	coil::eraseBlank(str);
	ans.clear();
	coil::vstring va = coil::split(str, ",");
	if(va.size() == 0)
	{
		return false;
	}
	for (coil::vstring::iterator it = va.begin(); it != va.end(); ++it)
	{
		T value;
		bool result = coil::stringTo<T>(value, (*it).c_str());
		if(result)
		{
			ans.push_back(value);
		}
		else
		{
			return false;
		}
	}
	
	return true;
};

template <class T>
bool getValueInList(std::vector<T> input, int num, T &ans)
{
	if(input.size() == 0)
	{
		return false;
	}

	if((int)input.size()-1 < num)
	{
		ans = input[0];
	}
	else
	{
		ans = input[num];
	}
	return true;
};


template <class T>
T RTCoulombAndViscousFriction(T input, T offset, T gain)
{
	if(input < 0)
	{
		return gain*input - offset;
	}
	else if(input > 0)
	{
		return gain*input + offset;
	}
	else
	{
		return 0;
	}
};

template <class T>
T RTDeadZone(T input, T start, T end)
{
	if(input < start)
	{
		return input - start;
	}
	else if(input > end)
	{
		return input - end;
	}
	else
	{
		return 0;
	}
};


template <class T>
class RTRateLimiter : public RTMath<T>
{
public:
	RTRateLimiter()
	{
		reset();
	};
	void setSlewRate(T rsr, T fsr)
	{
		risingSlewRate = rsr;
		fallingSlewRate = fsr;
	};
	void reset()
	{
		resetTime();
	};
	bool calc(T &ans)
	{
		if(dataList.size() == 1)
		{
			last_value = dataList[0].m_value;
		}
		if(dataList.size() < 2)
		{

			return false;
		}
		double stepTime;
		if(!getDiffTime(stepTime))
		{
			return false;
		};
		
		
		T rate = (dataList[dataList.size()-1].m_value - last_value)/stepTime;
		if(rate > risingSlewRate)
		{
			last_value += risingSlewRate * stepTime;
		}
		else if(rate < fallingSlewRate)
		{
			last_value += fallingSlewRate * stepTime;
		}
		else
		{
			last_value = dataList[dataList.size()-1].m_value;
		}
		ans = last_value;
		return true;
	};
	T last_value;
	T risingSlewRate;
	T fallingSlewRate;
};


template <class T>
class RTRelay
{
public:
	RTRelay()
	{
		reset();
	};
	void reset()
	{
		state = false;
	};
	void setSwitchPoint(T on, T off)
	{
		switchOnPoint = on;
		switchOffPoint = off;
	};
	void setOutput(T on, T off)
	{
		outputWhenOn = on;
		outputWhenOff = off;
	};
	T calc(T input)
	{
		T ans;
		if(state)
		{
			if(switchOffPoint > input)
			{
				state = false;
				ans = outputWhenOff;
			}
			else
			{
				ans = outputWhenOn;
			}
		}
		else
		{
			if(switchOnPoint < input)
			{
				state = true;
				ans = outputWhenOn;
			}
			else
			{
				ans = outputWhenOff;
			}
		}
		return ans;
	};
	T switchOnPoint;
	T switchOffPoint;
	T outputWhenOn;
	T outputWhenOff;
	bool state;
};


/*int RTAbs(int input);
double RTAbs(double input);
float RTAbs(float input);

double RTSin(double input);
float RTSin(float input);
double RTCos(double input);
float RTCos(float input);
double RTTan(double input);
float RTTan(float input);
double RTASin(double input);
float RTASin(float input);
double RTACos(double input);
float RTACos(float input);
double RTATan(double input);
float RTATan(float input);
double RTSinh(double input);
float RTSinh(float input);
double RTCosh(double input);
float RTCosh(float input);
double RTTanh(double input);
float RTTanh(float input);
double RTASinh(double input);
float RTASinh(float input);
double RTACosh(double input);
float RTACosh(float input);
double RTATanh(double input);
float RTATanh(float input);
double RTSqrt(double input);
float RTSqrt(float input);
double RTPow(double x, double y);
float RTPow(float x, float y);
*/


template <class T>
T RTSign(T input)
{
	if(input > 0)
	{
		return 1;
	}
	else if(input < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}



template <class T>
T RTSignedSqrt(T input)
{
	return RTSign<T>(input)*std::sqrt(std::abs(input));
}




template <class T>
class RTSineWave : public RTMath<T>
{
public:
	RTSineWave()
	{
		reset();
	};
	void reset()
	{
		resetTime();
	};
	
	T calc()
	{
		double nt = getTime();
		return amplitude*std::sin(2*M_PI*frequency*nt + phase) + bias;
	};
	void setAmplitude(T input)
	{
		amplitude = input;
	};
	void setBias(T input)
	{
		bias = input;
	};
	void setFrequency(T input)
	{
		frequency = input;
	};
	void setPhase(T input)
	{
		phase = input;
	};
	
	
	T amplitude;
	T bias;
	T frequency;
	T phase;
};


template <class T>
class RTRampFunction : public RTMath<T>
{
public:
	RTRampFunction()
	{
		reset();
	};
	void reset()
	{
		resetTime();
	};
	
	T calc()
	{
		double nt = getTime();
		if(startTime < nt)
		{
			return slope*(nt - startTime) + initialOutput;
		}
		else
		{
			return initialOutput;
		}
	};
	void setSlope(T input)
	{
		slope = input;
	};
	void setStartTime(T input)
	{
		startTime = input;
	};
	void setInitialOutput(T input)
	{
		initialOutput = input;
	};
	
	
	T slope;
	T startTime;
	T initialOutput;
};


template <class T>
class RTPulseGenerator : public RTMath<T>
{
public:
	RTPulseGenerator()
	{
		reset();
	};
	void reset()
	{
		resetTime();
	};
	
	T calc()
	{
		double nt = getTime();
		T st = nt - phaseDelay;
		if(st < 0)
		{
			return 0;
		}
		else
		{
			T fmodValue = std::fmod(st, period);
			//std::cout << fmodValue << "\t" << period*(1-pulseWidth/100.0) << std::endl;
			if(fmodValue < period*(1-pulseWidth/100.0))
			{
				return 0;
			}
			else
			{
				return amplitude;
			}
		}
	};
	void setAmplitude(T input)
	{
		amplitude = input;
	};
	void setPeriod(T input)
	{
		period = input;
	};
	void setPulseWidth(T input)
	{
		pulseWidth = input;
	};
	void setPhaseDelay(T input)
	{
		phaseDelay = input;
	};
	
	
	T amplitude;
	T period;
	T pulseWidth;
	T phaseDelay;
};


template <class T, class T2>
class RTUniformRandomNumber
{
public:
	RTUniformRandomNumber() : m_rand(-1,1), m_mt(0)
	{
		m_maximum = 1;
		m_minimum = -1;
		m_seed = 0;
		m_randomSeedGenerator = true;
		//m_rand = T2(m_maximum,m_minimum);
		//setMt();
	};
	void reset()
	{
		setMt();
		m_rand = T2(m_maximum,m_minimum);
	};
	void setMt()
	{
		unsigned int t_seed;
		if(m_randomSeedGenerator)
		{
			std::random_device rnd;
			t_seed = rnd();
		}
		else if(m_randomSeedGenerator)
		{
			t_seed = m_seed;
		}
		m_mt = std::mt19937(t_seed);
	};
	
	
	T calc()
	{
		return m_rand(m_mt);
	};
	void setMaximum(T input)
	{
		m_maximum = input;
		m_rand = T2(m_maximum,m_minimum);
	};
	void setMinimum(T input)
	{
		m_minimum = input;
		m_rand = T2(m_maximum,m_minimum);
	};
	void setSeed(unsigned int input)
	{
		m_seed = input;
		setMt();
	};
	void setRandomSeedGenerator(bool input)
	{
		m_randomSeedGenerator = input;
		setMt();
	};
	
	
	T m_maximum;
	T m_minimum;
	unsigned int m_seed;
	bool m_randomSeedGenerator;
	T2 m_rand;
	std::mt19937 m_mt;
};




template <class T>
class RTRandomNumber
{
public:
	RTRandomNumber() : m_rand(-1,1), m_mt(0)
	{
		m_mean = 0;
		m_variable = 1;
		m_seed = 0;
		m_randomSeedGenerator = true;

	};
	void reset()
	{
		setMt();
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	void setMt()
	{
		unsigned int t_seed;
		if(m_randomSeedGenerator)
		{
			std::random_device rnd;
			t_seed = rnd();
		}
		else if(m_randomSeedGenerator)
		{
			t_seed = m_seed;
		}
		m_mt = std::mt19937(t_seed);
	};
	
	
	T calc()
	{
		return m_rand(m_mt);
	};
	void setMean(T input)
	{
		m_mean = input;
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	void setVariable(T input)
	{
		m_variable = input;
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	void setSeed(unsigned int input)
	{
		m_seed = input;
		setMt();
	};
	void setRandomSeedGenerator(bool input)
	{
		m_randomSeedGenerator = input;
		setMt();
	};
	
	
	T m_mean;
	T m_variable;
	unsigned int m_seed;
	bool m_randomSeedGenerator;
	std::normal_distribution<T> m_rand;
	std::mt19937 m_mt;
};


template <class T>
class RTStepFunction : public RTMath<T>
{
public:
	RTStepFunction()
	{
		reset();
	};
	void reset()
	{
		resetTime();
	};
	
	T calc()
	{
		double nt = getTime();
		//std::cout << nt << std::endl;
		if(nt < stepTime)
		{
			return initialValue;
		}
		else
		{
			return finalValue;
		}
	};
	void setInitialValue(T input)
	{
		initialValue = input;
	};
	void setFinalValue(T input)
	{
		finalValue = input;
	};
	void setStepTime(T input)
	{
		stepTime = input;
	};
	
	
	
	T initialValue;
	T finalValue;
	T stepTime;
};


template <class T>
class RTController
{
public:
	RTController()
	{
		m_proportional = 1;
		m_integral = 0;
		m_derivative = 0;
		m_alpha = 1;
		m_beta = 0;
	};
	virtual void reset()
	{

	};
	virtual void setProportionalValue(T value)
	{
		m_proportional = value;
	};
	virtual void setIntegralValue(T value)
	{
		m_integral = value;
	};
	virtual void setDerivativeValue(T value)
	{
		m_derivative = value;
	};
	virtual void setAlpha(T value)
	{
		m_alpha = value;
	};
	virtual void setBeta(T value)
	{
		m_beta = value;
	};
	virtual bool calc(T input, T value, T &ans)
	{
		return true;
	};
	virtual void setSamplingTime(double s)
	{
		
	};
	virtual void setConfig(bool c)
	{

	};
	T m_proportional;
	T m_integral;
	T m_derivative;
	T m_alpha;
	T m_beta;
};



template <class T>
class RTPController : public RTController<T>
{
public:
	RTPController()
	{
		reset();
	};
	bool calc(T input, T value, T &ans)
	{
		ans = m_proportional*(m_alpha*input - value);
		return true;
	};
};


template <class T>
class RTPDController : public RTController<T>
{
public:
	RTPDController()
	{
		reset();
	};
	void reset()
	{
		d_func.reset();
	};
	bool calc(T input, T value, T &ans)
	{
		d_func.addData(m_beta*input - value);
		T d_value;
		if(!d_func.calc(d_value))return false;

		ans = m_proportional*(m_alpha*input - value) + m_derivative*d_value;
		return true;
	};
	void setSamplingTime(double s)
	{
		d_func.setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		d_func.setConfig(c);
	};
	RTDerivative<T> d_func;
};


template <class T>
class RTPIController : public RTController<T>
{
public:
	RTPIController()
	{
		reset();
	};
	void reset()
	{
		i_func.reset();
	};
	bool calc(T input, T value, T &ans)
	{
		i_func.addData(input-value);
		T i_value;
		if(!i_func.calc(i_value))return false;

		ans = m_integral*i_value + m_proportional*(m_alpha*input - value);
		return true;
	};
	void setSamplingTime(double s)
	{
		i_func.setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		i_func.setConfig(c);
	};
	RTIntegrator<T> i_func;
};


template <class T>
class RTIController : public RTController<T>
{
public:
	RTIController()
	{
		reset();
	};
	void reset()
	{
		i_func.reset();
	};
	bool calc(T input, T value, T &ans)
	{
		i_func.addData(input-value);
		T i_value;
		if(!i_func.calc(i_value))return false;

		ans = m_integral*i_value;
		return true;
	};
	void setSamplingTime(double s)
	{
		i_func.setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		i_func.setConfig(c);
	};
	RTIntegrator<T> i_func;
};


template <class T>
class RTPIDController : public RTController<T>
{
public:
	RTPIDController()
	{
		reset();
	};
	void reset()
	{
		d_func.reset();
		i_func.reset();
	};
	bool calc(T input, T value, T &ans)
	{
		d_func.addData(m_beta*input - value);
		T d_value;
		if(!d_func.calc(d_value))return false;

		i_func.addData(input-value);
		T i_value;
		if(!i_func.calc(i_value))return false;

		ans = m_integral*i_value + m_proportional*(m_alpha*input - value) + m_derivative*d_value;
		return true;
	};
	void setSamplingTime(double s)
	{
		d_func.setSamplingTime(s);
		i_func.setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		d_func.setConfig(c);
		i_func.setConfig(c);
	};
	RTDerivative<T> d_func;
	RTIntegrator<T> i_func;
};






#endif 
