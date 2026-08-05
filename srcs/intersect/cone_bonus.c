/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <jinliang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:36:47 by jinliang          #+#    #+#             */
/*   Updated: 2026/08/05 23:48:01 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	hit_cone_body(t_ray ray, t_object *obj, t_hit *hit)
{
	t_quad	q;

	cone_quad(ray, obj, &q);
	if (!quad_solve(&q))
		return (0);
	q.root = quad_root1(&q);
	if (check_cone_body(ray, obj, hit, &q))
		return (1);
	q.root = quad_root2(&q);
	return (check_cone_body(ray, obj, hit, &q));
}

static int	cone_cap_hit(t_ray ray, t_object *obj, double *t, double *denom)
{
	t_vec3	cap_center;
	t_vec3	to_hit;

	cap_center = vec3_add(obj->cone.apex,
			vec3_scale(obj->cone.axis, obj->cone.height));
	*denom = vec3_dot(ray.dir, obj->cone.axis);
	if (fabs(*denom) < EPSILON)
		return (0);
	*t = vec3_dot(vec3_sub(cap_center, ray.origin), obj->cone.axis) / *denom;
	if (*t < EPSILON)
		return (0);
	to_hit = vec3_sub(ray_at(ray, *t), cap_center);
	if (vec3_dot(to_hit, to_hit) > obj->cone.radius * obj->cone.radius)
		return (0);
	return (1);
}

static int	hit_cone_cap(t_ray ray, t_object *obj, t_hit *hit)
{
	double	t;
	double	denom;

	if (!cone_cap_hit(ray, obj, &t, &denom))
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->mat = &obj->mat;
	hit->front_face = denom < 0;
	if (denom < 0)
		hit->normal = obj->cone.axis;
	else
		hit->normal = vec3_negate(obj->cone.axis);
	return (1);
}

int	intersect_cone(t_ray ray, t_object *obj, t_hit *hit)
{
	t_hit	body_hit;
	t_hit	cap_hit;
	int		got;

	got = 0;
	if (hit_cone_body(ray, obj, &body_hit))
	{
		*hit = body_hit;
		got = 1;
	}
	if (hit_cone_cap(ray, obj, &cap_hit))
	{
		if (!got || cap_hit.t < hit->t)
		{
			*hit = cap_hit;
			got = 1;
		}
	}
	return (got);
}
