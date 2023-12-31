# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emman <emman@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/10/15 11:19:33 by emman            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	controls.c		\
		flood_fill.c	\
		init_data.c		\
		init_text.c		\
		utils.c			\
		main.c			\
		movements.c		\
		parsing.c		\
		parsing_utils.c	\
		parsing_utils2.c\
		raycast.c		\
		raycast_utils.c	\

BONUS =	controls_bonus.c		\
		door_bonus.c			\
		flood_fill_bonus.c		\
		init_data_bonus.c		\
		init_text_bonus.c		\
		utils_bonus.c			\
		main_bonus.c			\
		movements_bonus.c		\
		parsing_bonus.c			\
		parsing_utils_bonus.c	\
		parsing_utils2_bonus.c	\
		raycast_bonus.c			\
		raycast_utils_bonus.c	\
		minimap_bonus.c			\

HEADERS	:= -I ./include/cub3d.h -I $(LIBMLX_DIR)include/
SRCS_DIR = ./srcs/
OBJS_DIR = ./srcs/objs_cub3D/
OBJS = $(SRCS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)

BONUS_HEADERS	:= -I ./include/cub3d_bonus.h -I $(LIBMLX_DIR)include/
BONUS_SRCS_DIR = ./srcs/bonus/
BONUS_OBJS_DIR = ./srcs/bonus/objs_cub3D_bonus/
BONUS_OBJS = $(BONUS:$(BONUS_SCRS_DIR)%.c=$(BONUS_OBJS_DIR)%.o)

LIBFT_DIR = ./srcs/libft/
LIBFT = ./srcs/libft/libft.a

LIBMLX_DIR	:= ./MLX42/
LIBMLX	:= $(LIBMLX_DIR)/build/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

NAME = cub3D

BONUS_NAME = cub3D_bonus

CFLAGS = -Wall -Wextra -Werror

CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all: mlx $(NAME)

mlx: #dep
	(cd $(LIBMLX_DIR) && cmake -B build)
	make -C $(LIBMLX_DIR)build/

dep:
	brew install glfw
	brew install cmake

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBMLX) $(LIBFT) -o $(NAME)
	@echo "${GREEN}CUB3D COMPILED${NC}"

$(BONUS_OBJS_DIR)%.o:$(BONUS_SRCS_DIR)%.c
	@mkdir -p $(BONUS_OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BONUS_NAME): $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBMLX) $(LIBFT) -o $(BONUS_NAME)
	@echo "${GREEN}CUB3D BONUS COMPILED${NC}"

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/map01.cub

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "${RED}CUB3D OBJECTS DELETED${NC}"
	@$(MAKE) clean -C $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 CLEANED${NC}"

fclean: clean
	@$(MAKE) fclean -C ./srcs/libft
	@rm -f $(NAME)
	@echo "${RED}CUB3D DELETED${NC}"
	@rm -rf $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 BUILD DELETED${NC}"

bonus: mlx $(BONUS_NAME)

bonusclean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(BONUS_OBJS_DIR)
	@echo "${RED}CUB3D BONUS OBJECTS DELETED${NC}"
	@$(MAKE) clean -C $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 CLEANED${NC}"
	
bonusfclean: bonusclean
	@$(MAKE) fclean -C ./srcs/libft
	@rm -f $(BONUS_NAME)
	@echo "${RED}CUB3D BONUS DELETED${NC}"
	@rm -rf $(LIBMLX_DIR)build/
	@echo "${RED}MLX42 BUILD DELETED${NC}"

re: fclean all

.PHONY: all clean fclean bonus bonusclean bonusfclean re