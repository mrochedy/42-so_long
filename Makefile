NAME = so_long

MLX_LINUX = mlx_linux/libmlx.a
MLX_MACOS = mlx_macos/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iincludes

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    INCLUDES += -Imlx_linux -Iincludes/linux_include
    LDFLAGS = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
    MLX = $(MLX_LINUX)
else ifeq ($(UNAME_S), Darwin)
    INCLUDES += -Imlx_macos -Iincludes/macos_include
    LDFLAGS = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
    MLX = $(MLX_MACOS)
else
    $(error Operating system not supported)
endif

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

all: $(MLX) $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LINUX):
	@echo "$(BLUE)Creating the MLX library...$(RESET)"
	@make -s -C mlx_linux
$(MLX_MACOS):
	@echo "$(BLUE)Creating the MLX library...$(RESET)"
	@make -s -C mlx_macos

$(NAME): $(OBJS)
	@echo "\n$(YELLOW)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(BLUE)Progress: 100%$(RESET)"
	@echo "$(GREEN)Compilation complete!$(RESET)\n"
	@echo "$(COL1)███████╗ ██████╗         ██╗      ██████╗ ███╗  ██╗ ██████╗ "
	@echo "$(COL2)██╔════╝██╔═══██╗        ██║     ██╔═══██╗████╗ ██║██╔════╝ "
	@echo "$(COL3)███████╗██║   ██║        ██║     ██║   ██║██╔██╗██║██║  ███╗"
	@echo "$(COL4)╚════██║██║   ██║        ██║     ██║   ██║██║╚████║██║   ██║"
	@echo "$(COL5)███████║╚██████╔╝███████╗███████╗╚██████╔╝██║ ╚███║╚██████╔╝"
	@echo "$(COL6)╚══════╝ ╚═════╝ ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚══╝ ╚═════╝ $(RESET)\n"

clean:
	@make -s clean -C mlx_linux
	@make -s clean -C mlx_macos
	@echo "$(RED)Cleaned the MLX library.$(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Removed executable.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
