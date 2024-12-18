/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:44 by kaykin            #+#    #+#             */
/*   Updated: 2024/12/18 12:31:43 by kaykin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
    {
        write(2, "Wrong number of arguments", 25);
        return (1);
    }
    len = ft_strlen(av[1]);
    if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' 
        || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
    (
        write(2, "Wrong extension", 15);
        return (1);
    )
    return (0);
}

int	error_handler(t_data *data, char *msg)
{
	if (msg != NULL)
		ft_putendl_fd(msg, 2);
	free(msg);
	return (1);
}


int main(int ac, char *av[])
{
    if (arg_check(ac, av))
        return (1);
    init();
    parser();
    mlx_handle();
    init_win();
    prep_map_for_rc();
    ray_casting();
    mlx_loop();

    return (0);
}
