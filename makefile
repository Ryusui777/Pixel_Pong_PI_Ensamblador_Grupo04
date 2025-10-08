# ===== Config =====
CXX       := g++
ASM       := nasm
CXXFLAGS  := -std=c++20 -O2 -Wall -Wextra -Isrc/cpp/headers
ASFLAGS   := -f elf64
LDFLAGS   := -no-pie
# Raylib (Linux X11). Si usas pkg-config: LDFLAGS += $(shell pkg-config --libs --cflags raylib)
LIBS      := -lraylib -lm -ldl -lpthread -lGL -lX11

# ===== Fuentes / Objetos =====
ASM_SOURCES := $(wildcard src/asm/*.asm)
CPP_SOURCES := $(wildcard src/cpp/*.cpp)

OBJ_DIR     := build
ASM_OBJECTS := $(patsubst src/asm/%.asm, $(OBJ_DIR)/%.o, $(ASM_SOURCES))
CPP_OBJECTS := $(patsubst src/cpp/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SOURCES))
OBJECTS     := $(ASM_OBJECTS) $(CPP_OBJECTS)

TARGET := $(OBJ_DIR)/output

# ===== Targets de alto nivel =====
.PHONY: all build run clean val debug release

all: clean build run

build: $(TARGET)

run: $(TARGET)
	./$(TARGET)

val: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)

debug: CXXFLAGS += -O0 -g
debug: clean build

release: CXXFLAGS += -O3 -DNDEBUG
release: clean build

# ===== Reglas de construcción =====
$(TARGET): $(OBJECTS)
	@echo "🔗 Linkeando → $@"
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

# .asm → .o
$(OBJ_DIR)/%.o: src/asm/%.asm
	@mkdir -p $(OBJ_DIR)
	$(ASM) $(ASFLAGS) $< -o $@

# .cpp → .o
$(OBJ_DIR)/%.o: src/cpp/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

