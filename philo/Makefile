.SILENT:
.PHONY: all clean fclean re main help fsanitize valgrind

#------------------------------------------------------------------------------#
# 							VARIABLES										   #
#------------------------------------------------------------------------------#

NAME            = philo
EXEC			= exec/philo

OBJS_DIR		= .objs/
EXEC_DIR		= exec/
INC			    = -I .
TINC			= -I .

INCLUDEF		= philosophers.h

CFILES          = \
		main      			\
		init	  			\
		routine   			\
		utils	  			\
		dead	  			\
		ft_atoi	  			\
		check_and_unlock

SRC				= $(patsubst %, %.c, $(CFILES))
OBJS			= $(patsubst %.c, .objs/%.o, $(SRC))


#------------------------------------------------------------------------------#
# 							COMMANDS									       #
#------------------------------------------------------------------------------#


RM 				= rm -f
RM_DIR			= rm -rf
CC				= cc
MAKE			= make

CFLAGS 			= -Wall -Wextra -Werror
CFSIGSEV        = -fsanitize=address
THREADCFLAGS    = -lpthread
PURPLE          = \033[1;35m
GREEN           = \033[1;32m
RED             = \033[1;31m
YELLOW          = \033[33m
BOLD_UNDERLINE  = \033[1;4m
RESET           = \033[0m


#------------------------------------------------------------------------------#
# 							COMPILATION RULES								   #
#------------------------------------------------------------------------------#


all: $(NAME)

fsanitize:
	$(MAKE) CFLAGS="$(CFLAGS) $(CFSIGSEV)"

valgrindmacos:
	docker build -t philosophers .
	docker run --rm philosophers
	docker rm $(docker ps -a -q)

valgrind: $(EXEC_G3)
		$(MAKE) $(EXEC_G3)
		if [ -z "$(FLAGS)" ]; then \
			echo "$(PURPLE)Please define FLAGS (e.g., make valgrind FLAGS=1).$(RESET)"; \
		elif [ "$(FLAGS)" -eq 1 ]; then \
			valgrind --leak-check=full ./$(EXEC); \
		elif [ "$(FLAGS)" -eq 2 ]; then \
			valgrind --track-origins=yes ./$(EXEC); \
		elif [ "$(FLAGS)" -eq 3 ]; then \
			valgrind --tool=massif ./$(EXEC); \
		else \
			echo "$(RED)Invalid FLAGS value. Use 1, 2, or 3.$(RESET)"; \
		fi; \
		echo "$(RED)Deleting $(EXEC)...$(RESET)"; \
		if [ -f $(EXEC) ]; then $(RM) $(EXEC); fi; \
		echo "$(GREEN)Deleting $(EXEC) completed successfully!$(RESET)"

tests: all $(TOBJS) $(EXEC) | $(EXEC_DIR)
	echo "$(YELLOW)Compiling tests...$(RESET)"
	$(CC) $(CFLAGS) $(TINC) -o $(EXEC_DIR)test_philosopher.out $(TOBJS) $(EXEC) $(THREADCFLAGS)

	echo "$(GREEN)Tests compiled successfully! Now running tests...$(RESET)"

	$(EXEC_DIR)test_philosopher.out

	echo "$(GREEN)Tests executed successfully!$(RESET)"

clean:
	echo "$(RED)Deleting object files...$(RESET)"

		$(RM_DIR) $(OBJS_DIR)
		$(RM) massif.out*

	echo "$(GREEN)Deleting object files completed successfully!$(RESET)"

fclean: clean
	echo "$(RED)Deleting $(NAME)...$(RESET)"

		$(RM_DIR) $(EXEC_DIR)

	echo "$(GREEN)Deleting $(NAME) completed successfully!$(RESET)"
	
	echo "$(RED)"
	echo "┌──────────────────────────────────────────────────────────┐"
	echo "│      Deletion finished successfully! ( ◔ ω◔) ノシ        │"
	echo "└──────────────────────────────────────────────────────────┘"
	
	echo "                          ╱|、"
	echo "                        (˚ˎ 。7"
	echo "                         |、˜|"
	echo "                        じしˍ,)ノ"
	
	echo "$(RESET)"


re : fclean all


help:
	echo "$(YELLOW)\n                  =============================="
	echo "                        $(BOLD_UNDERLINE)AVAILABLE TARGETS:$(RESET)"
	echo "$(YELLOW)                  ==============================$(RESET)"
	echo " "
	echo "$(GREEN)───────────────────────────────────────────────────────────────────"
	echo " "
	echo "$(GREEN)  all$(RESET)           $(PURPLE)-$(RESET) Compile the library and generate $(NAME)"
	echo "$(GREEN)  clean$(RESET)         $(PURPLE)-$(RESET) Remove all object files and temporary build files"
	echo "$(GREEN)  fclean$(RESET)        $(PURPLE)-$(RESET) Perform 'clean' and remove the $(NAME) archive"
	echo "$(GREEN)  re$(RESET)            $(PURPLE)-$(RESET) Rebuild everything from scratch"
	echo "$(GREEN)  main$(RESET)          $(PURPLE)-$(RESET) Compile and run the main program with $(NAME)"
	echo "$(GREEN)  valgrind$(RESET)      $(PURPLE)-$(RESET) Run Valgrind with optional FLAGS for memory analysis"
	echo " "
	echo "           .  $(GREEN)FLAGS=1$(RESET) $(PURPLE)->$(RESET) Leak check"
	echo "           .  $(GREEN)FLAGS=2$(RESET) $(PURPLE)->$(RESET) Track origins of errors"
	echo "           .  $(GREEN)FLAGS=3$(RESET) $(PURPLE)->$(RESET) Memcheck, a memory error detector"
	echo " "  
	echo "$(GREEN)  fsanitize$(RESET)     $(PURPLE)-$(RESET) Compile with sanitizers to detect memory errors"
	echo " "
	echo "$(GREEN)───────────────────────────────────────────────────────────────────"


#------------------------------------------------------------------------------#
# 							DIRECTORY CREATION RULES						   #
#------------------------------------------------------------------------------#


$(OBJS_DIR):
	echo "$(YELLOW)Creating directory $(OBJS_DIR)...$(RESET)"
		
		mkdir -p $(OBJS_DIR)

$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR) directory...$(RESET)"

		mkdir -p $(EXEC_DIR)

$(TEST_OBJS_DIR):
	echo "$(YELLOW)Creating directory $(TEST_OBJS_DIR)...$(RESET)"
	mkdir -p $(TEST_OBJS_DIR)

#------------------------------------------------------------------------------#
# 							BUILD RULES										   #
#------------------------------------------------------------------------------#

$(NAME): $(OBJS) $(INCLUDE) | $(EXEC_DIR)
	echo "$(PURPLE)Compiling $(NAME) in progress...$(RESET)"

		$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(THREADCFLAGS)

	echo "$(GREEN)$(EXEC) completed successfully!$(RESET)"

	echo "$(GREEN)"
	echo "┌───────────────────────────────────────────────────────────┐"
	echo "│      Compilation finished successfully! ᕕ(⌐■_■)ᕗ ♪♬       │"
	echo "└───────────────────────────────────────────────────────────┘"

	echo "                      ☆  *    .      ☆"
	echo "                        ∧＿∧   ∩    * ☆"
	echo "                 *  ☆ ( ・∀・)/ ."
	echo "                  .  ⊂      ノ* ☆"
	echo "                ☆ * (つ   ノ  .☆"
	echo "                      (ノ"

	echo "$(RESET)"


$(OBJS_DIR)%.o: %.c $(INCLUDEF) | $(OBJS_DIR)
	echo "$(PURPLE)Compiling $<...$(RESET)"

		$(CC) $(CFLAGS) $(INC) -c $< -o $@

	echo "$(GREEN)$< completed successfully!$(RESET)"

$(TEST_OBJS_DIR)%.o: $(TEST_DIR)%.c $(INCLUDEF) | .test_objs
	echo "$(PURPLE)Compiling test $<...$(RESET)"
	$(CC) $(CFLAGS) $(TINC) -c $< -o $@

$(EXEC_G3): $(OBJS) | $(OBJS_DIR)
	echo "$(PURPLE)Compiling $< with g3...$(RESET)"
		
		$(CC) $(CFLAGS) -o $(EXEC) -g3 $(OBJS)

	echo "$(GREEN)$< completed successfully!$(RESET)"