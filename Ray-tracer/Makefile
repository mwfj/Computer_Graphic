## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -g -std=c++11
LFLAGS = -lglut -L/usr/lib -L/usr/X11R6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
		Vector2f.cpp\
		Vector3f.cpp\
		ObjLoader.cpp\
		Marix.cpp\
		Ray_tracer.cpp\
        assn2.cpp\
        $(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): Vector2f.o Vector3f.o ObjLoader.o Marix.o Ray_tracer.o assn2.o
	$(CC) -o run Vector2f.o Vector3f.o ObjLoader.o Marix.o Ray_tracer.o assn2.o ${LFLAGS}	

depend :
	makedepend ${PROGFILES}
# DO NOT DELETE
clean:
	rm -rf run
	rm -rf *.o
