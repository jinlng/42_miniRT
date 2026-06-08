#include "miniRT.h"

/*
** Write one pixel into the image buffer.
** Never call mlx_pixel_put — it's extremely slow (one syscall per pixel).
** We write into the raw buffer and flush once per frame instead.
*/
void    mlx_put_pixel(t_mlx *mlx, int x, int y, t_color color)
{
    char    *dst;
    int     argb;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    argb = (color.r << 16) | (color.g << 8) | color.b;
    dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
    *(unsigned int *)dst = argb;
}

/*
** Temporary: fill the window with a gradient so we can see the buffer works.
** You will replace this with your real render call in step 4.
*/
void    render_test(t_app *app)
{
    int     x;
    int     y;
    t_color color;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            color.r = (int)(255.0 * x / WIDTH);
            color.g = (int)(255.0 * y / HEIGHT);
            color.b = 128;
            mlx_put_pixel(&app->mlx, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(app->mlx.ptr, app->mlx.win, app->mlx.img, 0, 0);
}