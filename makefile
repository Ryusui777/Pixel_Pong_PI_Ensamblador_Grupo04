# all: run

# build: clean
# 	@mkdir -p build

	
# 	@for f in src/asm/*.asm; do \
# 		echo "   $$f → build/$$(basename $$f .asm).o"; \
# 		nasm -f elf64 "$$f" -o "build/$$(basename $$f .asm).o"; \
# 	done

# 	@for f in src/cpp/*.cpp; do \
# 		echo "   $$f → build/$$(basename $$f .cpp).o"; \
# 		g++ -c -Isrc/cpp/headers "$$f" -o "build/$$(basename $$f .cpp).o"; \
# 	done

# 	@g++ -no-pie build/*.o -lraylib -lm -ldl -lpthread -lGL -lX11 -o build/output


# run: build
# 	@./build/output

# clean:
# 	@rm -rf build
# Compilador y Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./include -no-pie
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -no-pie

# Ensamblador
AS = nasm
ASFLAGS = -f elf64

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Archivos fuente
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.asm)

# Archivos objeto
CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))
OBJECTS = $(CPP_OBJECTS) $(ASM_OBJECTS)

# Ejecutable
TARGET = $(BIN_DIR)/program

# Target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilar c++
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar ensamblador
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Correr programa
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/program

.PHONY: all clean run
