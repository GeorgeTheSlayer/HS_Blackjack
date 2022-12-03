XX = g++
FLAGS= -std=c++11 -O2 -Wall -Werror -Wextra

DEPS = dealer.h
OBJ =  main.o dealer.o

%.o: %.cpp $(DEPS)
		$(CXX) -c -o $@ $< $(CFLAGS)

app: $(OBJ)
		$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.o && rm app

