/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2024/12/18 17:31:42 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parser(void) 
{
    get_meta();
    get_map();
    map_check();
}

/*
    Argümanların kontrolü
*/

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

/*
    Error handler, mesajı yazdırıp datayı freeleyip exit atıp programı kapatıyoruz
*/

int	error_handler(t_data *data, char *msg)
{
	if (msg != NULL)
    {
        ft_putendl_fd("Error", 2);
		ft_putendl_fd(msg, 2);
    }
	free(msg);
    //freedata
    exit(1);
	//return (1);
}

/*
    Initialize
*/

void    init(t_data data)
{
    char *meta[6];
    data.meta_data = meta;
}

/*
    Bütün whitespace'leri space ile değiştiriyoruz.
*/

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

/*
    Wordslerle işimiz bitince freeliyoruz.
*/
void    free_words(char **words)
{
    int i;
    
    i = 0;
    while (words[i])
    {
        free(words[i]);
        i++;
    }
    return ;
}
/*
    Meta dataların kontrolünü yapıyoruz. 6 tane olup olmadığını ve ulaşılabilir ve
    okunabilir olup olmadığını kontrol ediyoruz.
*/

void    check_meta_data(t_data *data)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (data->meta_data[i] == NULL)
            error_handler(data, "Missing or repeated elements");
        if (access(data->meta_data[i], F_OK | R_OK) != 0)
            error_handler(data, "Non-existing or unreadable file");
        i++;
    }
    return ;
}

/*
    Split ile gelen words'leri ilkine bakıp identifier mı diye kontrol ettik.
    Oyleyse bir sonraki wordü data->meta_data'nın uygun yerine koyuyoruz.
*/
void    get_element(t_data *data, char **str)
{
    int i;

    i = 0;
    if(str[0][0] == 'N' && str[0][1] == 'O' && str[0][2] == NULL)
        data->meta_data[NO] = str[1];
    else if(str[0][0] == 'S' && str[0][1] == 'O' && str[0][2] == NULL)
        data->meta_data[SO] = str[1];
    else if(str[0][0] == 'W' && str[0][1] == 'E' && str[0][2] == NULL)
        data->meta_data[WE] = str[1];
    else if(str[0][0] == 'E' && str[0][1] == 'A' && str[0][2] == NULL)
        data->meta_data[EA] = str[1];
    else if(str[0][0] == 'F' && str[0][1] == NULL)
        data->meta_data[F] = str[1];
    else if(str[0][0] == 'C' && str[0][1] == NULL)
        data->meta_data[C] = str[1];
    if (str[2] != NULL)
        error_handler(data, "Excessive information");
}

void    parser(t_data *data, char *av)
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
        free_words(words);
    }
    if (count != 7)
        check_meta_data(data);
}

int main(int ac, char *av[])
{
    t_data  data;
    if (arg_check(ac, av))
        return (1);
    init();
    parser(&data, av[1]);
    mlx_handle();
    init_win();
    prep_map_for_rc();
    ray_casting();
    mlx_loop();

    return (0);
}
