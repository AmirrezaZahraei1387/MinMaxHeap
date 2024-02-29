
CXX = g++

OBJ = main.o
EXE_NAME = demo
HEADERS = MinMaxH/MinMaxHeap.hpp MinMaxH/MinMaxHeapCore.inl MinMaxH/MinMaxHeapMem.inl MinMaxH/MinMaxHeapTe.inl
CONFIG_H = MinMaxH/ConfigDir.hpp



.PHONY:
all: $(EXE_NAME)

.PHONY:
check: $(EXE_NAME)
	./$(EXE_NAME)

.PHONY:
clean:
	rm $(EXE_NAME) $(OBJ)

$(EXE_NAME): main.o
	g++ main.o -o $(EXE_NAME)

main.o: $(HEADERS) $(CONFIG_H)
