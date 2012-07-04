#ifndef __OBSERABLE_HPP__
#define __OBSERABLE_HPP__

#include <vector> 
#include <iostream>

class Observable 
{ 
	public:
		Observable()
		{
			changed = false;
		}

		virtual ~Observable()
		{
			// do nothing
		}

		bool addObserver(Observer *a)
		{
			// check observer is valid
			if(a == NULL)
				return false;

			// don't add and observer more than once.
			for(std::vector<Observer*>::const_iterator observer_iterator=observers.begin(); 
					observer_iterator != observers.end(); 
					observer_iterator++ ) {
				if((*observer_iterator) == a) 
					return false;
			}

			// put observer into the list
			observers.push_back(a);

			return true;
		}

		void removeObserver(Observer *a)
		{
			// check observer is valid
			if(a == NULL)
				return;

			for(std::vector<Observer *>::iterator observer_iterator = observers.begin(); 
					observer_iterator != observers.end(); 
					observer_iterator++ ) {
				if(*observer_iterator == a) {
					observer_iterator = observers.erase(observer_iterator);
					return;
				}
			}
		}

		// notifyObservers 
		void notifyObservers()
		{ 
			// do nothing when observable is not changed
			if(!isChanged())
				return;
			
			for(std::vector<Observer *>::const_iterator observer_iterator = observers.begin(); 
					observer_iterator != observers.end(); 
					observer_iterator++ ) {
				(*observer_iterator)->update(this);
			}

			clearChanged();
		} 

		bool isChanged(void)
		{
			return changed;
		}

		size_t countObserver(void)
		{
			return observers.size();
		}

		void setChanged(void)
		{
			changed = true;
		}

		void clearChanged(void)
		{
			changed = false;
		}

	private:
		std::vector<Observer *>observers; 	// observer list 
		bool changed;
}; 

#endif  // __OBSERABLE_HPP__

