/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:39:44 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/15 23:25:28 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt(char *cur_name, char *cur_dir, char **path)
{
	int		i;

	i = 0;
	free(cur_name);
	free(cur_dir);
	while (path[i][0] != '\0')
		free(path[i++]);
	free(path);
}

void	write_prompt(char *cur_name, char *cur_dir)
{
	ft_putstr("\033[31m");
	ft_putstr(cur_name);
	ft_putstr("\033[0m - \033[36m");
	ft_putstr(cur_dir);
	ft_putstr("\033[0m >  ");
}

void	main_loop(char **env, t_env *lkd_env)
{
	char	*cur_name;
	char	*cur_dir;
	char	*command;
	char	**path;

	cur_dir = ft_strsub(env[8], 4, 857); //Linux
	//cur_dir = ft_strsub(env[7], 4, 857); //MacOs
	cur_name = ft_strsub(env[22], 5, 50); //Linux
	//cur_name = ft_strsub(env[16], 5, 50); //MacOs
	write_prompt(cur_name, cur_dir);
	path = get_path(env[36]); //Linux
	//path = get_path(env[12]); //MacOs
	get_next_line(0, &command);
	get_command(command, path, lkd_env, env);
	while (ft_strcmp(command, "exit") != 0)
	{
		free(command);
		write_prompt(cur_name, cur_dir);
		free(cur_dir);
		cur_dir = ft_strsub(env[7], 4, 857);
		get_next_line(0, &command);
		get_command(command, path, lkd_env, env);
	}
	free_prompt(cur_name, cur_dir, path);
	free(command);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	main_loop(env, get_env(env));
	return (0);
}
