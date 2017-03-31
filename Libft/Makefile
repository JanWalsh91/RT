# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 13:07:31 by jwalsh            #+#    #+#              #
#    Updated: 2017/02/22 14:16:27 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FT_MEM = ft_bzero \
		ft_memset \
		ft_memcpy \
		ft_memccpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_memalloc \
		ft_memdel \
		ft_swap \
		ft_swapd

FT_IO = get_next_line \
		ft_putchar \
		ft_putwchar \
		ft_putstr \
		ft_putendl \
		ft_putnbr \
		ft_putchar_fd \
		ft_putwchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putwstr_fd \
		ft_putwstr_fd \
		ft_error \
		ft_error_exit \
		ft_display_usage_exit \
		ft_errno_exit

FT_STR = ft_strlen \
		ft_strdup \
		ft_strdupfree \
		ft_strcpy \
		ft_strncpy \
		ft_strcat \
		ft_strncat \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strstr \
		ft_strnstr \
		ft_strcmp \
		ft_strncmp \
		ft_strnew \
		ft_strdel \
		ft_strclr \
		ft_strscmp \
		ft_strcmp_percent \
		ft_striter \
		ft_striteri \
		ft_strmap \
		ft_strmapi \
		ft_strequ \
		ft_strnequ \
		ft_strrev \
		ft_strsub \
		ft_strtrim \
		ft_strsplit \
		ft_strjoin \
		ft_strsjoin \
		ft_strjoinfree \
		ft_strsjoinfree \
		ft_strappend \
		ft_strappendfree \
		ft_straddchar \
		ft_straddcharfree \
		ft_charcount

FT_USTR = ft_ustrnew \
		ft_ustrdup \
		ft_ustrdupfree \
		ft_ustrlen \
		ft_ustrcpy \
		ft_ustrncpy \
		ft_ustrappend \
		ft_ustrappendfree \
		ft_ustrjoin \
		ft_ustrjoinfree \
		ft_ustrsjoin \
		ft_ustrsjoinfree \
		ft_ustrncat

FT_WSTR = ft_wstrnew \
		ft_wstrlen \
		ft_wstrappend \
		ft_wstrsjoin \
		ft_wstrsjoinfree \
		ft_wstrappendfree

FT_IS = ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_ispunct \
		ft_isspace \
		ft_islower \
		ft_isupper

FT_LST = ft_lstnew \
		ft_lstdelone \
		ft_lstdel \
		ft_lstadd \
		ft_lstadd_end \
		ft_lstiter \
		ft_lstmap

FT_TO = ft_atoi \
		ft_itoa \
		ft_itoa_base \
		ft_uitoa_base \
		ft_wctostr \
		ft_wstrtostr \
		ft_toupper \
		ft_tolower \
		ft_strtolower \
		ft_strtoupper \
		ft_atod

FT_PRINTF = ft_printf \
		check_flags \
		check_precision \
		check_type \
		get_address \
		get_char \
		get_format \
		get_int \
		get_percent \
		get_string \
		get_unsigned_int \
		init_arg \
		init_data \
		parse_arg \
		parse_flags \
		parse_length \
		parse_precision \
		parse_type \
		parse_until_arg \
		parse_width \
		set_byte_count

FT_MISC = ft_clamp \
		ft_clampd \
		ft_range

OBJ_DIR = obj

EXT = .c

SRC_MEM = $(addsuffix $(EXT), $(FT_MEM))
SRC_IO = $(addsuffix $(EXT), $(FT_IO))
SRC_STR = $(addsuffix $(EXT), $(FT_STR))
SRC_USTR = $(addsuffix $(EXT), $(FT_USTR))
SRC_WSTR = $(addsuffix $(EXT), $(FT_WSTR))
SRC_IS = $(addsuffix $(EXT), $(FT_IS))
SRC_LST = $(addsuffix $(EXT), $(FT_LST))
SRC_TO = $(addsuffix $(EXT), $(FT_TO))
SRC_PRINTF = $(addsuffix $(EXT), $(FT_PRINTF))
SRC_MISC = $(addsuffix $(EXT), $(FT_MISC))
OBJ_MEM = $(addprefix $(OBJ_DIR)/, $(SRC_MEM:.c=.o))
OBJ_IO = $(addprefix $(OBJ_DIR)/, $(SRC_IO:.c=.o))
OBJ_STR = $(addprefix $(OBJ_DIR)/, $(SRC_STR:.c=.o))
OBJ_USTR = $(addprefix $(OBJ_DIR)/, $(SRC_USTR:.c=.o))
OBJ_WSTR = $(addprefix $(OBJ_DIR)/, $(SRC_WSTR:.c=.o))
OBJ_IS = $(addprefix $(OBJ_DIR)/, $(SRC_IS:.c=.o))
OBJ_LST = $(addprefix $(OBJ_DIR)/, $(SRC_LST:.c=.o))
OBJ_TO = $(addprefix $(OBJ_DIR)/, $(SRC_TO:.c=.o))
OBJ_PRINTF = $(addprefix $(OBJ_DIR)/, $(SRC_PRINTF:.c=.o))
OBJ_MISC = $(addprefix $(OBJ_DIR)/, $(SRC_MISC:.c=.o))

HEAD = libft.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

C_NONE = \033[0m
C_BOLD = \033[1m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_BROWN = \033[33m
C_BLUE = \033[34m
C_MAGENTA = \033[35m
C_CYAN = \033[36m
C_GRAY = \033[37m

all: $(NAME)

$(NAME): $(OBJ_MEM) $(OBJ_IO) $(OBJ_STR) $(OBJ_USTR) $(OBJ_WSTR) $(OBJ_IS) $(OBJ_LST) $(OBJ_TO) $(OBJ_PRINTF) $(OBJ_MISC) 
	@ar rcs $(NAME) $(OBJ_MEM) $(OBJ_IO) $(OBJ_STR) $(OBJ_USTR) $(OBJ_WSTR) $(OBJ_IS) $(OBJ_LST) $(OBJ_TO) $(OBJ_PRINTF) $(OBJ_MISC)
	@echo "$(C_CYAN)Libft compilation done.$(C_NONE)"

$(OBJ_DIR)/%.o : ./ft_mem/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_io/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_str/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_ustr/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_wstr/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_is/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_lst/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_to/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_printf/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./ft_misc/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I./inc -c -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
	@echo "$(C_CYAN)Libft clean done.$(C_NONE)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(C_CYAN)Libft fclean done.$(C_NONE)"

re: fclean
	@$(MAKE) all

.PHONY: clean fclean
	@echo "$(C_CYAN)Libft .PHONY done.$(C_NONE)"
