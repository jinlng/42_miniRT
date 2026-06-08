#include "miniRT.h"

# define KEY_ESC 65307   /* Linux X11  */

int key_handler(int keycode, void *param)
{
    t_app *app;

    app = (t_app *)param;
    if (keycode == KEY_ESC)
    {
        mlx_destroy_image(app->mlx.ptr, app->mlx.img);
        mlx_destroy_window(app->mlx.ptr, app->mlx.win);
        exit(0);
    }
    return (0);
}

int close_handler(t_app *app)
{
    mlx_destroy_image(app->mlx.ptr, app->mlx.img);
    mlx_destroy_window(app->mlx.ptr, app->mlx.win);
    exit(0);
}