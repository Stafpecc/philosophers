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
		time				\
		take_forks			\
		init_mutexes

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

#------------------------------------------------------------------------------#
# 							DIRECTORY CREATION RULES						   #
#------------------------------------------------------------------------------#


$(OBJS_DIR):
	echo "$(YELLOW)Creating directory $(OBJS_DIR)...$(RESET)"
		
		mkdir -p $(OBJS_DIR)

$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR) directory...$(RESET)"

		mkdir -p $(EXEC_DIR)

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
