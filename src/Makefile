# The g++ compiler.
CC = g++
# Flags passed to the compiler
CFLAGS = -c -Wall -Werror -g
IDIR = include
ODIR = obj
SRCS := $(shell find . -name '*.cpp')
_OBJS = $(SRCS:.cpp=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
EXEC = magrathea
LIBS = -lglut -lGLU -lGLEW

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
