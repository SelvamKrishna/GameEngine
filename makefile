CXX := g++
CXXFLAGS := -std=c++20 -Iinclude -Iengine -Ivendor

DEBUG_FLAGS := -DPR_DEBUG -Wall -Wextra -g
DEBUG_FLAGS += -O2
RELEASE_FLAGS := -DNDEBUG -O3 -Wall -Wextra -Werror

LDFLAGS := vendor/libraylib.a -lwinmm -lgdi32 -lopengl32

ENGINE_DIR := engine
SANDBOX_DIR := sandbox
BUILD_DIR := build

ENGINE_SRC := $(wildcard $(ENGINE_DIR)/*/*.cpp) $(wildcard $(ENGINE_DIR)/*/*/*.cpp) 
ENGINE_OBJ := $(ENGINE_SRC:$(ENGINE_DIR)/%.cpp=$(BUILD_DIR)/engine/%.o)

SANDBOX_SRC := $(wildcard $(SANDBOX_DIR)/*.cpp)
SANDBOX_OBJ := $(SANDBOX_SRC:$(SANDBOX_DIR)/%.cpp=$(BUILD_DIR)/sandbox/%.o)

ENGINE_LIB := $(BUILD_DIR)/libengine.a
SANDBOX_BIN := $(BUILD_DIR)/sandbox.exe

all: debug

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(SANDBOX_BIN)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(SANDBOX_BIN)

$(ENGINE_LIB): $(ENGINE_OBJ)
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	ar rcs $@ $^

$(BUILD_DIR)/engine/%.o: $(ENGINE_DIR)/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/sandbox/%.o: $(SANDBOX_DIR)/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SANDBOX_BIN): $(SANDBOX_OBJ) $(ENGINE_LIB)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CXX) $^ -o $@ $(LDFLAGS)

run: debug
	./$(SANDBOX_BIN)

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

.PHONY: all debug release run clean