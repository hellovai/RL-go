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
	$(CC) $(CFLAGS) $(CPPFLAGS) ./main.cpp -o ./$(BUILD)/main.o
	$(LD) -o $(EXE) $(OBJS) $(LIBS) -pg

playerlib: buildrepo players/Player.cpp players/AIPlayer.cpp players/UCTBrain.cpp
	(cd ./players; $(CC) $(CFLAGS) $(CPPFLAGS) Player.cpp -o ../$(BUILD)/players.o)
	(cd ./players; $(CC) $(CFLAGS) $(CPPFLAGS) AIPlayer.cpp -o ../$(BUILD)/aiplayers.o)
	(cd ./players; $(CC) $(CFLAGS) $(CPPFLAGS) UCTBrain.cpp -o ../$(BUILD)/uctbrain.o)
	$(AR) $(ARFLAGS) $(PLAYERLIB) ./$(BUILD)/players.o ./$(BUILD)/aiplayers.o ./$(BUILD)/uctbrain.o

gplayerlib: buildrepo players/Player.cpp players/AIPlayer.cpp
	(cd ./players; $(CC) $(GDEF) $(CFLAGS) $(CPPFLAGS) Player.cpp -o ../$(BUILD)/players.o)
	(cd ./players; $(CC) $(GDEF) $(CFLAGS) $(CPPFLAGS) AIPlayer.cpp -o ../$(BUILD)/aiplayers.o)
	(cd ./players; $(CC) $(GDEF) $(CFLAGS) $(CPPFLAGS) UCTBrain.cpp -o ../$(BUILD)/uctbrain.o)
	$(AR) $(ARFLAGS) $(PLAYERLIB) ./$(BUILD)/players.o ./$(BUILD)/aiplayers.o ./$(BUILD)/uctbrain.o

gamelib: buildrepo game/game.cpp game/move.cpp game/state.cpp
	(cd ./game; $(CC) $(CFLAGS) $(CPPFLAGS) game.cpp -o ../$(BUILD)/game.o)
	(cd ./game; $(CC) $(CFLAGS) $(CPPFLAGS) move.cpp -o ../$(BUILD)/move.o)
	(cd ./game; $(CC) $(CFLAGS) $(CPPFLAGS) state.cpp -o ../$(BUILD)/state.o)
	$(AR) $(ARFLAGS) $(GAMELIB) ./$(BUILD)/game.o ./$(BUILD)/move.o ./$(BUILD)/state.o

ggamelib: buildrepo game/game.cpp game/move.cpp game/state.cpp
	(cd ./game; $(CC) $(GDEF) $(CFLAGS) $(CPPFLAGS) game.cpp -o ../$(BUILD)/game.o)
	(cd ./game; $(CC) $(GDEF) $(CFLAGS) $(CPPFLAGS) move.cpp -o ../$(BUILD)/move.o)
	(cd ./game; $(CC) $(GDEF) $(CFLAGS) $(CPPFLAGS) state.cpp -o ../$(BUILD)/state.o)
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
