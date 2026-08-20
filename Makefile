NAME        = miniRT
BONUS_NAME  = miniRT_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -ggdb

# 终端输出颜色定义
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RESET       = \033[0m

# 1. 核心定义：MLX 的目录
MLX_DIR 	= mlx_linux
MLX		= $(MLX_DIR)/libmlx.a
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# 2. 包含路径：让编译器既能找到你的 includes，也能找到 MLX 的头文件&libft 头文件路径
INCLUDES    = -I includes/ -I $(MLX_DIR) -I $(LIBFT_DIR)

# 3. 链接标志：-L 指定库目录，-lmlx 和 -lft 指定链接库
LIBS        = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm

# 4. 两个构建共用的源文件
COMMON_SRCS = srcs/main.c \
              srcs/math/vec3.c \
              srcs/math/vec3_bis.c \
              srcs/math/vec3_ops.c \
              srcs/math/quad.c \
              srcs/parser/parse_scene.c \
              srcs/parser/parse_ambient.c \
              srcs/parser/parse_camera.c \
              srcs/parser/material.c \
              srcs/parser/parse_objects.c \
              srcs/parser/parse_utils.c \
              srcs/parser/tok_utils.c \
              srcs/parser/parse_num.c \
              srcs/parser/parse_num2.c \
              srcs/parser/free_scene.c \
              srcs/window/mlx_init.c \
              srcs/window/mlx_hooks.c \
              srcs/window/mlx_utils.c \
              srcs/render/camera.c \
              srcs/render/render.c \
              srcs/render/translation.c \
              srcs/intersect/intersect.c \
              srcs/intersect/sphere.c \
              srcs/intersect/plane.c \
              srcs/intersect/cylinder.c \
              srcs/intersect/cylinder_utils.c \
              srcs/shading/color.c \
              srcs/shading/diffuse.c \
              srcs/shading/ambient.c \
              srcs/shading/shadow.c \
              srcs/shading/attenuation.c

# 5. partie obligatoire seulement, sphère plan cylindre, ambiant et diffus
MAND_SRCS   = srcs/parser/dispatch.c \
              srcs/parser/parse_opts.c \
              srcs/parser/parse_light.c \
              srcs/intersect/hit_object.c \
              srcs/shading/shade.c

# 6. bonus seulement, cône triangle spéculaire matériaux et lumières multiples
BONUS_SRCS  = srcs/parser/dispatch_bonus.c \
              srcs/parser/parse_opts_bonus.c \
              srcs/parser/parse_light_bonus.c \
              srcs/parser/parse_objects_bonus.c \
              srcs/intersect/hit_object_bonus.c \
              srcs/intersect/cone_bonus.c \
              srcs/intersect/cone_utils_bonus.c \
              srcs/intersect/triangle_bonus.c \
              srcs/shading/shade_bonus.c \
              srcs/shading/specular_bonus.c \
              srcs/shading/checker_bonus.c

COMMON_OBJS = $(COMMON_SRCS:.c=.o)
MAND_OBJS   = $(MAND_SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

HEADERS     = includes/miniRT.h includes/miniRT_bonus.h

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(MLX) $(LIBFT) $(COMMON_OBJS) $(MAND_OBJS)
	@echo "🚀 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(MAND_OBJS) $(LIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) built successfully!$(RESET)\n"

$(BONUS_NAME): $(MLX) $(LIBFT) $(COMMON_OBJS) $(BONUS_OBJS)
	@echo "🚀 Linking $(BONUS_NAME)..."
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
	@printf "$(GREEN)✓ $(BONUS_NAME) built successfully!$(RESET)\n"

# 编译 MiniLibX
$(MLX):
	@echo "$(YELLOW)🎨 Compiling MiniLibX...$(RESET)\n"
	@make -sC $(MLX_DIR)
	@printf "$(GREEN)✓ MLX ready$(RESET)\n"

# 编译 Libft
$(LIBFT):
	@printf "$(YELLOW)Compiling libft...$(RESET)\n"
	@make -sC $(LIBFT_DIR)
	@printf "$(GREEN)✓ Libft ready$(RESET)\n"

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "🧹 Cleaning objects..."
	rm -f $(COMMON_OBJS) $(MAND_OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean > /dev/null 2>&1 || true

fclean: clean
	@echo "🗑️ Full cleaning..."
	rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean > /dev/null 2>&1 || true

re: fclean all

.PHONY: all bonus clean fclean re
