NAME = so_long
MACOS = so_long_macos

MLX_LINUX = mlx_linux/libmlx.a
MLX_MACOS = mlx_macos/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror 

OBJS_DIR = objs

SRCS = so_long.c \
	tools.c \
	error_checks.c \
	flood_fill.c \
	window_management.c \
	rendering.c \
	game.c \
	ft_itoa.c \
	ft_printf/ft_printf.c \
	ft_printf/flags_methods.c \
	ft_printf/add_methods.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# ANSI color codes
GREEN = \033[1;32m
YELLOW = \033[1;33m
WHITE = \033[1;97m
BLUE = \033[1;34m
CYAN = \033[1;36m
RED = \033[1;31m
RESET = \033[0m

COL1 = \033[38;2;255;204;153m # Orange pastel
COL2 = \033[38;2;255;214;140m # Orange clair pastel
COL3 = \033[38;2;255;224;128m # Orange-jaune pastel
COL4 = \033[38;2;255;234;115m # Jaune-orangé pastel
COL5 = \033[38;2;255;244;102m # Jaune clair pastel
COL6 = \033[38;2;255;255;153m # Jaune pastel

INCLUDES = -Iincludes

all: INCLUDES += -Imlx_linux -Iincludes/linux_include
macos: INCLUDES += -Imlx_macos -Iincludes/macos_include

all: $(MLX_LINUX) $(NAME)
macos: $(MLX_MACOS) $(MACOS)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LINUX):
	@echo "$(BLUE)Creating the MLX library...$(RESET)"
	@make -s -C mlx_linux
$(MLX_MACOS):
	@echo "$(BLUE)Creating the MLX library...$(RESET)"
	@make -s -C mlx_macos

$(NAME): $(OBJS)
	@printf "\n$(YELLOW)Linking objects...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -I$(MLX_PATH) -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(BLUE)Progress: 100%$(RESET)"
	@printf "$(GREEN)Compilation complete!$(RESET)\n"
	@printf "\n$(COL1)███████╗ ██████╗         ██╗      ██████╗ ███╗  ██╗ ██████╗ \n"
	@printf "$(COL2)██╔════╝██╔═══██╗        ██║     ██╔═══██╗████╗ ██║██╔════╝ \n"
	@printf "$(COL3)███████╗██║   ██║        ██║     ██║   ██║██╔██╗██║██║  ███╗\n"
	@printf "$(COL4)╚════██║██║   ██║        ██║     ██║   ██║██║╚████║██║   ██║\n"
	@printf "$(COL5)███████║╚██████╔╝███████╗███████╗╚██████╔╝██║ ╚███║╚██████╔╝\n"
	@printf "$(COL6)╚══════╝ ╚═════╝ ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚══╝ ╚═════╝ $(RESET)\n\n"

$(MACOS): $(OBJS)
	@printf "\n$(YELLOW)Linking objects...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -Lmlx_macos -lmlx -framework OpenGL -framework AppKit -o $(MACOS)
	@echo "$(BLUE)Progress: 100%$(RESET)"
	@printf "$(GREEN)Compilation complete!$(RESET)\n"
	@printf "\n$(COL1)███████╗ ██████╗         ██╗      ██████╗ ███╗  ██╗ ██████╗ \n"
	@printf "$(COL2)██╔════╝██╔═══██╗        ██║     ██╔═══██╗████╗ ██║██╔════╝ \n"
	@printf "$(COL3)███████╗██║   ██║        ██║     ██║   ██║██╔██╗██║██║  ███╗\n"
	@printf "$(COL4)╚════██║██║   ██║        ██║     ██║   ██║██║╚████║██║   ██║\n"
	@printf "$(COL5)███████║╚██████╔╝███████╗███████╗╚██████╔╝██║ ╚███║╚██████╔╝\n"
	@printf "$(COL6)╚══════╝ ╚═════╝ ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚══╝ ╚═════╝ $(RESET)\n\n"

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)Cleaned object files.$(RESET)\n"

fclean: clean
	@make -s clean -C mlx_macos
	@rm -f $(NAME) $(MACOS)
	@printf "$(RED)Removed executable.$(RESET)\n"

re: fclean all

re_macos: fclean macos

.PHONY: all clean fclean re macos re_macos
