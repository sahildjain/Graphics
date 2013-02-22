CC      = c++
LD      = c++
CFLAGS  = -I/usr/X11R6/include -std=c++0x -I. -c
LDFLAGS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXi -lXmu -lXt -lXext -lX11 -lSM -lICE -lm

INCS = 

OBJS = surfaceModelParser.o cgRender.o 

all: cgRender

clean:
	rm -rf $(OBJS) cgRender

cgRender.o: $(INCS) cgRender.cpp
	$(CC) $(CFLAGS) cgRender.cpp -o cgRender.o

surfaceModelParser.o: surfaceModelParser.cpp
	$(CC) $(CFLAGS) surfaceModelParser.cpp -o surfaceModelParser.o

cgRender: $(OBJS)
	$(LD) $(OBJS) -o cgRender $(LDFLAGS)

