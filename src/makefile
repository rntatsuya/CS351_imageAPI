# set the C compiler, for C++ use g++
# use this setting on most sane machines
CC = gcc

# use this line on the engin linux machines
# CC = gcc296

# set the path to the include directory
INCDIR =../include

# set the flags for the C and C++ compiler to give lots of warnings
CFLAGS = -I$(INCDIR) -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations
CPPFLAGS = $(CFLAGS)

# path to the object file directory
ODIR = obj

# path to the lib directory
LIBDIR =../lib

# path to the bin directory
BINDIR =../bin

# libraries to include
LIBS = -lm -limageIO
LFLAGS = -L$(LIBDIR)

# put all of the relevant include files here
_DEPS = ppmIO.h image.h fractals.h color.h line.h circle.h polygon.h list.h graphics.h vector.h matrix.h view.h module.h drawstate.h lighting.h bezier.h 

# convert them to point to the right place
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

# put a list of the executables here
EXECUTABLES = test7a test7b test7c kha1 kha2 ext cylinder pyramid sphere test8a 

# put a list of all the object files here for all executables (with .o endings)
_OBJ = test7a.o test7b.o test7c.o kha1.o kha2.o ext.o pyramid.o cylinder.o  sphere.o test8a.o

# convert them to point to the right place
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# patterns for compiling source code
# $< is the file that caused the action to occur
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.C $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all:
	for i in $(EXECUTABLES); do (make $$i) ; done

# put the specific executable rules here

test7a: $(ODIR)/test7a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7b: $(ODIR)/test7b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
test7c: $(ODIR)/test7c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
kha1: $(ODIR)/kha1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
kha2: $(ODIR)/kha2.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

ext: $(ODIR)/ext.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

cylinder: $(ODIR)/cylinder.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

pyramid: $(ODIR)/pyramid.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

sphere: $(ODIR)/sphere.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test8a: $(ODIR)/test8a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

