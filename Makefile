NAME = computor

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC_SUBDIRS = $(SRC_DIR) $(SRC_DIR)/computor $(SRC_DIR)/solvers $(SRC_DIR)/utils

SRC_FILES = $(foreach dir, $(SRC_SUBDIRS), $(wildcard $(dir)/*.cpp))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
