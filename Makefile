################################################################################
##                               Présentation                                 ##
################################################################################

COLOR_NORM		=	\033[0m
COLOR_RED		=	\033[31m
COLOR_PURPLE	=	\033[35m

################################################################################
##                               SRCS                                         ##
################################################################################

MK = Makefile

# Headers

DIR_HDS				=	includes

RELATIVE_HDS		= nm.h 

# Code

DIR_GLOBAL						=	srcs
SRC_GLOBAL						=	error.c   \
												formatElf.c     \
												parsing.c     \
												sortList.c     \
												ft_printf.c     \
												endian.c     \
												symbol.c     \
												symbols.c     \
												List.c     \
												init.c     \
												print.c     \
												parseTable.c     \
												tools.c     \
												main.c

################################################################################
##                       Compilation Environnement                            ##
################################################################################

NAME	=	ft_nm
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -O3 -g3 -ggdb# -fsanitize=address
# Sources
DIRS_SRC			=	$(DIR_GLOBAL)

DIR_OBJ				=	obj

SRCS		=	$(addprefix $(DIR_GLOBAL)/, $(SRC_GLOBAL))					\

HDS			=	$(addprefix $(DIR_HDS)/, $(RELATIVE_HDS))
OBJS		=	$(addprefix $(DIR_OBJ)/, $(SRCS:.c=.o))

DEPENDS		=	$(HDS) $(MK) $(LIBFT_NAME)

################################################################################
##                                 Règles                                     ##
################################################################################

all		:	$(NAME)

define src2obj

$(DIR_OBJ)/$(1)/%.o:	$(1)/%.c $(2)
	@mkdir -p $(DIR_OBJ)/$(1)
	@printf "\r\033[K\t[✅]\t$(COLOR_PURPLE)$$< --> $$@\$(COLOR_NORM)"
	@$(CC) $(CFLAGS) -c -o $$@ $$< $(INC_INC)
endef

$(foreach dir,$(DIRS_SRC),$(eval $(call src2obj,$(dir), $(DEPENDS))))

$(NAME)	: $(DEPENDS) $(OBJS)
	@printf "\n[✅]\tCompilation of $(COLOR_PURPLE)$(NAME)\$(COLOR_NORM)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@printf "[✅]\tDelete $(COLOR_RED)object of $(DIR_GLOBAL)$(COLOR_NORM) of $(NAME)\n"
	@rm -rf $(DIR_OBJ)

fclean: clean
	@printf "[✅]\tDelete $(COLOR_RED)all binary on $(DIR_LIBFT)$(COLOR_NORM)\n"
	@rm -rf $(NAME)

re:	fclean all
