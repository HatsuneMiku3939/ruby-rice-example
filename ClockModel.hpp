#ifndef __CLOCK_MODEL_HPP__
#define __CLOCK_MODEL_HPP__

#include "mvc/mvc.hpp"

class ClockModel : public Observable
{
	public:
		ClockModel();
		virtual ~ClockModel();

		void setHour(int h);
		void setMinute(int m);
		void setSecond(int s);

		int getHour();
		int getMinute();
		int getSecond();

		void incHour(void);
		void incMinute(void);
		void incSecond(void);

	private:
		void notify(void);

		int hour;
		int minute;
		int second;
};


#endif  // __CLOCK_MODEL_HPP__
