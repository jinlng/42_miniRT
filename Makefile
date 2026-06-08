NAME     = miniRT

CC       = cc
CFLAGS   = -Wall -Wextra -Werror -ggdb

# 1. 核心定义：MLX 的目录
MLX_DIR 	= mlx_linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# 2. 包含路径：让编译器既能找到你的 includes，也能找到 MLX 的头文件
INCLUDES = -I includes/ -I $(MLX_DIR)

# 3. 链接标志：告诉链接器去哪里找 libmlx.a，以及 Linux 必需的 X11 库
# 注意：库的链接顺序不能乱，-lm 和 X11 库必须在后面
# LIBS     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS     = srcs/main.c \
           srcs/math/vec3.c \
           srcs/math/vec3_ops.c \
           srcs/parser/parse_scene.c \
           srcs/parser/parse_ambient.c \
           srcs/parser/parse_camera.c \
           srcs/parser/parse_light.c \
           srcs/parser/parse_objects.c \
           srcs/parser/parse_utils.c \
		   srcs/window/mlx_init.c \
           srcs/window/mlx_hooks.c \
           srcs/window/mlx_utils.c \
		   srcs/render/camera.c \
           srcs/render/render.c \
           srcs/intersect/intersect.c \
           srcs/intersect/intersect_sphere.c \
		   srcs/intersect/intersect_plane.c \
		   srcs/intersect/intersect_cylinder.c \
           srcs/shading/lighting.c \
           srcs/shading/color.c

OBJS     = $(SRCS:.c=.o)

all: $(NAME)

# 4. 这里的改动至关重要：
# 在链接你的 miniRT 之前，先执行 make -C 强行把 minilibx 编译出来生成 libmlx.a
$(NAME): mlx_linux/libmlx.a $(OBJS)
	@echo "🎨 Compiling MiniLibX..."
	@make -C $(MLX_DIR)
	@echo "🚀 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

mlx_linux/libmlx.a:
	$(MAKE) -C mlx_linux

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "🧹 Cleaning objects..."
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "🗑️ Full cleaning..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re