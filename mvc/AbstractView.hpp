#ifndef __ABSTRACTVIEW_HPP__
#define __ABSTRACTVIEW_HPP__

#include "Observable.hpp"
#include "Observer.hpp"
#include "AbstractController.hpp"

class AbstractView : public Observer
{
	public:
		AbstractView()
		{
			// do nothing
		}

		AbstractView(Observable *m, AbstractController *c) : model(m), controller(c)
		{
			// do nothing
		}

		virtual ~AbstractView()
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

		void setController(AbstractController *c)
		{
			controller = c;
			controller->setView(this);
		}

		AbstractController *getController(void)
		{
			return controller;
		}

	protected:
		Observable *model;
		AbstractController *controller;

};

#endif  // __ABSTRACTVIEW_HPP__

