#include <cstdio>
#include <unistd.h>

#include "ClockModel.hpp"
#include "ClockController.hpp"

ClockController::ClockController()
{
	std::cout << "Instantiation ClockController from CPP" << std::endl;
}

ClockController::~ClockController()
{
	// do nothing
}

int ClockController::run(void)
{
	while(1) {
		sleep(1);
		static_cast<ClockModel *>(model)->incSecond();
	}

	std::printf("\n");
	return 0;
}
