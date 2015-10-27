#
# TODO: 
#

SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGET := bin/sopt_olsTestQuadratic
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++11
LIB := -larmadillo
INC := -I include

default: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CFLAGS) -c $< -o $@ $(INC) $(LIB)"; $(CXX) $(CFLAGS) -c $< -o $@ $(INC) $(LIB)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) -o $(TARGET) $^ $(LIB)"; $(CXX) -o $(TARGET) $^  $(LIB)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#  $(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#  $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean