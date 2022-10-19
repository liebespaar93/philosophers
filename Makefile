# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 12:53:58 by kyoulee           #+#    #+#              #
#    Updated: 2022/10/19 13:06:02 by kyoulee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = $(PHILO_DIR)/philo

CC = cc
CXXFLAGS = $(NULL)
CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(INCLUDE_DIR)
LDFLAGS = $(NULL)
LDLIBS = $(NULL)

# COLORS
BG_RED     = \033[41m
BG_GREEN   = \033[42m
BG_YELLOW  = \033[43m
BG_BLUE    = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN    = \033[46m
BG_LGREY   = \033[47m
BG_DGREY   = \033[100m
BG_LRED    = \033[101m
BG_LGREEN  = \033[102m
BG_LYELLOW = \033[103m
BG_LBLUE   = \033[104m
BG_LMAGENTA= \033[105m
BG_LCYAN   = \033[106m
BG_WHITE   = \033[107m
BG_MAKE1   = \033[48;5;236m
BG_MAKE2   = \033[48;5;238m
BG_MAKE3   = \033[48;5;240m
 
FG_BLACK   = \033[30m
FG_RED     = \033[31m
FG_GREEN   = \033[32m
FG_YELLOW  = \033[33m
FG_BLUE    = \033[34m
FG_MAGENTA = \033[35m
FG_CYAN    = \033[36m
FG_LGREY   = \033[37m
FG_DGREY   = \033[90m
FG_LRED    = \033[91m
FG_LGREEN  = \033[92m
FG_LYELLOW = \033[93m
FG_LBLUE   = \033[94m
FG_LMAGENTA= \033[95m
FG_LCYAN   = \033[96m
FG_WHITE   = \033[97m
 
CL_BOLD   = \033[1m
CL_DIM    = \033[2m
CL_UDLINE = \033[4m
CL_BLINK  = \033[5m
CL_INVERT = \033[7m
CL_HIDDEN = \033[8m
 
NO_COLOR = \033[0m

#####***** DIR *****#####

ROOTDIR = $(abspath $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))
PHILO_DIR = $(ROOTDIR)/philo
SRC_DIR = $(PHILO_DIR)/src

OBJ_DIR = $(PHILO_DIR)/obj
INCLUDE_DIR = $(PHILO_DIR)/include

#####***** SRC *****#####

SRC_C_FILE =	\
				ft_atoi.c	\
				ft_pthread.c	\
				init.c	\
				main.c	\
				print_mutex.c	\
				time.c	\
				work.c

SRC_C = $(addprefix $(SRC_DIR)/, $(SRC_C_FILE))

## SRC OBJS ##
OBJS =	$(SRC_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_CLEAN = $(OBJS)
#####***** working *****#####

all : $(OBJ_DIR) $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) $(OBJS_SERVER) -o $(TARGET)
	@echo "$(FG_MAGENTA)ar $(FG_LBLUE)src $(FG_LYELLOW)$@$(FG_LCYAN)"
	@(for i in $(OBJS) $(OBJS_GET_NEXT_LINE) $(OBJS_DIMENSION); do echo $$i; done)
	@echo "$(FG_WHITE)"

$(OBJ_DIR) : 
	mkdir $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

clean : 
	@rm -f $(OBJS_CLEAN)
	@(for F in $(OBJS_CLEAN); do echo $$F; done)

fclean : OBJS_CLEAN+=$(TARGET)
fclean : clean

re : fclean all

.PHONY: all bonus clean fclean re
