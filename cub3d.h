/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:44:43 by kaykin            #+#    #+#             */
/*   Updated: 2025/01/29 11:41:25 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h> // printf
#include <stdlib.h> //malloc-exit
#include <stddef.h> //NULL
#include "libft.h"
#include <fcntl.h>

typedef struct s_data
{
    char    **meta_data;
    char    **map_data;
	char	**second_map_data;
	int		multiple_map_count; //double map var mı kontrolü, playerın olduğu mapin karakter sayısı
    int		total_char_count; // whitespace olmayan karakter sayısı text dosyasında
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*addr_ptr;
    int		endian; //
    int		window_height;
    int		bits_per_pixel; //32
	int		window_width;
	int		size_line;
    int     line_count;
    int     max_line_length;
    float   pos_angle;
    int     pos_x;      // float olabilir
    int     pos_y;      // float olabilir
} t_data;

enum Identifiers
{
    NO,
    SO,
    WE,
    EA,
    F,
    C
};

#endif