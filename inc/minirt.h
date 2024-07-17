/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:07:24 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 15:41:27 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

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
	SPH,
	CYL,
	PLA
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
	t_light	*lights;
	int		light_n;
	t_light	amb;
	t_obj	*objs;
	int		obj_n;
	t_err	error;
	int		cam_n;
	int		amb_n;
}	t_data;

void	data_init(t_data *data);
void	allocate_stuff(t_data *data);
t_rgb	rgb_init(void);

int		file_probe(t_data *data, char *s);
void	parser_counter(t_data *data, int fd);

void	parser(t_data *data, int fd);

void	parse_amb(t_data *data, char **s);
void	parse_cam(t_data *data, char **s);

double	parse_power(t_data *data, char *s);
double	atod_res_add_logic(int *ptp, double res, char c);
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

#endif
