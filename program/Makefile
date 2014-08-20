include Makefile.inc

DIRS	= game
EXE	= ./$(BIN)/game
OBJS	= $(BUILD)/main.o
OBJLIBS	= $(BUILD)/libgame.a
LIBS	=-L./$(BUILD) -lgame -lglog

all: buildrepo $(EXE)
	$(ECHO) run $(EXE)

buildrepo:
	mkdir -p $(BIN)
	mkdir -p $(BUILD)

$(EXE): $(OBJS) $(OBJLIBS)
	$(ECHO) $(LD) -o $(EXE) $(OBJS) $(LIBS)
	$(LD) -o $(EXE) $(OBJS) $(LIBS)

$(OBJS):
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./main.cpp -o $(OBJS)

$(BUILD)/lib%.a: %
	$(ECHO) building ./$< : $(MAKE) $(MFLAGS)
	cd $<; $(MAKE) $(MFLAGS)

clean:
	$(ECHO) cleaning up in .
	-$(RM) -f $(EXE) $(OBJS) $(OBJLIBS)
	-$(RM) -rf $(BUILD) $(BIN)
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

force_look:
	true
