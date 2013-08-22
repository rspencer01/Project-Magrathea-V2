# The g++ compiler.
CC = g++
# Flags passed to the compiler
CFLAGS = -c -Wall -Werror
IDIR = src/include
ODIR = obj
SRCS = main.cpp
_OBJS = $(SRCS:.cpp=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
EXEC = magrathea
LIBS = 

all: $(ODIR) $(OBJS) $(EXEC)

$(ODIR):
	mkdir $(ODIR)

$(EXEC):
	$(CC) $(OBJS) $(LIBS) -o $(EXEC)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -r $(ODIR)
	rm $(EXEC)
