/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:44:43 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/31 14:59:43 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h> // printf
#include <stdlib.h> //malloc-exit
#include <stddef.h> //NULL
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <fcntl.h>

typedef struct s_data
{
    char    **meta_data;
    char    **map_data;
    int     offset_line_count;
	int		multiple_map_count; //double map var mı kontrolü, playerın olduğu mapin karakter sayısı
    int		total_char_count; // whitespace olmayan karakter sayısı text dosyasında
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*addr_ptr;
	int		floor_color;
	int		ceiling_color;
    int		endian;
    int		window_height;
	int		window_width;
    int		bits_per_pixel; //32
	int		size_line;
    int     line_count;
    int     max_line_length;
    double  pos_x;
    double  pos_y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	time;
	double	oldtime;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;	
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		sidecolor[4];
	int		mapx;
	int		mapy;
} t_data;

enum	identifiers
{
    NO,
    SO,
    WE,
    EA,
    F,
    C
};

enum	directions
{
	N,
	E,
	S,
	W
};

# define PI 3.14159
# define UP 119
# define DOWN 97
# define LEFT 115
# define RIGHT 100
# define L_ROTATE 65363
# define R_ROTATE 65361
# define ESC 27

void	create_window(t_data *data);
void	create_image(t_data *data);
void	set_background(t_data *data);
int		close_frame(t_data *data);
int		error_handler(t_data *data, char *msg);
int		key_press(int key, t_data *data);
void	calculate_step(t_data *data);
void	put_vertical_line_to_image(t_data *data, int x, int drawstart, int drawend);
void	put_vertical_line(t_data *data, int x);
void	set_wall(t_data *data);
void 	set_background(t_data *data);
void	raycaster(t_data *data);

#endif