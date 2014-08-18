SOURCES = main.o gameapp.o wrestler.o
all: $(SOURCES)
  c++ -o ww2d $(SOURCES)
clean:
  rm -f *.o ww2d
