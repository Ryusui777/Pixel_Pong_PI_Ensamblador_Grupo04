# Compilador y Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./include -no-pie
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -no-pie
TESTFLAGS = -lgtest -lgtest_main -pthread -no-pie

# Ensamblador
AS = nasm
ASFLAGS = -f elf64

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include
TEST_DIR = tests

# Archivos fuente
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.asm)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

# Archivos objeto
CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test_%.o, $(TEST_SOURCES))

# Objetos sin main.o para tests
CPP_OBJECTS_NO_MAIN = $(filter-out $(BUILD_DIR)/main.o, $(CPP_OBJECTS))

OBJECTS = $(CPP_OBJECTS) $(ASM_OBJECTS)

# Ejecutables
TARGET = $(BIN_DIR)/program
TEST_TARGET = $(BIN_DIR)/test_runner

# Target principal
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilar C++
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar ensamblador
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Compilar tests
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build tests
$(TEST_TARGET): $(ASM_OBJECTS) $(TEST_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(ASM_OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(TESTFLAGS) $(LDFLAGS)

# Correr programa
run: $(TARGET)
	./$(TARGET)

# Correr tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean todo
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/program $(BIN_DIR)/test_runner

# Clean solo tests
clean-tests:
	rm -rf $(BUILD_DIR)/test_*.o $(BIN_DIR)/test_runner

CPPLINT_FLAGS = --filter=-build/include_subdir,-readability/casting,-runtime/references
lint-src:
	cpplint $(CPPLINT_FLAGS) $(SRC_DIR)/*.cpp

lint-include:
	cpplint $(CPPLINT_FLAGS) $(INCLUDE_DIR)/*.h

.PHONY: all clean run test clean-tests lint-all lint-include lint-src
