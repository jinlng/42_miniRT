#include "miniRT.h"

t_color color_scale(t_color c, double t)
{
    return ((t_color){
        (int)(c.r * t),
        (int)(c.g * t),
        (int)(c.b * t)
    });
}

t_color color_add(t_color a, t_color b)
{
    return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

/* multiply two colors component-wise, normalized by 255 */
t_color color_multiply(t_color a, t_color b)
{
    return ((t_color){
        (int)(a.r * b.r / 255.0),
        (int)(a.g * b.g / 255.0),
        (int)(a.b * b.b / 255.0)
    });
}

t_color color_clamp(t_color c)
{
    t_color out;

    out.r = c.r < 0 ? 0 : c.r > 255 ? 255 : c.r;
    out.g = c.g < 0 ? 0 : c.g > 255 ? 255 : c.g;
    out.b = c.b < 0 ? 0 : c.b > 255 ? 255 : c.b;
    return (out);
}