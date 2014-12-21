include Makefile.inc

DIRS	= game
EXE	= ./$(BIN)/game
OBJS	= $(BUILD)/main.o
GAMELIB	= $(LIBDIR)/libgame.a
LIBS	=-L./$(LIBDIR) -lgame
GDEF = -D USE_GLOG -D USE_GFLAGS
GLIBS = -lglog -lgflags

all: buildrepo build
	$(ECHO) run $(EXE)

gbuild: buildrepo ggamelib gserverlib
	$(CC) $(CFLAGS) $(CPPFLAGS) $(GDEF) -c ./main.cpp -o ./$(BUILD)/main.o
	$(LD) -o $(EXE) $(OBJS) $(LIBS) $(GLIBS)
	$(ECHO) run $(EXE)

buildrepo:
	mkdir -p $(BIN)
	mkdir -p $(BUILD)
	mkdir -p $(LIBDIR)

build: gamelib serverlib
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./main.cpp -o ./$(BUILD)/main.o
	$(LD) -o $(EXE) $(OBJS) $(LIBS)

gamelib: buildrepo game/game.cpp game/move.cpp game/state.cpp
	(cd ./game; $(CC) -std=gnu++0x -c game.cpp -o ../$(BUILD)/game.o)
	(cd ./game; $(CC) -std=gnu++0x -c move.cpp -o ../$(BUILD)/move.o)
	(cd ./game; $(CC) -std=gnu++0x -c state.cpp -o ../$(BUILD)/state.o)
	$(AR) $(ARFLAGS) $(GAMELIB) ./$(BUILD)/game.o ./$(BUILD)/move.o ./$(BUILD)/state.o

ggamelib: buildrepo game/game.cpp game/move.cpp game/state.cpp
	(cd ./game; $(CC) $(GDEF) -std=gnu++0x -c game.cpp -o ../$(BUILD)/game.o)
	(cd ./game; $(CC) $(GDEF) -std=gnu++0x -c move.cpp -o ../$(BUILD)/move.o)
	(cd ./game; $(CC) $(GDEF) -std=gnu++0x -c state.cpp -o ../$(BUILD)/state.o)
	$(AR) $(ARFLAGS) $(GAMELIB) ./$(BUILD)/game.o ./$(BUILD)/move.o ./$(BUILD)/state.o

serverlib:
	$(ECHO) server not yet functional

gserverlib:
	$(ECHO) server not yet functional

clean:
	$(ECHO) cleaning up in .
	-$(RM) -f $(EXE) $(OBJS) $(OBJLIBS)
	-$(RM) -rf $(BUILD) $(BIN) $(LIBDIR)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look:
	true
