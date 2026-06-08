#include "miniRT.h"

void    mlx_setup(t_app *app)
{
    app->mlx.ptr = mlx_init();
    if (!app->mlx.ptr)
        error_exit("mlx_init failed");
    app->mlx.win = mlx_new_window(app->mlx.ptr, WIDTH, HEIGHT, "miniRT");
    if (!app->mlx.win)
        error_exit("mlx_new_window failed");
    app->mlx.img = mlx_new_image(app->mlx.ptr, WIDTH, HEIGHT);
    if (!app->mlx.img)
        error_exit("mlx_new_image failed");
    app->mlx.addr = mlx_get_data_addr(
        app->mlx.img,
        &app->mlx.bpp,
        &app->mlx.line_len,
        &app->mlx.endian
    );
}