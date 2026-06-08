// #include "miniRT.h"

// /*
// ** Walk the object list, find the closest hit.
// ** Returns 1 if anything was hit, 0 otherwise.
// ** closest.t starts at infinity so every real hit beats it.
// */
// int intersect_scene(t_ray ray, t_scene *scene, t_hit *hit)
// {
//     t_object    *obj;
//     t_hit       tmp;
//     int         hit_anything;
//     double      closest;

//     hit_anything = 0;
//     closest      = 1e15;
//     obj          = scene->objects;
//     while (obj)
//     {
//         tmp.t = closest;
//         if (obj->type == OBJ_SPHERE && intersect_sphere(ray, obj, &tmp))
//         {
//             if (tmp.t < closest)
//             {
//                 closest      = tmp.t;
//                 *hit         = tmp;
//                 hit_anything = 1;
//             }
//         }
//         /* OBJ_PLANE and OBJ_CYLINDER cases added in steps 7 & 8 */
//         obj = obj->next;
//     }
//     return (hit_anything);
// }

#include "miniRT.h"

int intersect_scene(t_ray ray, t_scene *scene, t_hit *hit)
{
    t_object    *obj;
    t_hit       tmp;
    int         hit_anything;
    double      closest;

    hit_anything = 0;
    closest      = 1e15;
    obj          = scene->objects;
    while (obj)
    {
        tmp.t = closest;
        if (obj->type == OBJ_SPHERE && intersect_sphere(ray, obj, &tmp))
        {
            if (tmp.t < closest)
            {
                closest      = tmp.t;
                *hit         = tmp;
                hit_anything = 1;
            }
        }
        else if (obj->type == OBJ_PLANE && intersect_plane(ray, obj, &tmp))
        {
            if (tmp.t < closest)
            {
                closest      = tmp.t;
                *hit         = tmp;
                hit_anything = 1;
            }
        }
        else if (obj->type == OBJ_CYLINDER
            && intersect_cylinder(ray, obj, &tmp))
        {
            if (tmp.t < closest)
            {
                closest      = tmp.t;
                *hit         = tmp;
                hit_anything = 1;
            }
        }

        obj = obj->next;

    }
    return (hit_anything);
}