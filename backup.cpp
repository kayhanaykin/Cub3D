double tex_x_coord(t_data *data)
{
    double	wallx;
    int		tex_x;
    if (data->side == E || data->side == W) 
	  	wallx = data->pos_y + data->perpwalldist * data->raydiry;
    else           
	  	wallx = data->pos_x + data->perpwalldist * data->raydirx;
	
    wallx -= (int)wallx;
	tex_x = (int)(wallx * (double)(data->text_width[data->side]));

    if ((data->side == E || data->side == W) && data->raydirx > 0)
		tex_x = data->text_width[data->side] - tex_x - 1;
    if ((data->side == N || data->side == S) && data->raydiry < 0)
		tex_x = data->text_width[data->side] - tex_x - 1;
}



void	put_vertical_line_to_image(t_data *data, int x, int drawstart, int drawend)
{
	char	*dst;
	double	wall_height;
	double	y_ratio;
	double  x_ratio;
	int		tex_x;
	int 	i;
	
	tex_x = tex_x_coord(data);
	i = 0;
	wall_height = drawend - drawstart;
	y_ratio = wall_height / (double) data->text_height[data->side];
	x_ratio = (double) data->window_width / (double) data->text_width[data->side];
	while (i < drawend - drawstart)
	{
		dst = data->addr_ptr + (drawstart + i) * data->size_line + (x * 4);

		
		*(int *) dst = *(int *)(data->text_address[data->side] + ((int)((double)(i) / y_ratio) * //y yonü
		 data->text_width[data->side] * 4) 
		 
		 + (tex_x * 4)); //x yonü		
		i++;
	}
}