#include "rice/Director.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/VM.hpp"

#include "ClockModel.hpp"
#include "ClockController.hpp"
#include "glue.hpp"

#include <iostream>
#include <csignal>
#include <vector>

using namespace Rice;

class ClockApplication
{
	public:
		explicit ClockApplication();
		virtual ~ClockApplication();
		
		int initialize(void);
		int run(int argc, char **argv);

		int init_ruby_vm(const char *script);
	
	private:
		int init_glue_code(void);
	
	private:
		ClockModel model;
		Object view;
		ClockController controller;

		std::auto_ptr<VM> vm;
};

ClockApplication::ClockApplication()
{
}

int ClockApplication::initialize(void)
{
	controller.setModel(&model);
	
	view = rb_class_new_instance(0, 0,
	                             rb_const_get(rb_cObject, rb_intern("ClockView")));

	std::cout << "Chaning between ClockView and ClockModel" << std::endl;
	view.call("model=", to_ruby(model));

	std::cout << "Chaning between ClockView and ClockController" << std::endl;
	view.call("controller=", to_ruby(controller));

	model.addObserver(from_ruby<Observer *>(view));			
	
	model.setHour(0);
	model.setMinute(0);
	model.setSecond(57);

	return 0;
}

ClockApplication::~ClockApplication()
{
	// do nothing
}

int ClockApplication::run(int argc, char **argv)
{
	return controller.run();
}

int ClockApplication::init_ruby_vm(const char *script)
{
	int error;

	std::vector<const char *> args;
	args.push_back("embedded");
	args.push_back(script);

	std::cout << "Run RUBY VM" << std::endl;
	vm.reset(new VM(args));
	ruby_script("embedded");

	init_glue_code();
	
	rb_protect((VALUE (*)(VALUE))rb_require, (VALUE)script, &error);

	if(error)
		return error;

	return 0;
}

int ClockApplication::init_glue_code(void)
{
	init_abstractview_warpper();
	init_abstractcontroller_warpper();
	init_clockmodel_wrapper();

	return 0;
}

void int_handler(int x)
{
	exit(0);
}

int catched_main(int argc, char **argv)
{
	ClockApplication app;
	if(app.init_ruby_vm("./RubyClockView.rb")) {
		std::cout << "Something was wrong!" << std::endl;
		return 1;
	}
	app.initialize();

	std::cout << "Run Application\n" << std::endl;
	return app.run(argc, argv);
}

int main(int argc, char **argv)
{
	int res;
	signal(SIGINT, int_handler);
	
	try {	
		res = catched_main(argc, argv);
	} catch(...) {
		res = 1;
	}

	return res;
}
