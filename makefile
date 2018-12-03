





CFLAGS_DEBUG =  -g -std=c++11
OUT_DEBUG = Debug/treecomp


CFLAGS_RELEASE = -O3  -std=c++11
LDFLAGS_RELEASE = -s
OUT_RELEASE = Release/treecomp

OBJ_DEBUG = Debug/interval.o Debug/intervaltree.o Debug/rangetree2d.o Debug/rangetreeFC.o Debug/indexrtFC.o Debug/treesearch_nooutput.o

OBJ_RELEASE = Release/interval.o Release/intervaltree.o Release/rangetree2d.o Release/rangetreeFC.o Release/indexrtFC.o Release/treesearch_nooutput.o

all: debug release

clean: clean_debug clean_release

before_debug:
	test -d Debug || mkdir -p Debug

before_release:
	test -d Release || mkdir -p Release



debug: before_debug out_debug

out_debug: before_debug $(OBJ_DEBUG)
	g++ -o $(OUT_DEBUG) $(OBJ_DEBUG)

Debug/interval.o: interval.cpp
	g++ $(CFLAGS_DEBUG) -c interval.cpp -o Debug/interval.o

Debug/intervaltree.o: intervaltree.cpp
	g++ $(CFLAGS_DEBUG) -c intervaltree.cpp -o Debug/intervaltree.o

Debug/rangetree2d.o: rangetree2d.cpp
	g++ $(CFLAGS_DEBUG) -c rangetree2d.cpp -o Debug/rangetree2d.o

Debug/rangetreeFC.o: rangetreeFC.cpp
	g++ $(CFLAGS_DEBUG) -c rangetreeFC.cpp -o Debug/rangetreeFC.o

Debug/indexrtFC.o: indexrtFC.cpp
	g++ $(CFLAGS_DEBUG) -c indexrtFC.cpp -o Debug/indexrtFC.o

Debug/treesearch_nooutput.o: treesearch_nooutput.cpp
	g++ $(CFLAGS_DEBUG) -c treesearch_nooutput.cpp -o Debug/treesearch_nooutput.o

clean_debug:
	rm -rf Debug





release: before_release out_release

out_release: before_release $(OBJ_RELEASE)
	g++  -o $(OUT_RELEASE) $(OBJ_RELEASE)  -O3

Release/interval.o: interval.cpp
	g++ $(CFLAGS_RELEASE) -c interval.cpp -o Release/interval.o

Release/intervaltree.o: intervaltree.cpp
	g++ $(CFLAGS_RELEASE) -c intervaltree.cpp -o Release/intervaltree.o

Release/rangetree2d.o: rangetree2d.cpp
	g++ $(CFLAGS_RELEASE) -c rangetree2d.cpp -o Release/rangetree2d.o

Release/rangetreeFC.o: rangetreeFC.cpp
	g++ $(CFLAGS_RELEASE) -c rangetreeFC.cpp -o Release/rangetreeFC.o

Release/indexrtFC.o: indexrtFC.cpp
	g++ $(CFLAGS_RELEASE) -c indexrtFC.cpp -o Release/indexrtFC.o

Release/treesearch_nooutput.o: treesearch_nooutput.cpp
	g++ $(CFLAGS_RELEASE) -c treesearch_nooutput.cpp -o Release/treesearch_nooutput.o

clean_release:
	rm -rf Release

.PHONY: before_debug  clean_debug before_release clean_release

