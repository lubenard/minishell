/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:39:44 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/30 14:14:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_username;
char	*g_curr_dir;

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

void	main_loop(char **env, t_env *lkd_env, char **argv)
{
	char	*command;
	char	**path;

	g_curr_dir = find_cur_dir(lkd_env);
	g_username = find_name(env);
	write_prompt(g_username, g_curr_dir);
	path = get_path(find_path(lkd_env));
	signal(SIGINT, handle_signals);
	if (argv[1] == NULL)
		get_next_line(0, &command);
	else
	{
		command = ft_strdup(argv[1]);
		ft_putendl(argv[1]);
	}
	save_command(command);
	get_command(command, path, lkd_env);
	while (ft_strcmp(command, "exit") != 0)
	{
		free(command);
		free_prompt(ft_strdup(""), g_curr_dir, path);
		path = get_path(find_path(lkd_env));
		g_curr_dir = find_cur_dir(lkd_env);
		write_prompt(g_username, g_curr_dir);
		get_next_line(0, &command);
		save_command(command);
		get_command(command, path, lkd_env);
	}
	free_prompt(g_username, g_curr_dir, path);
	free(command);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	main_loop(env, get_env(env), argv);
	return (0);
}
