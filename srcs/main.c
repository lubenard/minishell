/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:39:44 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/09 16:32:34 by lubenard         ###   ########.fr       */
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

int		exec_loop(t_env *lkd_env, char **get_curr_path,
	char ***path, char **command)
{
	free(*command);
	free_prompt(ft_strdup(""), g_curr_dir, *path);
	*path = get_path(find_path(lkd_env));
	g_curr_dir = find_cur_dir(lkd_env);
	write_prompt(g_username, g_curr_dir);
	signal(SIGINT, handle_signals);
	get_next_line(0, command);
	save_command(*command, *get_curr_path);
	return (get_command(*command, *path, lkd_env));
}

void	change_env_launch(t_env *lkd_env, char *curr_dir)
{
	char buff[4096];
	char *str;
	int i;

	ft_strcpy(buff, "setenv SHELL=");
	set_env(lkd_env, ft_strcat(buff, curr_dir));
	str = find_in_env(lkd_env, ft_strdup("SHLVL"));
	i = ft_atoi(str) + 1;
	free(str);
	ft_strcpy(buff, "setenv SHLVL=");
	set_env(lkd_env, ft_strcat(buff, str = ft_itoa(i)));
	free(str);
}

void	main_loop(t_env *lkd_env, char **argv)
{
	char	*command;
	char	**path;
	char	*get_curr_path;
	int		return_command;

	g_curr_dir = find_cur_dir(lkd_env);
	g_username = find_name(lkd_env);
	get_curr_path = find_in_env(lkd_env, ft_strdup("PWD"));
	write_prompt(g_username, g_curr_dir);
	path = get_path(find_path(lkd_env));
	signal(SIGINT, handle_signals);
	change_env_launch(lkd_env, g_curr_dir);
	get_command_from_arg(argv, &command);
	save_command(command, get_curr_path);
	return_command = get_command(command, path, lkd_env);
	while (command && find_exit(command) == 0 && return_command == 1)
		return_command = exec_loop(lkd_env, &get_curr_path, &path, &command);
	free_prompt(g_username, g_curr_dir, path);
	free(command);
	free(get_curr_path);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	main_loop(get_env(env), argv);
	return (0);
}
