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

CC = clang
#CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls 	# used for memory leaks detection
#CFLAGS = -Wall -Wextra -Werror # -g -fsanitize = address
CFLAGS = ""
CLIENT = client
SRCS1 =	src/client.c \
	src/conversion.c
OBJSRCS1 = $(SRCS1:.c=.o)

$(NAME) : $(CLIENT), $(SERVER)
$(CLIENT) : $(OBJSRCS1)
	@echo "Libft compilation..."
	@$(MAKE) -C ./libft
	@echo "Client compilation..."
	@$(CC) $(CFLAGS) $(OBJSRCS1) ./libft/libft.a -o $(CLIENT)

SERVER = server
SRCS2 =	src/server.c \
	src/server_tools.c \
	src/conversion.c
OBJSRCS2 = $(SRCS2:.c=.o)

$(SERVER) : $(OBJSRCS2)
	@echo "Server compilation..."
	@$(CC) $(CFLAGS) $(OBJSRCS2) ./libft/libft.a -o $(SERVER)
	@echo "Done !"

all : $(NAME)

test : $(NAME)
	./$(CLIENT)
clean :
	rm -rf $(OBJSRCS1)
	rm -rf $(OBJSRCS2)
	$(MAKE) clean -C ./libft

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(CLIENT)
	rm -rf $(SERVER)

re : fclean all

bonus : $(NAME)
