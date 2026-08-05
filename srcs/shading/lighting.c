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
- normal bias: pushes origin off the surface to avoid self-hit
-   ray-dir bias: handles grazing angles where normal bias alone fails*/
// static int  in_shadow(t_scene *scene, t_vec3 hit_point,
//                         t_vec3 normal, t_light *light)
// {
