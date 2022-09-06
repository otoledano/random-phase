CCC = gcc
INCLUDE = .
NAME = RP

CFLAGS = -fopenmp -Wall -I$(INCLUDE) -O2 -fno-strict-aliasing
CFLAGS +=  -fomit-frame-pointer -fPIC
LDFLAGS = -lm

OBJS = $(NAME).o input_variables.o files.o general_functions.o final_output.o potential_energy.o

DEPS = input_variables.h files.h general_functions.h final_output.h potential_energy.h

default: $(NAME)
clean:
	rm -f *.o $(NAME)

$(NAME): $(OBJS)
	$(CCC) $(CFLAGS) -o $@  $^ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CCC) $(CFLAGS) -c -o $@ $< $(OPTS)
