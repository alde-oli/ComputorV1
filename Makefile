NAME = computor

CC = g++
FLAGS = -Wall -Wextra -Werror 

SRC_FOLDER = src
INC_FOLDER = inc
OBJ_FOLDER = obj

SRC = $(shell find $(SRC_FOLDER) -name '*.cpp')
OBJ = $(patsubst $(SRC_FOLDER)/%.cpp, $(OBJ_FOLDER)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I $(INC_FOLDER) -c $< -o $@

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
