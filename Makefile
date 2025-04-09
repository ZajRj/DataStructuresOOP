# Compilador y banderas (C++98)
CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -I.
LDFLAGS = 

# Directorios
SRC_DIR = .
BUILD_DIR = build

# Fuentes (solo archivos .cpp que necesitan compilación)
MAIN_SRC = elfos.cpp

# Objetos
MAIN_OBJ = $(BUILD_DIR)/$(MAIN_SRC:.cpp=.o)

# Ejecutable
EXECUTABLE = elfos

# Reglas
all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

.PHONY: all clean