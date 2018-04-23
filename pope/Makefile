# Directories
SRC_DIR := ./src
BUILD_DIR := ./build
INC_DIRS := ./include
#Compiler
CXX := g++
# Flags
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPP_FLAGS := -std=c++17 $(INC_FLAGS) -O2 -O3 -MMD -MP
YAML_FLAGS := -lyaml-cpp
# Objects
SRCS := $(shell cd $(SRC_DIR); find . -name "*.cpp")
OBJS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SRCS)))
DEPS := $(OBJS:.o=.d)
# Make
pope.out: $(OBJS)
	$(CXX) $(CPP_FLAGS) $(OBJS) -o $@ $(YAML_FLAGS)
$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPP_FLAGS) -c $(INCLUDES) $< -o $@
# Clean
clean:
	rm -r $(BUILD_DIR)
	rm ./pope.out

.PHONY: all clean

-include $(DEPS)
