#ifndef __CLOCK_CONTROLLER_HPP__
#define __CLOCK_CONTROLLER_HPP__

#include "mvc/mvc.hpp"

class ClockController : public AbstractController
{
	public:
		ClockController();
		virtual ~ClockController();
		int run(void);
};

#endif  // __CLOCK_CONTROLLER_HPP__
