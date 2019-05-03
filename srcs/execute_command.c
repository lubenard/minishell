/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/03 17:14:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

char	*search_absolute_path(char *command)
{
	int		length;

	if (access(command, F_OK) != -1)
	{
		length = ft_strlen(command);
		while (command[length] != '/')
			length--;
		return (ft_strndup(command, length + 1));
	}
	else
		return (NULL);
}

char	*external_command(char **path, char *first_command)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;

	i = 0;
	if (first_command[0] == '/'
		|| (first_command[0] == '.' && first_command[1] == '/'))
		return (search_absolute_path(first_command));
	if (path == NULL || !ft_strcmp(first_command, "."))
		return (NULL);
	while (path[i + 1])
	{
		p_dir = opendir(path[i]);
		while ((p_dirent = readdir(p_dir)) != NULL)
		{
			if (ft_strcmp(p_dirent->d_name, first_command) == 0)
			{
				closedir(p_dir);
				return (ft_strdup(path[i]));
			}
		}
		closedir(p_dir);
		i++;
	}
	return (NULL);
}

char	**compact_env(t_env *lkd_env)
{
	int		i;
	char	**env;
	t_env	*tmp;

	i = 0;
	tmp = lkd_env;
	while (lkd_env)
	{
		i++;
		lkd_env = lkd_env->next;
	}
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (tmp)
	{
		env[i] = tmp->env_line;
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*reduce_command(char *command)
{
	int		i;
	int		e;
	char	*ret;

	i = 0;
	e = 0;
	if ((command[0] == '/' || command[0] == '.') && command[1])
	{
		i = ft_strlen(command);
		while (command[i] != '/')
			i--;
		while (command[i + e] && command[i + e] != ' ')
			e++;
		ret = ft_strlower(ft_strsub(command, i + 1, e - 1));
		free(command);
		return (ret);
	}
	return (NULL);
}

int		execute_command(char *get_right_path, char *command,
	char **argv, char **env)
{
	pid_t	wait_result;
	int		i;
	char	path[6000];

	i = 0;
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
		command = reduce_command(command);
	g_pid = fork();
	signal(SIGINT, handle_signals_proc);
	if (g_pid < 0)
		return (0);
	if (g_pid == 0)
	{
		ft_strcpy(path, get_right_path);
		execve(ft_strcat(path, command), argv, env);
	}
	if ((wait_result = wait(&g_pid)) == -1)
	{
		ft_putstr("An error happened: \n");
		get_error_exec(path);
	}
	return (free_after_exec(argv, get_right_path, command, env));
}
