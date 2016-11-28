# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaustry <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 05:15:37 by jaustry           #+#    #+#              #
#    Updated: 2016/11/28 05:15:41 by jaustry          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

all:
	make -C ./libft/
	make -C ./machine_virtuel/
	make -C ./asm/

clean:
	make -C ./libft/ clean
	make -C ./machine_virtuel/ clean
	make -C ./asm/ clean


fclean: clean
	make -C ./libft/ fclean
	make -C ./machine_virtuel/ fclean
	make -C ./asm/ fclean

re: fclean all
