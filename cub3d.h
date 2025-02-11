/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kaykin@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:44:43 by kaykin            #+#    #+#             */
/*   Updated: 2025/02/11 08:25:19 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <unistd.h> // Add this include for compatibility with WSL

typedef struct s_data
{
	int		fd;
	char	**meta_data;
	char	**map_data;
	int		offset_line_count;
	int		multiple_map_count;
	int		total_char_count;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*addr_ptr;
	int		floor_color;
	int		ceiling_color;
	int		endian;
	int		window_height;
	int		window_width;
	int		bits_per_pixel;
	int		size_line;
	int		line_count;
	int		max_line_length;
	double	pos_x;
	double	pos_y;
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
	void	*identifier[4];
	void	*text_address[4];
	int		text_height[4];
	int		text_width[4];
}	t_data;

enum	e_identifiers
{
	NO,
	EA,
	SO,
	WE,
	F,
	C
};

enum	e_directions
{
	N,
	E,
	S,
	W
};

# define PI 3.14159
# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'
# define L_ROTATE 65363
# define R_ROTATE 65361
# define ESC 65307

//hook.c
int		key_press(int key, t_data *data);
int		close_frame(t_data *data);

//parser_meta.c
void	get_element(t_data *data, char **str);
void	get_meta_data(t_data *data, int fd);
int		check_meta_data_inter(t_data *data, char **words);

//parser_map.c
void	get_map_size(t_data *data, int fd);
void	get_map_data(t_data *data, int fd);
void	map_offset(t_data *data, int fd);

//flood_fill_utils.c
int		player_pos_finder(t_data *data, char c);
void	possible_char_check(t_data *data);
int		border_check(t_data *data, int x, int y);

//flood_fill.c
void	map_control(t_data *data);

//create.c
void	create_texture(t_data *data);
void	create_window(t_data *data);
void	create_image(t_data *data);

//raycaster.c
void	raycaster(t_data *data);
void	raydir_unitize(t_data *data);
void	calculate_step(t_data *data);
void	set_wall(t_data *data);

//raycaster_utils.c
double	tex_x_coord(t_data *data);
void	put_vertical_line_to_image(t_data *data, int x,
			int drawstart, int drawend);
void	put_vertical_line(t_data *data, int x);
void	set_background(t_data *data);

//color.c
int		atoi_cub3d(t_data *data, const char *str);
void	check_rgb(t_data *data, char **word);
void	comma_check(t_data *data);
void	get_color(t_data *data);

//check.c
void	error_handler(t_data *data, char *msg);
void	check_meta_data(t_data *data);
void	extension_access_check(t_data *data, char *str);
void	xpm_check(t_data *data);
void	free_data(t_data *data);

//main_utils.c
int		all_white_space(char *str);
int		is_white_space(char c);
void	copy_line(char **map_data, char *line, int line_no);
void	replace_white_s_with_s(char *str);
void	free_words(char **words);

//Main.c
void	arg_check(t_data *data, int ac, char *av[]);
void	parser(t_data *data, char *av);
void	init(t_data *data);

#endif
