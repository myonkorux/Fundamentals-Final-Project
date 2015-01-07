CMP = gcc
MAIN = asteroidsT
GRAPH = gfx3
FUNC = asteroidsTfn
EXEC = asteroidsT
FLAGS = -lm -lX11

$(EXEC): $(MAIN).o $(FUNC).o $(GRAPH).o
	$(CMP) $(MAIN).o $(FUNC).o $(GRAPH).o $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).c $(GRAPH).h $(FUNC).h
	$(CMP) -c $(MAIN).c

$(GRAPH).o: $(GRAPH).c
	$(CMP) -c $(GRAPH).c

$(FUNC).o:
	$(CMP) -c $(FUNC).c

clean:
	rm *.o $(EXEC)
