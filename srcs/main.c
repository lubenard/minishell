/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:39:44 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/29 23:54:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*username;
char	*curr_dir;

void	free_prompt(char *username, char *curr_dir, char **path)
{
	int		i;

	i = 0;
	free(username);
	free(curr_dir);
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
}

void	write_prompt(char *username, char *curr_dir)
{
	ft_putstr("\033[31m");
	ft_putstr(username);
	ft_putstr("\033[0m - \033[36m");
	ft_putstr(curr_dir);
	ft_putstr("\033[0m >  ");
}

void	main_loop(char **env, t_env *lkd_env, char *ext_command)
{
	char	*command;
	char	**path;

	curr_dir = find_cur_dir(lkd_env);
	username = find_name(env);
	write_prompt(username, curr_dir);
	path = get_path(find_path(lkd_env));
	signal(SIGINT, handle_signals);
	if (ext_command == NULL)
		get_next_line(0, &command);
	else
	{
		command = ft_strdup(ext_command);
		ft_putendl(ext_command);
	}
	get_command(command, path, lkd_env);
	while (ft_strcmp(command, "exit") != 0)
	{
		free(command);
		free_prompt(ft_strdup(""), curr_dir, path);
		path = get_path(find_path(lkd_env));
		curr_dir = find_cur_dir(lkd_env);
		write_prompt(username, curr_dir);
		get_next_line(0, &command);
		get_command(command, path, lkd_env);
	}
	free_prompt(username, curr_dir, path);
	free(command);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	main_loop(env, get_env(env), argv[1]);
	return (0);
}
