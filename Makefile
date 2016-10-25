FLAGS=-g -Wall -std=c++11
LIB=-pthread
EXEC=prodcons
SRC=ProdCons.cpp Util.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(FLAGS) $^ $(LIB) -o $@

clean:
	$(RM) $(EXEC)

