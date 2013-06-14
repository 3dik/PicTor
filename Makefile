CC = g++ -O6
CFLAGS = `pkg-config gtkmm-2.4 --cflags` -W -pedantic
OBJECTS = Main.o Pic.o Convert.o Functions.o Err.o Buf.o ConvertFile.o ConvertBmp.o ConvertBit.o ConvertLamer.o
LIBS = `pkg-config gtkmm-2.4 --cflags --libs`

all: pictor

pictor: $(OBJECTS)
	$(CC) -o pictor $(CFLAGS) $(OBJECTS) $(LIBS)

%.o: %.cpp %.hpp
	$(CC) -c $(CFLAGS) $<
