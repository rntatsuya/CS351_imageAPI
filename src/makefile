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
EXECUTABLES = test7a test7b test7c kha1proj7 kha2proj7 extproj7 cylinder pyramid sphere test8a cubism kha1proj8 kha2proj8 kha1proj9 kha2proj9

# put a list of all the object files here for all executables (with .o endings)
_OBJ = test7a.o test7b.o test7c.o kha1proj7.o kha2proj7.o extproj7.o pyramid.o cylinder.o sphere.o test8a.o cubism.o kha1proj8.o kha2proj8.o kha1proj9.o kha2proj9.o

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

# Project 7 
test7a: $(ODIR)/test7a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7b: $(ODIR)/test7b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
test7c: $(ODIR)/test7c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
kha1proj7: $(ODIR)/kha1proj7.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
kha2proj7: $(ODIR)/kha2proj7.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

extproj7: $(ODIR)/extproj7.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

cylinder: $(ODIR)/cylinder.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

pyramid: $(ODIR)/pyramid.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

sphere: $(ODIR)/sphere.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

# Project 8
test8a: $(ODIR)/test8a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

cubism: $(ODIR)/cubism.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

kha1proj8: $(ODIR)/kha1proj8.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
kha2proj8: $(ODIR)/kha2proj8.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

# Project 9 
kha1proj9: $(ODIR)/kha1proj9.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
	
kha2proj9: $(ODIR)/kha2proj9.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

