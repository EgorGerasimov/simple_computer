SRC=$(wildcard *.c)
SRC_DIR=console
OBJ_DIR=../obj
LIBS=$(wildcard $(OBJ_DIR)/*.a)
INCLUDE_DIR=../include
OBJ=$(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SRC:%.c=%.o))
LFLAGS=-Wall -Wextra -I $(INCLUDE_DIR)
CC=gcc
EXECUTABLE=console

.PHONY: all rebuild $(EXECUTABLE) clean $(EXECUTABLE).a

all: create_dir $(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

run:
	@./$(EXECUTABLE)

font: create_dir
	@$(CC) $(LFLAGS) -o font font.c $(LIBS)

$(EXECUTABLE): $(EXECUTABLE).a
	@$(CC) $(LFLAGS) -o ../console/$(EXECUTABLE) main.c $(LIBS)

$(EXECUTABLE).a: $(OBJ)
	@ar rcs $(OBJ_DIR)/$(EXECUTABLE).a $(shell find "$(OBJ_DIR)/$(SRC_DIR)" -name "*.o" ! -name "main.o" ! -name "font.o")

$(OBJ_DIR)/$(SRC_DIR)/%.o: %.c
	@$(CC) $(LFLAGS) -c -o $@ $^

clean:
	@echo "cleaning..."
	@rm -rf $(OBJ_DIR)/$(SRC_DIR) $(EXECUTABLE) ./font
	
cpp_clang:
	@clang-format -i --verbose *.c *.h
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

create_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)

leaks:	
	@valgrind --leak-check=full ./$(EXECUTABLE)