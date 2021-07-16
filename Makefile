# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/28 19:15:11 by pmontese          #+#    #+#              #
#    Updated: 2021/07/16 13:48:55 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   = server
CLIENT   = client

CC	     = gcc $(FLAGS)
FLAGS    = -Wall -Werror -Wextra
SERVER_SRC = src/server.c src/libft.c src/linked_lst.c src/server_tools.c src/conversion.c
CLIENT_SRC = src/client.c src/libft.c src/conversion.c src/client_tools.c

SERVER_OBJ	= $(SERVER_SRC:.c=.o)
CLIENT_OBJ	= $(CLIENT_SRC:.c=.o)

all :	$(SERVER) $(CLIENT)

$(SERVER) :	$(SERVER_OBJ)
	@echo "Building server"
	$(CC) $(SERVER_SRC) -I minitalk.h -o server
$(CLIENT) :	$(CLIENT_OBJ)
	@echo "Building client"
	$(CC) $(CLIENT_SRC) -I minitalk.h -o client

clean :
	@rm -rf ./src/*.o

fclean: clean
	@rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY : all clean fclean
