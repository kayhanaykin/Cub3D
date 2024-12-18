/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2024/12/18 16:02:34 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parser(void) 
{
    get_meta();
    get_map();
    map_check();
}

int arg_check(int ac, char *av[])
{
    int len;
    
    if (ac != 2)
        return(error_handler(NULL, "Wrong number of arguments"));
    len = ft_strlen(av[1]);
    if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' 
        || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
        return(error_handler(NULL, "Wrong extension"));
    return (0);
}

int	error_handler(t_data data, char *msg)
{
	if (msg != NULL)
		ft_putendl_fd(msg, 2);
	free(msg);
	return (1);
}

void    init(t_data data)
{
    char *meta[6];
    data.meta_data = meta;
}

void    replace_white_s_with_s(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\f' ||str[i] == '\r' 
            || str[i] == '\v' || str[i] == '\t')
            str[i] == ' ';
        i++;
    }
    return ;
}

void    parser(t_data data, char *av)
{
    int     fd;
    int     count;
    char    *line;
    char    **words;
    
    fd = open(av, O_RDONLY);
    count = 0;
    while (count < 7)
    {
        line = get_next_line(fd);
        replace_white_s_with_s(line);
        words = ft_split(line, ' ');
        if (words[0] == NULL)
            continue ;
        get_element(data, words);
        count++;
    }   
}

void    get_element(t_data data, char **str)
{
    int i;

    i = 0;
    if(str[0][0] == 'S' && str[0][1] == 'O' && str[0][2] == NULL)
        
}

int main(int ac, char *av[])
{
    t_data  data;
    if (arg_check(ac, av))
        return (1);
    init();
    parser(data, av[1]);
    mlx_handle();
    init_win();
    prep_map_for_rc();
    ray_casting();
    mlx_loop();

    return (0);
}
