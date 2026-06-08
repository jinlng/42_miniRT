// #include "miniRT.h"

// /*
// ** Temporary ray color: visualize direction as RGB.
// ** dir is normalized so components are in [-1,1].
// ** Map to [0,255] so we can see the gradient.
// ** Replace this entirely in step 5 when intersection arrives.
// */
// t_color ray_color(t_ray ray)
// {
//     t_color color;

//     color.r = (int)((ray.dir.x + 1.0) * 0.5 * 255.99);
//     color.g = (int)((ray.dir.y + 1.0) * 0.5 * 255.99);
//     color.b = (int)((ray.dir.z + 1.0) * 0.5 * 255.99);
//     return (color);
// }

// /*
// ** Main pixel loop.
// ** u goes left→right, v goes top→bottom (we invert v for viewport coords).
// */
// void    render(t_app *app)
// {
//     t_camera_basis  basis;
//     t_ray           ray;
//     t_color         color;
//     double          u;
//     double          v;
//     int             x;
//     int             y;

//     basis = build_camera_basis(&app->scene.camera);
//     y = 0;
//     while (y < HEIGHT)
//     {
//         x = 0;
//         while (x < WIDTH)
//         {
//             /* center of pixel, v flipped so y=0 is top */
//             u = (x + 0.5) / (double)WIDTH;
//             v = 1.0 - (y + 0.5) / (double)HEIGHT;
//             ray = get_ray(&basis, u, v);
//             color = ray_color(ray);
//             mlx_put_pixel(&app->mlx, x, y, color);
//             x++;
//         }
//         y++;
//     }
//     mlx_put_image_to_window(app->mlx.ptr, app->mlx.win, app->mlx.img, 0, 0);
// }

#include "miniRT.h"

/*
** Background: simple sky gradient when no object is hit.
** Lerp white→blue based on ray vertical direction.
*/
static t_color background(t_ray ray)
{
    double  t;
    t_color white;
    t_color blue;

    white = (t_color){255, 255, 255};
    blue  = (t_color){128, 178, 255};
    t = (ray.dir.y + 1.0) * 0.5;
    return (color_clamp(color_add(
        color_scale(white, 1.0 - t),
        color_scale(blue, t)
    )));
}

t_color ray_color(t_ray ray, t_scene *scene)
{
    t_hit   hit;

    if (intersect_scene(ray, scene, &hit))
        return (shade(&hit, scene, ray));
    return (background(ray));
}

void    render(t_app *app)
{
    t_camera_basis  basis;
    t_ray           ray;
    t_color         color;
    double          u;
    double          v;
    int             x;
    int             y;

    basis = build_camera_basis(&app->scene.camera);
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            u = (x + 0.5) / (double)WIDTH;
            v = 1.0 - (y + 0.5) / (double)HEIGHT;
            ray = get_ray(&basis, u, v);
            color = ray_color(ray, &app->scene);
            mlx_put_pixel(&app->mlx, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(app->mlx.ptr, app->mlx.win, app->mlx.img, 0, 0);
}