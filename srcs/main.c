/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:39:44 by lubenard          #+#    #+#             */
/*   Updated: 2019/03/11 16:21:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt(char *cur_name, char *cur_dir, char *command)
{
	free(command);
	free(cur_name);
	free(cur_dir);
}

void	write_prompt(char *cur_name, char *cur_dir)
{
	ft_putstr("\033[31m");
	ft_putstr(cur_name);
	ft_putstr("\033[0m - \033[36m");
	ft_putstr(cur_dir);
	ft_putstr("\033[0m > ");
}

inline static void		main_loop(char **env)
{
	char	*cur_name;
	char	*cur_dir;
	char	*command;

	//cur_dir = ft_strsub(env[8], 4, 4092);
	cur_dir = ft_strsub(env[7], 4, 857);
	//cur_name = ft_strsub(env[22], 5, 4091);
	cur_name = ft_strsub(env[16], 5, 50);
	write_prompt(cur_name, cur_dir);
	get_next_line(0, &command);
	get_command(command);
	while (ft_strcmp(command, "exit") != 0)
	{
		free_prompt(cur_name, cur_dir, command);
		cur_dir = ft_strsub(env[8], 4, 50);
		cur_name = ft_strsub(env[22], 4, 30);
		write_prompt(cur_name, cur_dir);
		get_next_line(0, &command);
		get_command(command);
	}
	free_prompt(cur_name, cur_dir, command);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	main_loop(env);
	return (0);
}
