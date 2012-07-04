#include "ClockModel.hpp"

ClockModel::ClockModel()
{
	hour = 0;
	minute = 0;
	second = 0;

	std::cout << "Instantiation ClockModel from CPP" << std::endl;
}

ClockModel::~ClockModel()
{
	// do nothing
}

void ClockModel::setHour(int h)
{
	hour = h;
	notify();
}

void ClockModel::setMinute(int m)
{
	minute = m;
	notify();
}

void ClockModel::setSecond(int s)
{
	second = s;
	notify();
}

int ClockModel::getHour(void)
{
	return hour;
}

int ClockModel::getMinute(void)
{
	return minute;
}

int ClockModel::getSecond(void)
{
	return second;
}

void ClockModel::incHour(void)
{
	hour += 1;
	if(hour >= 24) {
		hour = 0;
	}

	notify();
}

void ClockModel::incMinute(void)
{
	minute += 1;
	if(minute >= 60) {
		minute = 0;
		incHour();
	}

	notify();
}

void ClockModel::incSecond(void)
{
	second += 1;
	if(second >= 60) {
		second = 0;
		incMinute();
	}

	notify();
}

void ClockModel::notify(void)
{
	setChanged();

	notifyObservers();
}

