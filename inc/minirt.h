/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:07:24 by akozin            #+#    #+#             */
/*   Updated: 2024/07/15 17:13:58 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
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
	FLOAT_ERR,
	TYPE_ERR,
	FILE_ERR,
	FNAME_ERR,
	TOO_MUCH_ERR
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
	float		diameter;
	float		height;
}	t_obj;

typedef struct s_light
{
	t_vec3			origin;
	t_rgb			color;
	float			power;
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

int		file_probe(t_data *data, char *s);
void	parser_counter(t_data *data, int fd);

#endif
