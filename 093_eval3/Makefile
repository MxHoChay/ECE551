CFLAGS=-std=gnu++98 -Werror -Wall -pedantic -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %, %.o, $(PROGS))
all: $(PROGS)
cyoa-step%: cyoa-step%.o
	g++ -o $@ $^
cyoa-step%.o: cyoa-step%.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)
