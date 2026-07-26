/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:24:07 by jinliang          #+#    #+#             */
/*   Updated: 2026/07/16 15:21:43 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*  Cast a ray from the hit surface toward the light.
>> Return 1 if something blocks it before it reaches the light.

	Two bias terms:
-   normal bias: pushes origin off the surface to avoid self-hit
-   ray-dir bias: handles grazing angles where normal bias alone fails*/
// static int  in_shadow(t_scene *scene, t_vec3 hit_point,
//                         t_vec3 normal, t_light *light)
// {
//     t_ray   shadow_ray;
//     t_hit   tmp;
//     t_vec3  to_light;
//     double  light_dist;

//     to_light       = vec3_sub(light->pos, hit_point);
//     light_dist     = vec3_len(to_light);
//     shadow_ray.dir = vec3_norm(to_light);
//     shadow_ray.origin = vec3_add(hit_point,
//                             vec3_add(
//                                 vec3_scale(normal, EPSILON * 100),
//                                 vec3_scale(shadow_ray.dir, EPSILON * 100)
//                             ));
//     if (intersect_scene(shadow_ray, scene, &tmp))
//         return (tmp.t < light_dist - EPSILON * 100);
//     return (0);
// }
