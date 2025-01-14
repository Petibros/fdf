#include "fdf.h"

void	reset_image(t_img *image)
{
	t_2_vectors	coords;

	coords.y = 0;
	while (coords.y < HEIGHT)
	{
		coords.x = 0;
		while (coords.x < LENGTH)
		{
			my_mlx_pixel_put(image, coords.x, coords.y, 0x00000000);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	my_mlx_pixel_put(t_img *data, float x, float y, int color)
{
	char	*dst;

	if (x <= LENGTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		dst = data->address + (int)(y * data->line_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	print_map(t_args *args, t_map **start)
{
	t_3_vectors	point;
	t_2_vectors	coords;
	t_map		*map;

	map = *start;
	point.y = 0;
	while (map)
	{
		point.x = 0;
		while (point.x < args->size_x)
		{
			point.z = map->row[(int)point.x];
			coords.x = (point.x * cosf((30 * 3.14) / 180) - point.y
					* cosf((30 * 3.14) / 180)) * args->scale;
			coords.y = ((point.x * sinf((30 * 3.14) / 180) + point.y
					* sinf((30 * 3.14) / 180)) - point.z) * args->scale;
			coords.x += args->x;
			coords.y += args->y;
			my_mlx_pixel_put(args->img, coords.x, coords.y, 0xFFFFFFFF);
			point.x += 1;
//			printf("%f %f\n", coords.x, coords.y);
		}
		point.y += 1;
		map = map->next;
	}
}

int	render_frame(t_args *args)
{
	reset_image(args->img);
	print_map(args, &args->map);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
        args->img->image, 0, 0);
	return (0);
}
