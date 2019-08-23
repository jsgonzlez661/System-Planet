NAME   = planet
CPP    = g++
SOURCE = $(NAME).cpp
OBJ    = $(NAME).o
BIN    = $(NAME)
#BIN    = $(NAME).exe
CFLAGS = -O3 -Wall
LFLAGS = -g
LIBS   = -lglut -lGLU -lGL -lm 

All: $(BIN)

$(BIN):$(OBJ)
	$(CPP) $(LDFLAGS) -o $(BIN) $(OBJ) $(LIBS) 

$(OBJ): $(SOURCE)
	$(CPP) $(CFLAGS) -c $(SOURCE)

clean: 
	rm -f $(OBJ) $(BIN)


