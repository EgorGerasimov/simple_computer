SRC=$(wildcard *.c)
SRC_DIR=simpleassembler
OBJ_DIR=../obj
LIBS=$(wildcard $(OBJ_DIR)/*.a)
INCLUDE_DIR=../include
OBJ=$(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SRC:%.c=%.o))
LFLAGS=-Wall -Wextra -I $(INCLUDE_DIR) -g3
CC=gcc
EXECUTABLE=simpleassembler

.PHONY: all rebuild $(EXECUTABLE) clean $(EXECUTABLE).a

all: create_dir $(EXECUTABLE) $(EXECUTABLE).a

rebuild: clean $(EXECUTABLE)

run: 
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@$(CC) $(LFLAGS) -o $(EXECUTABLE) $(OBJ) $(LIBS)

$(EXECUTABLE).a: $(OBJ)
	@ar rcs $(OBJ_DIR)/$(EXECUTABLE).a $(shell find "$(OBJ_DIR)/$(SRC_DIR)" -name "*.o" -not -name "main.o")

$(OBJ_DIR)/$(SRC_DIR)/%.o: %.c
	@$(CC) $(LFLAGS) -c -o $@ $^

clean:
	@echo "cleaning..."
	@rm -rf $(OBJ_DIR)/$(SRC_DIR) $(EXECUTABLE)
	
cpp_clang:
	clang-format -i --verbose *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

create_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)

leaks:	
	valgrind --leak-check=full ./$(EXECUTABLE)