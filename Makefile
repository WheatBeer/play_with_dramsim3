SRCDIR=src
OBJDIR=obj
EXTDIR=ext
DRAMSIMDIR=$(EXTDIR)/DRAMsim3

CXX=g++
CXXFLAGS=-g -Wall -O3 -std=c++11 -I$(DRAMSIMDIR)/src
LDFLAGS=-L$(DRAMSIMDIR)
LIBFLAGS=-ldramsim3

SRCS=$(wildcard $(SRCDIR)/*.cc)
HDRS=$(wildcard $(SRCDIR)/*.h)
OBJS=$(SRCS:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
EXE=project

.PHONY: default 
default: $(EXE)

$(EXE): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBFLAGS) 

$(OBJDIR)/%.o : $(SRCDIR)/%.cc $(HDRS)
	@mkdir -pv $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE)
	rm -rf $(OBJDIR)
