# The g++ compiler.
CC = g++
# Flags passed to the compiler
CFLAGS = -c --std=c++11 -Wall -Werror -g -I /usr/include/glm
IDIR = include
ODIR = obj
SRCS := $(shell find . -name '*.cpp')
_OBJS = $(SRCS:.cpp=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
EXEC = magrathea
LIBS = -lGL -lglut -lGLU -lGLEW

all: $(ODIR) $(OBJS) $(EXEC)

$(ODIR):
	mkdir $(ODIR)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(EXEC)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -I $(IDIR) $(CFLAGS) -o $@ $<

clean:
	rm -r $(ODIR)
	rm $(EXEC)
