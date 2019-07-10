





CFLAGS_DEBUG =  -g -std=c++11
OUT_DEBUG = Debug/treecomp


CFLAGS_RELEASE = -O3  -std=c++11
LDFLAGS_RELEASE = -s
OUT_RELEASE = Release/treecomp

OBJ_DEBUG = Debug/interval.o Debug/itvtree.o Debug/rangetree2d.o Debug/rangetreeFC.o Debug/indexrtFC.o Debug/rtfc_eqkey.o Debug/treesearch_nooutput.o

OBJ_RELEASE = Release/interval.o Release/itvtree.o Release/rangetree2d.o Release/rangetreeFC.o Release/indexrtFC.o Release/rtfc_eqkey.o Release/treesearch_nooutput.o

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

Debug/itvtree.o: itvtree.cpp
	g++ $(CFLAGS_DEBUG) -c itvtree.cpp -o Debug/itvtree.o

Debug/rangetree2d.o: rangetree2d.cpp
	g++ $(CFLAGS_DEBUG) -c rangetree2d.cpp -o Debug/rangetree2d.o

Debug/rangetreeFC.o: rangetreeFC.cpp
	g++ $(CFLAGS_DEBUG) -c rangetreeFC.cpp -o Debug/rangetreeFC.o

Debug/indexrtFC.o: indexrtFC.cpp
	g++ $(CFLAGS_DEBUG) -c indexrtFC.cpp -o Debug/indexrtFC.o
	
Debug/rtfc_eqkey.o: rtfc_eqkey.cpp
	g++ $(CFLAGS_DEBUG) -c rtfc_eqkey.cpp -o Debug/rtfc_eqkey.o

Debug/treesearch_nooutput.o: treesearch_nooutput.cpp
	g++ $(CFLAGS_DEBUG) -c treesearch_nooutput.cpp -o Debug/treesearch_nooutput.o

clean_debug:
	rm -rf Debug





release: before_release out_release

out_release: before_release $(OBJ_RELEASE)
	g++  -o $(OUT_RELEASE) $(OBJ_RELEASE)  -O3

Release/interval.o: interval.cpp
	g++ $(CFLAGS_RELEASE) -c interval.cpp -o Release/interval.o

Release/itvtree.o: itvtree.cpp
	g++ $(CFLAGS_RELEASE) -c itvtree.cpp -o Release/itvtree.o

Release/rangetree2d.o: rangetree2d.cpp
	g++ $(CFLAGS_RELEASE) -c rangetree2d.cpp -o Release/rangetree2d.o

Release/rangetreeFC.o: rangetreeFC.cpp
	g++ $(CFLAGS_RELEASE) -c rangetreeFC.cpp -o Release/rangetreeFC.o

Release/indexrtFC.o: indexrtFC.cpp
	g++ $(CFLAGS_RELEASE) -c indexrtFC.cpp -o Release/indexrtFC.o
	
Release/rtfc_eqkey.o: rtfc_eqkey.cpp
	g++ $(CFLAGS_DEBUG) -c rtfc_eqkey.cpp -o Release/rtfc_eqkey.o

Release/treesearch_nooutput.o: treesearch_nooutput.cpp
	g++ $(CFLAGS_RELEASE) -c treesearch_nooutput.cpp -o Release/treesearch_nooutput.o

clean_release:
	rm -rf Release

.PHONY: before_debug  clean_debug before_release clean_release

