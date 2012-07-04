#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

class Observable;

class Observer 
{
	public: 
		virtual void update(Observable *) = 0;
}; 

#endif  // __OBSERVER_HPP__

