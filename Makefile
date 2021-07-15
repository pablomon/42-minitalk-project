# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/28 19:15:11 by pmontese          #+#    #+#              #
#    Updated: 2021/06/06 01:58:33 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   = server
CLIENT   = client

CC	     = gcc $(FLAGS)
#FLAGS =
FLAGS    = -Wall -Werror -Wextra
SERVER_SRC = src/server.c src/libft.c src/linked_lst.c src/server_tools.c src/conversion.c
CLIENT_SRC = src/client.c src/libft.c src/conversion.c

SERVER_SRC_OBJ	= $(SERVER_SRC:.c=.o)
CLIENT_SRC_OBJ	= $(CLIENT_SRC:.c=.o)

all :	fclean $(SERVER_SRC_OBJ) $(CLIENT_SRC_OBJ)
		@$(CC) $(SERVER_SRC) -I minitalk.h -o server
		@$(CC) $(CLIENT_SRC) -I minitalk.h -o client

clean :
	@rm -rf ./src/*.o

fclean: clean
	@rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY : all clean fclean