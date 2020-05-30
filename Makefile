SRCDIR=src
OBJDIR=obj
MAIN=$(SRCDIR)/main.cc

CXX=g++
CXXFLAGS=-g -Wall -O3 -std=c++11 -IDRAMsim3/src
LDFLAGS=-LDRAMsim3
LIBFLAGS=-ldramsim3

SRCS=$(filter-out $(MAIN), $(wildcard $(SRCDIR)/*.cc))
HDRS=$(wildcard $(SRCDIR)/*.h)
OBJS=$(SRCS:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
EXE=project

.PHONY: default 
default: directories $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBFLAGS) -o $@ $(MAIN) $< 

$(OBJS): $(SRCS) 
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

directories:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE)
	rm -rf $(OBJDIR)
