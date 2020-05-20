CXX=g++

TARGET=snakegame
LIBS=-lncurses
OBJECTS=main.o

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

clean:
	rm *.o $(TARGET)