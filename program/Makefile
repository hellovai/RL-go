include Makefile.inc

DIRS	= game
EXE	= ./$(BIN)/game
OBJS	= $(BUILD)/main.o
GAMELIB	= $(LIBDIR)/libgame.a
PLAYERLIB = $(LIBDIR)/libplayers.a
LIBS	=-L./$(LIBDIR) -lgame -lplayers
GDEF = -D USE_GLOG -D USE_GFLAGS
GLIBS = -lglog -lgflags

all: buildrepo build
	$(ECHO) run $(EXE)

gbuild: buildrepo ggamelib gplayerlib gserverlib
	$(CC) $(CFLAGS) $(CPPFLAGS) $(GDEF) -c ./main.cpp -o ./$(BUILD)/main.o
	$(LD) -o $(EXE) $(OBJS) $(LIBS) $(GLIBS)
	$(ECHO) run $(EXE)

buildrepo:
	mkdir -p $(BIN)
	mkdir -p $(BUILD)
	mkdir -p $(LIBDIR)

build: gamelib playerlib serverlib
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./main.cpp -o ./$(BUILD)/main.o
	$(LD) -o $(EXE) $(OBJS) $(LIBS)

playerlib: buildrepo players/Player.cpp players/AIPlayer.cpp
	(cd ./players; $(CC) -std=gnu++0x -c Player.cpp -o ../$(BUILD)/players.o)
	(cd ./players; $(CC) -std=gnu++0x -c AIPlayer.cpp -o ../$(BUILD)/aiplayers.o)
	$(AR) $(ARFLAGS) $(PLAYERLIB) ./$(BUILD)/players.o ./$(BUILD)/aiplayers.o

gplayerlib: buildrepo players/Player.cpp players/AIPlayer.cpp
	(cd ./players; $(CC) $(GDEF) -std=gnu++0x -c Player.cpp -o ../$(BUILD)/players.o)
	(cd ./players; $(CC) $(GDEF) -std=gnu++0x -c AIPlayer.cpp -o ../$(BUILD)/aiplayers.o)
	$(AR) $(ARFLAGS) $(PLAYERLIB) ./$(BUILD)/players.o ./$(BUILD)/aiplayers.o

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
