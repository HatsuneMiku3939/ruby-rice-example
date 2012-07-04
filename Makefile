CPP = g++

PROGRAM = clock
RUBY_ROOT = /home/dmw/.rvm/rubies/ruby-1.9.3-p125
GEM_ROOT = /home/dmw/.rvm/gems/ruby-1.9.3-p125/gems
INCDIR = -I. -I$(RUBY_ROOT)/include/ruby-1.9.1/i686-linux \
	-I$(RUBY_ROOT)/include/ruby-1.9.1/ruby/backward \
	-I$(RUBY_ROOT)/include/ruby-1.9.1 \
	-I/home/dmw/.rvm/usr/include \
	-I$(GEM_ROOT)/rice-1.4.3/ruby/lib/include 
DEFS = -D_FILE_OFFSET_BITS=64
CPPFLAGS = -Os -fPIC -g -ggdb -Wall -Wextra -Wno-unused-parameter -Wno-parentheses \
	-Wpointer-arith -Wwrite-strings -Wno-missing-field-initializers -Wno-long-long \
	$(INCDIR) $(DEFS)

LDDIR =  -L. -L$(RUBY_ROOT)/lib \
	-Wl,-R$(RUBY_ROOT)/lib \
	-L/home/dmw/.rvm/usr/lib \
	-Wl,-R/home/dmw/.rvm/usr/lib \
	-Wl,-R -Wl,$(RUBY_ROOT)/lib \
	-L$(RUBY_ROOT)/lib \
	-L$(GEM_ROOT)/rice-1.4.3/ruby/lib/lib 
LIB = -lruby -lpthread -lrt -ldl -lcrypt -lm -lc -lrice
LDFLAGS = $(LDDIR) $(LIB)

OBJS = main.o ClockModel.o ClockController.o glue.o
SRCS = $(OBJS:.o=.cpp)
.SUFFIXES : .cpp .o

.cpp.o:
	@echo CPP $<
	@$(CPP) $(CPPFLAGS) -c $<

all: main

main: def $(OBJS)
	@echo LINK $(PROGRAM)
	@$(CPP) -o $(PROGRAM) $(OBJS) $(LDFLAGS)

clean: 
	@rm -rf $(OBJS) $(PROGRAM) .depend

def: 
	@$(CPP) -M $(SRCS) $(INCDIR) $(DPFS) > .depend

ifeq (.depend, $(wildcard .depend))
include .depend
endif
