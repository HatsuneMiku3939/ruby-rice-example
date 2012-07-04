#ifndef __ABSTRACTCONTROLLER_HPP__
#define __ABSTRACTCONTROLLER_HPP__

#include "Observer.hpp"

class AbstractView;

class AbstractController 
{
	public:
		AbstractController()
		{
			// do nothing
		}

		AbstractController(Observable *m) : model(m)
		{
			// do nothing
		}

		virtual ~AbstractController()
		{
			// do nothing
		}

		void setModel(Observable *m)
		{
			model = m;
		}

		Observable *getModel(void)
		{
			return model;
		}

		void setView(AbstractView *v)
		{
			view = v;
		}

		AbstractView *getView(void)
		{
			return view;
		}

	protected:
		Observable *model;
		AbstractView *view;
};

#endif  // __ABSTRACTCONTROLLER_HPP__

