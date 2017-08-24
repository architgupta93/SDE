CC=g++
LDFLAGS=
CFLAGS=-c -g
DEBUG_FLAGS=-D__DEBUG__
#DEBUG_FLAGS+=-D__PRINT_DETAILS__
INCLUDE_DIRS=$(shell pwd)
CFLAGS+=-I $(INCLUDE_DIRS)
CFLAGS+=$(DEBUG_FLAGS)

ALL_HEADERS=wiener_process.h multipath_rv.h gaussian_multipath_rv.h
ALL_SRCS=multipath_rv.cpp gaussian_multipath_rv.cpp
ALL_DEPS=$(ALL_SRCS)
ALL_DEPS+=$(ALL_HEADERS)
ALL_OBJS=$(ALL_SRCS:.cpp=.o)

BASIC_HEADERS=SDE.h integrator.h ito_integrator.h stochastic_integrator.h vec_ops.h

all: kuramoto

# Basic stuff required by all the experiments: Compiling .cpp files to create
# object files
%.o: %.cpp $(BASIC_HEADERS) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $< -o $@

# Experiment 03: Simulating the Kuramoto model with noise
KRM_SRCS=examples/kuramoto_sde.cpp
KRM_HEADERS=$(BASIC_HEADERS)
KRM_SRCS+=$(KRM_HEADERS:.h=.cpp)
KRM_DEPS=$(KRM_HEADERS)
KRM_DEPS+=$(KRM_SRCS)
KRM_OBJS=$(KRM_SRCS:.cpp=.o)

kuramoto: $(KRM_OBJS) $(ALL_OBJS)
	$(CC) $(LDFLAGS) $(KRM_OBJS) $(ALL_OBJS) -o $@

# Experiment 02: Simulating a black-scholes like SDE system using an Ito
# integral (We should have done the same using a Stratanovich integral as well)
# TODO! Simulation runs without the use of an equation engine

BS_SRCS=examples/sde_black_scholes.cpp
BS_HEADERS=$(BASIC_HEADERS)
BS_SRCS+=$(BS_HEADERS:.h=.cpp)
BS_DEPS=$(BS_HEADERS)
BS_DEPS+=$(BS_SRCS)
BS_OBJS=$(BS_SRCS:.cpp=.o)

black_scholes: $(BS_OBJS) $(ALL_OBJS)
	$(CC) $(LDFLAGS) $(BS_OBJS) $(ALL_OBJS) -o $@

# Experiment 01: Simulation of a toy SDE, The functions f and g  were written by
# hand and simulated
SSDE_SRCS=examples/simple_sde.cpp 
SSDE_HEADERS=$(BASIC_HEADERS)
SSDE_HEADERS+=$(ALL_HEADERS)
SSDE_SRCS+=$(SSDE_HEADERS:.h=.cpp)
SSDE_DEPS=$(SSDE_HEADERS)
SSDE_DEPS+=$(SSDE_SRCS)
SSDE_OBJS=$(SSDE_SRCS:.cpp=.o)

ssde: $(SSDE_OBJS) $(ALL_OBJS)
	$(CC) $(LDFLAGS) $(SSDE_OBJS) $(ALL_OBJS) -o $@

# Experiment 01.a: Simulation of a toy linear ODE, The functions f and g  were
# written by hand and simulated
SSDE_SRCS=examples/simple_ode.cpp 
SSDE_HEADERS=$(BASIC_HEADERS)
SSDE_SRCS+=$(SSDE_HEADERS:.h=.cpp)
SSDE_DEPS=$(SSDE_HEADERS)
SSDE_DEPS+=$(SSDE_SRCS)
SSDE_OBJS=$(SSDE_SRCS:.cpp=.o)

ode: $(SSDE_OBJS) $(ALL_OBJS)
	$(CC) $(LDFLAGS) $(SSDE_OBJS) $(ALL_OBJS) -o $@

clean:
	rm -rf examples/*.o
	rm -rf models/*.o
	rm -rf *data.tmp
	rm -rf *.o
	rm -rf kuramoto ssde black_scholes hh_det
