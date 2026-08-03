NAME     = miniRT

CC       = cc
CFLAGS   = -Wall -Wextra -Werror -ggdb

# 终端输出颜色定义
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RESET       = \033[0m

# 1. 核心定义：MLX 的目录
MLX_DIR 	= mlx_linux
MLX		= $(MLX_DIR)/libmlx.a
# MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# 2. 包含路径：让编译器既能找到你的 includes，也能找到 MLX 的头文件&libft 头文件路径
INCLUDES    = -I includes/ -I $(MLX_DIR) -I $(LIBFT_DIR)

# 3. 链接标志：-L 指定库目录，-lmlx 和 -lft 指定链接库
LIBS        = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm

SRCS     = srcs/main.c \
           srcs/math/vec3.c \
		   srcs/math/vec3_bis.c \
           srcs/math/vec3_ops.c \
		   srcs/math/quad.c \
           srcs/parser/parse_scene.c \
           srcs/parser/parse_ambient.c \
           srcs/parser/parse_camera.c \
           srcs/parser/parse_light.c \
		   srcs/parser/parse_material.c \
           srcs/parser/parse_objects.c \
           srcs/parser/parse_utils.c \
		   srcs/parser/tok_utils.c \
		   srcs/parser/parse_num.c \
		   srcs/parser/parse_objects_bis.c \
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
		   srcs/intersect/cone.c \
		   srcs/intersect/triangle.c \
           srcs/shading/lighting.c \
           srcs/shading/color.c \
		   srcs/shading/diffuse.c \
		   srcs/shading/ambient.c \
		   srcs/shading/shade.c \
		   srcs/shading/shadow.c \
		   srcs/shading/attenuation.c \
		   srcs/shading/specular.c \
		   srcs/shading/reflect.c 

OBJS     = $(SRCS:.c=.o)

all: $(NAME)

# 4. 依赖项包含 MLX、LIBFT 和 OBJS
$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@echo "🚀 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) built successfully!$(RESET)\n"

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

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "🧹 Cleaning objects..."
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean > /dev/null 2>&1 || true

fclean: clean
	@echo "🗑️ Full cleaning..."
	rm -f $(NAME) $(NAME)_debug
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean > /dev/null 2>&1 || true

re: fclean all

debug: $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -DDEBUG_SHADOW $(SRCS) $(LIBS) -o $(NAME)_debug

.PHONY: all clean fclean re debug

# # 4. 这里的改动至关重要：
# # 在链接你的 miniRT 之前，先执行 make -C 强行把 minilibx 编译出来生成 libmlx.a
# $(NAME): mlx_linux/libmlx.a $(LIBFT) $(OBJS)
# 	@echo "🎨 Compiling MiniLibX..."
# # 	@make -C $(MLX_DIR)
# 	@echo "🚀 Linking $(NAME)...
# 	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

# # 5. 当且仅当 libmlx.a 不存在时，才会触发这个规则
# $(MLX):
# 	@echo "🎨 Compiling MiniLibX..."
# 	@make -C $(MLX_DIR)

# # mlx_linux/libmlx.a:
# # 	$(MAKE) -C mlx_linux

# $(LIBFT):
# 	@printf "$(YELLOW)Compiling libft...$(RESET)\n"
# 	@make -s -C libft
# 	@printf "$(GREEN)✓ Libft ready$(RESET)\n"

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	@echo "🧹 Cleaning objects..."
# 	rm -f $(OBJS)
# # 	@make -C $(MLX_DIR) clean

# fclean: clean
# 	@echo "🗑️ Full cleaning..."
# 	rm -f $(NAME)
# # 	@make -C $(MLX_DIR) clean

# re: fclean all

# debug:
# 	$(CC) $(CFLAGS) $(INCLUDES) -DDEBUG_SHADOW $(SRCS) $(LIBS) -o $(NAME)_debug

# .PHONY: all clean fclean re