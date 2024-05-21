NAME = computor

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc


SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re
