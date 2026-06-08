#include "miniRT.h"

// static void print_scene(t_scene *scene)
// {
//     t_object    *obj;
//     t_light     *light;

//     printf("=== Scene parsed OK ===\n");
//     printf("Ambient: ratio=%.2f color=(%d,%d,%d)\n",
//         scene->ambient.ratio,
//         scene->ambient.color.r,
//         scene->ambient.color.g,
//         scene->ambient.color.b);
//     printf("Camera:  pos=(%.1f,%.1f,%.1f) dir=(%.2f,%.2f,%.2f) fov=%.0f\n",
//         scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z,
//         scene->camera.dir.x, scene->camera.dir.y, scene->camera.dir.z,
//         scene->camera.fov);
//     light = scene->lights;
//     while (light)
//     {
//         printf("Light:   pos=(%.1f,%.1f,%.1f) brightness=%.2f\n",
//             light->pos.x, light->pos.y, light->pos.z, light->brightness);
//         light = light->next;
//     }
//     obj = scene->objects;
//     while (obj)
//     {
//         if (obj->type == OBJ_SPHERE)
//             printf("Sphere:  center=(%.1f,%.1f,%.1f) radius=%.2f\n",
//                 obj->sphere.center.x, obj->sphere.center.y,
//                 obj->sphere.center.z, obj->sphere.radius);
//         else if (obj->type == OBJ_PLANE)
//             printf("Plane:   point=(%.1f,%.1f,%.1f) normal=(%.2f,%.2f,%.2f)\n",
//                 obj->plane.point.x, obj->plane.point.y, obj->plane.point.z,
//                 obj->plane.normal.x, obj->plane.normal.y, obj->plane.normal.z);
//         else if (obj->type == OBJ_CYLINDER)
//             printf("Cylinder:center=(%.1f,%.1f,%.1f) r=%.2f h=%.2f\n",
//                 obj->cylinder.center.x, obj->cylinder.center.y,
//                 obj->cylinder.center.z,
//                 obj->cylinder.radius, obj->cylinder.height);
//         obj = obj->next;
//     }
// }

// int main(int argc, char **argv)
// {
//     t_scene scene;

//     if (argc != 2)
//     {
//         write(2, "Usage: ./miniRT <scene.rt>\n", 27);
//         return (1);
//     }
//     parse_scene(argv[1], &scene);
//     print_scene(&scene);
//     return (0);
// }
// int main(int argc, char **argv)
// {
//     t_app   app;

//     if (argc != 2)
//     {
//         write(2, "Usage: ./miniRT <scene.rt>\n", 27);
//         return (1);
//     }
//     parse_scene(argv[1], &app.scene);
//     mlx_setup(&app);
//     render_test(&app);
//     mlx_hook(app.mlx.win, 2, 1L << 0, (int (*)())(void *)key_handler, &app);
//     mlx_hook(app.mlx.win, 17, 0, close_handler, &app);
//     mlx_loop(app.mlx.ptr);
//     return (0);
// }

#include "miniRT.h"

int main(int argc, char **argv)
{
    t_app   app;

    if (argc != 2)
    {
        write(2, "Usage: ./miniRT <scene.rt>\n", 27);
        return (1);
    }
    parse_scene(argv[1], &app.scene);
    mlx_setup(&app);
    render(&app);
    mlx_hook(app.mlx.win, 2, 1L << 0, (int (*)())(void *)key_handler, &app);
    mlx_hook(app.mlx.win, 17, 0, (int (*)())(void *)close_handler, &app);
    mlx_loop(app.mlx.ptr);
    return (0);
}