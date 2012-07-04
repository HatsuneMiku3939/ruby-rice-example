#include "glue.hpp"
#include "ClockModel.hpp"
#include "ClockController.hpp"

using namespace Rice;

ObserverDirector::ObserverDirector(Object self) : Director(self) 
{ 
	// do nothing
}

void ObserverDirector::update(Observable *model) 
{
	getSelf().call("update", to_ruby(*model));
}

void ObserverDirector::default_update(Observable *model) 
{
	raisePureVirtual();
}

AbstractViewDirector::AbstractViewDirector(Object self) : Director(self) 
{ 
	// do nothing
}

void AbstractViewDirector::update(Observable *model) 
{
	ClockModel *clock_model = dynamic_cast<ClockModel *>(model);

	if(clock_model != NULL) {
		getSelf().call("update", to_ruby(*clock_model));
		return;
	}
	getSelf().call("update", to_ruby(*model));
}

void AbstractViewDirector::default_update(Observable *model) 
{
	raisePureVirtual();
}

template<>
Observer *from_ruby<Observer *>(Object x)
{
  Observer *retval;
  Data_Get_Struct(x.value(), Observer, retval);
  return retval;
}

void init_abstractview_warpper(void) 
{
	define_class<Observer>("Observer")
		.define_director<ObserverDirector>()
		.define_constructor(Constructor<ObserverDirector, Rice::Object>())
		.define_method("update", &ObserverDirector::default_update);

	define_class<AbstractView, Observer>("AbstractView")
		.define_director<AbstractViewDirector>()
		.define_constructor(Constructor<AbstractViewDirector, Rice::Object>())
		.define_method("model=", &AbstractView::setModel)
		.define_method("model", &AbstractView::getModel)
		.define_method("controller=", &AbstractView::setController)
		.define_method("controller", &AbstractView::getController);
}

void init_abstractcontroller_warpper(void) 
{
	define_class<AbstractController>("AbstractController")
		.define_constructor(Constructor<AbstractController>())
		.define_method("model=", &AbstractController::setModel)
		.define_method("model", &AbstractController::getModel)
		.define_method("view=", &AbstractController::setView)
		.define_method("view", &AbstractController::getView);

	define_class<ClockController, AbstractController>("ClockController")
		.define_constructor(Constructor<ClockController>())
		.define_method("run", &ClockController::run);
}

void init_clockmodel_wrapper(void)
{
	define_class<Observable>("Observable")
		.define_constructor(Constructor<Observable>())
		.define_method("add_observer", &Observable::addObserver)
		.define_method("remove_observer", &Observable::removeObserver)
		.define_method("notify_observer", &Observable::notifyObservers)
		.define_method("changed?", &Observable::isChanged)
		.define_method("count_observer", &Observable::countObserver)
		.define_method("set_changed", &Observable::setChanged)
		.define_method("clear_changed", &Observable::clearChanged);
	
	define_class<ClockModel, Observable>("ClockModel")
		.define_constructor(Constructor<ClockModel>())
		.define_method("hour=", &ClockModel::setHour)
		.define_method("minute=", &ClockModel::setMinute)
		.define_method("second=", &ClockModel::setSecond)
		.define_method("hour", &ClockModel::getHour)
		.define_method("minute", &ClockModel::getMinute)
		.define_method("second", &ClockModel::getSecond)
		.define_method("inc_hour", &ClockModel::incHour)
		.define_method("inc_minute", &ClockModel::incMinute)
		.define_method("inc_second", &ClockModel::incSecond);
}
