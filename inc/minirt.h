/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:07:24 by akozin            #+#    #+#             */
/*   Updated: 2024/07/29 15:38:24 by akozin           ###   ########.fr       */
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

# define EPSILON 0.00001
//# define WIN_Y 1080.f
//# define WIN_X 1920.f
//# define WIN_Y 270.f
//# define WIN_X 480.f
//# define WIN_Y 540.f
//# define WIN_X 960.f
# define WIN_Y 1000.f
# define WIN_X 1000.f
//# define WIN_X 50.f
//# define WIN_Y 50.f
# define FALLOFF 1.3f

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

typedef struct s_ur
{
	t_vec3	u;
	t_vec3	r;
}	t_ur;

/*
 * p - col point
 */
typedef struct s_col
{
	int		obj_ind;
	double	r_dist;
	t_vec3	p;
}	t_col;

/*
 * origin  = o
 * forward = f
 */
typedef struct s_ray
{
	t_vec3	o;
	t_vec3	f;
}	t_ray;

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
	NORMAL_ERR,
	RGB_ERR,
	ORIGIN_ERR,
	FOV_ERR,
	TYPE_ERR,
	FILE_ERR,
	FNAME_ERR,
	TOO_MANY_OBJS_ERR,
	NO_CAM_ERR,
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
	double	fov;
}	t_cam;

/*
 * curr_c really comes in with a clutch when
 * we have to squeeze some parameters into an aux function
 * because norminette is not a normal person
 */
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
	t_col	curr_c;
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
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double f);
void	normalize(t_vec3 *v);
double	dot_prod(t_vec3 v1, t_vec3 v2);
t_vec3	cross_prod(t_vec3 u, t_vec3 v);
double	distance(t_vec3 a, t_vec3 b);
t_vec3	vec_inv(t_vec3 v);
void	print_vector(t_vec3 v);

double	plane_ray(t_vec3 o, t_vec3 d, t_vec3 pp, t_vec3 n);
double	sphere_intersection(t_vec3 o, t_vec3 d, t_obj *obj);
double	sphere_far_result(t_vec3 o, t_vec3 d, t_obj *obj);
t_vec3	sphere_n(t_obj sp, t_vec3 p);
double	cylinder_intersection(const t_ray cam, const t_obj obj);

void	draw(t_data *data);
t_vec3	find_f(t_data *data, int px, int py, t_ur ur);
t_ur	set_up_right(t_data *data, t_ur ur);
t_col	check_objs_internal(t_vec3 f, t_data *data, int i, t_col res);
t_col	check_os_from_int_p(t_ray l, t_data *data, int i, t_col res);

t_rgb	light_calc(t_data *data, t_col col, t_vec3 f);
void	light_calc_init(t_data *data, t_col *col, t_vec3 f, t_rgb *ret);
int		ignore_light(t_data *data, int *j);
double	sc_fac_calc_sp(t_data *data, t_col col, t_ray r_light);
int		light_blocked(t_data *data, t_ray r_light, int *j, double *dist_l);
t_rgb	super_mix(t_rgb ret, t_rgb additive, double scale_factor, t_rgb o_rgb);

t_rgb	rgb_add(t_rgb c1, t_rgb c2);
t_rgb	rgb_mult(t_rgb c1, t_rgb c2);
t_rgb	rgb_clamp(t_rgb c);
t_rgb	rgb_scale(t_rgb c, double j);


#endif
