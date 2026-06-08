#include "miniRT.h"

/*
** Full shading will grow here in step 6 (diffuse + shadows).
** For now: ambient only so we can see the sphere shape.
**
** ambient = object_color * ambient_ratio * ambient_color / 255
*/
t_color shade(t_hit *hit, t_scene *scene, t_ray ray)
{
    t_color ambient;

    (void)ray;
    ambient = color_multiply(hit->color, scene->ambient.color);
    ambient = color_scale(ambient, scene->ambient.ratio);
    return (color_clamp(ambient));
}