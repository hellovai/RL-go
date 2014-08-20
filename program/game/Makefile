include ../Makefile.inc

OBJLIBS	= ../$(BUILD)/libgame.a
OBJDIR = ../$(BUILD)/game

SRCS = game.cpp state.cpp move.cpp
OBJS	= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: buildrepo $(OBJLIBS)

buildrepo:
	mkdir -p $(OBJDIR)

$(OBJLIBS) : $(OBJS)
	$(ECHO) $(AR) $(ARFLAGS) rv $(OBJLIBS) $?
	$(AR) $(ARFLAGS) rv $(OBJLIBS) $?
	$(ECHO) $(RANLIB) $(OBJLIBS)
	$(RANLIB) $(OBJLIBS)

$(OBJDIR)/game.o: game.cpp $(OBJDIR)/state.o $(OBJDIR)/move.o
	$(CC) $(OPTS) -c $< -o $@

$(OBJDIR)/state.o: state.cpp $(OBJDIR)/move.o
	$(CC) $(OPTS) -c $< -o $@

$(OBJDIR)/move.o: move.cpp
	$(CC) $(OPTS) -c $< -o $@

clean:
	$(ECHO) cleaning up in game
	-$(RM) -f $(OBJDIR)
