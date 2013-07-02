#
#	GMK Makefile
#

# Paths
SOURCES_PATH=src
INCLUDE_PATH=include
OBJECTS_PATH=objs
TARGET=libgmk.a

# Tools
CXX=g++
AR=ar

# Parse Parameters
SOURCES=$(foreach dir, $(SOURCES_PATH), $(wildcard $(dir)/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
OBJLIST=$(addprefix $(OBJECTS_PATH)/,$(OBJECTS))

# Rules
all: $(TARGET)

$(TARGET): $(OBJLIST)
	$(AR) rvs $(TARGET) $(OBJLIST)

$(OBJECTS_PATH)/%.o: %.cpp
	$(CXX) -I$(SOURCES_PATH)/$(INCLUDE_PATH) -c $< -o $@
	
clean:
	@find $(OBJECTS_PATH) -name '*.o' | xargs rm  -f
	@rm -f $(TARGET)
