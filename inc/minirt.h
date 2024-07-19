/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:07:24 by akozin            #+#    #+#             */
/*   Updated: 2024/07/19 21:35:51 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line.h"
# include "../libs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

#define EPSILON 0.00001

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;


typedef enum e_err
{
	NULL_ERR,
	DOUBLE_ERR,
	RGB_ERR,
	ORIGIN_ERR,
	FOV_ERR,
	TYPE_ERR,
	FILE_ERR,
	FNAME_ERR,
	TOO_MANY_OBJS_ERR,
	PARAM_N_ERR,
	MALLOC_ERR
}	t_err;

typedef enum e_obj_name
{
	SP,
	PL,
	CY
}	t_obj_name;


typedef struct s_obj
{
	t_obj_name	type;
	t_vec3		origin;
	t_rgb		color;
	t_vec3		normal;
	double		diameter;
	double		height;
}	t_obj;

typedef struct s_light
{
	t_vec3			origin;
	t_rgb			color;
	double			power;
}	t_light;

typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	normal;
	int		fov;
}	t_cam;

typedef struct s_data
{
	t_cam	cam;
	int		cam_n;
	t_light	*lights;
	int		light_n;
	int		c_light;
	t_light	amb;
	int		amb_n;
	t_obj	*objs;
	int		obj_n;
	int		c_obj;
	t_err	error;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data;

void	data_init(t_data *data);
void	file_reading(t_data *data, char **av);
void	allocate_stuff(t_data *data);
void	mlx_setting_up(t_data *data);

int		key_hand(int keycode, t_data *data);
int		x_hand(t_data *data);

int		rgb_to_int(t_rgb rgb);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

int		file_probe(t_data *data, char *s);
void	parser_counter(t_data *data, int fd);

void	parser(t_data *data, int fd);

void	parse_amb(t_data *data, char **s);
void	parse_cam(t_data *data, char **s);
void	parse_lig(t_data *data, char **s);
void	parse_sp(t_data *data, char **s);
void	parse_pl(t_data *data, char **s);
void	parse_cy(t_data *data, char **s);

double	parse_power(t_data *data, char *s);
double	parse_rational_positive(t_data *data, char *s);
double	atod_res_add_logic(int *ptp, double res, char c);
t_rgb	rgb_init(void);
t_rgb	parse_rgb(t_data *data, char *s);
t_vec3	parse_origin(t_data *data, char *s);
t_vec3	parse_normal(t_data *data, char *s);
int		parse_fov(t_data *data, char *s);

void	err_exit(t_data *data, int code, int fd_to_close);
void	print_err(t_data *data);
void	print_usage(char *s);

void	free_str_arr(char ***s);
void	free_all(t_data *data);

int		str_arr_counter(char **s);

double	vec_len(t_vec3 vec);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vect_add(t_vec3 a, t_vec3 b);
t_vec3	prod_esc(t_vec3 v, double f);
void	normalize(t_vec3 *v);
double	dot_prod(t_vec3 v1, t_vec3 v2);
t_vec3	cross_prod(t_vec3 u, t_vec3 v);
double	distance(t_vec3 a, t_vec3 b);
t_vec3	vect_inv(t_vec3 v);
void	print_vector(t_vec3 v);

double	splane_ray(t_vec3 o, t_vec3 d, t_vec3 pp, t_vec3 n);

void	test_drawing_lol(t_data *data);

#endif
