all: cyoa-step1 cyoa-step2
cyoa-step%: cyoa-step%.cpp Story.hpp Page.hpp Choice.hpp
	g++ -o cyoa-step% -std=gnu++98 -pedantic -Wall -Werror -ggdb3 cyoa-step%.cpp
