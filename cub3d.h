/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:44:43 by kaykin            #+#    #+#             */
/*   Updated: 2024/12/18 12:08:04 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    char    **meta_data;
    int     **map_data;
    void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*addr_ptr;
    int		endian; //
    int		window_height;
	int		window_width;
    int     pos_x;      // float olabilir
    int     pos_y;      // float olabilir
    float   pos_angle;
    int		bits_per_pixel; //32
	int		size_line;
} t_data;


#endif