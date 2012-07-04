#ifndef __GLUE_HPP__
#define __GLUE_HPP__

#include "rice/Director.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/VM.hpp"

#include "mvc/mvc.hpp"

using namespace Rice;

class ObserverDirector : public Observer, public Rice::Director 
{
	public:
		ObserverDirector(Object self);

		virtual void update(Observable *model);
		void default_update(Observable *model);
};

class AbstractViewDirector : public AbstractView, public Rice::Director 
{
	public:
		AbstractViewDirector(Object self);

		virtual void update(Observable *model);
		void default_update(Observable *model);
};

void init_abstractview_warpper(void);
void init_abstractcontroller_warpper(void);
void init_clockmodel_wrapper(void);

#endif  // __GLUE_HPP__
