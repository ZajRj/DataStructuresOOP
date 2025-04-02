# Compilador y banderas (C++98)
CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -I.

# Directorios
BUILD_DIR = build
LIST_DIR = List
QUEUE_DIR = Queue
STACK_DIR = Stack
NODE_DIR = Node

# Fuentes
SRCS = $(LIST_DIR)/SinglyList.cpp $(QUEUE_DIR)/Queue.cpp $(STACK_DIR)/Stack.cpp $(NODE_DIR)/SinglyNode.cpp $(NODE_DIR)/DoublyNode.cpp
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Reglas
all: $(BUILD_DIR) main_program

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/$(LIST_DIR) $(BUILD_DIR)/$(QUEUE_DIR) $(BUILD_DIR)/$(STACK_DIR) $(BUILD_DIR)/$(NODE_DIR)

main_program: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) main_program

.PHONY: all clean