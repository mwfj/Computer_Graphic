## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -g -std=c++11 -O2
LFLAGS = -lglut -L/usr/lib -L/usr/X11R6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
		Vector2f.cpp\
		Vector3f.cpp\
		Point.cpp\
		Line.cpp\
		Triangle.cpp\
		ObjLoader.cpp\
		Marix.cpp\
		Color.cpp\
		Illumination.cpp\
		Ray.cpp\
		Ray_tracer.cpp\
        assn3.cpp\
        $(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): Vector2f.o Vector3f.o Point.o Line.o Triangle.o ObjLoader.o Marix.o Color.o Illumination.o Ray.o Ray_tracer.o assn3.o
	$(CC) -o run Vector2f.o Vector3f.o Point.o Line.o Triangle.o ObjLoader.o Marix.o Color.o Illumination.o Ray.o Ray_tracer.o assn3.o ${LFLAGS}	

depend :
	makedepend ${PROGFILES}
# DO NOT DELETE
clean:
	rm -rf run
	rm -rf *.o
