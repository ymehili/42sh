##
## EPITECH PROJECT, 2024
## Delivery
## File description:
## Makefile
##

## ------------------------------------ ##
##              VARIABLES               ##

CC 					:= gcc
CFLAGS 				:= -I./include/ -W -Wall -Wextra
DFLAGS 				:= -g3
EXECUTABLE 			:= 42sh
TEST_EXECUTABLE 	:= unit_tests

SRCDIR 				:= src
OBJDIR 				:= obj
TESTDIR 			:= tests

SOURCES_FILES 		:= $(shell find $(SRCDIR) -name '*.c')
OBJECTS_FILES 		:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES_FILES))
SOURCES_FILES_TEST 	:= $(filter-out $(SRCDIR)/main.c, $(SOURCES_FILES))
TESTER_FILES 		:= $(shell find $(TESTDIR) -name '*.c')

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CFLAGS += $(DFLAGS)
endif

## ------------------------------------ ##
##                RULES                 ##

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@rm -f $(TEST_EXECUTABLE)
	@rm -f *.gcno
	@rm -f *.gcda

fclean: clean
	@rm -f $(EXECUTABLE)

tester: all
	@cp $(EXECUTABLE) tester
	@cd tester && ./tester.sh && rm -f $(EXECUTABLE)
	make fclean

unit_tests:
	$(CC) $(CFLAGS) $(SOURCES_FILES_TEST) $(TESTER_FILES) -lcriterion \
	--coverage -o $(TEST_EXECUTABLE)

tests_run: unit_tests
	./$(TEST_EXECUTABLE)

tests_gcovr: unit_tests
	@gcovr --exclude $(TESTDIR)

re: fclean all

.PHONY: all clean fclean re unit_tests tests_run tests_gcovr tester