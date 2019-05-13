/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/13 18:19:01 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

char	*search_absolute_path2(char *command, char *str, char *str2)
{
	int length;

	length = ft_strlen(command);
	while (command[length] != '/')
		length--;
	free(str);
	free(str2);
	return (ft_strndup(command, length + 1));
}

char	*search_absolute_path(char *command)
{
	char	*str;
	char	*str2;
	char	buff[6000];

	str2 = ft_strjoin(getcwd(buff, 6000), "/");
	str = ft_strjoin(str2, command);
	if (command[0] != '/' && ft_strncmp(command, "..", 2)
	&& command[0] && !access(str, F_OK))
	{
		free(str);
		if (ft_strchr(command, '/'))
			return (str2);
		free(str2);
		return (NULL);
	}
	else if (access(command, F_OK) != -1)
		return (search_absolute_path2(command, str, str2));
	free(str);
	free(str2);
	return (NULL);
}

char	*external_command(char **path, char *first_command)
{
	int				i;
	struct dirent	*p_dirent;
	DIR				*p_dir;
	char			*does_it_exist;
	int				e;

	i = 0;
	e = (path != NULL) ? 1 : 0;
	while (e == 1 && path[i])
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
	if ((does_it_exist = search_absolute_path(first_command)))
		return (does_it_exist);
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
	if (access(command, X_OK) == -1 || get_error_exec(command, 0))
	{
		get_error_exec(command, 1);
		free(command);
		return (NULL);
	}
	if ((command[0] == '/' || !ft_strncmp(command, "./", 2)
	|| !ft_strncmp(command, "..", 2)) && command[2])
	{
		i = ft_strlen(command);
		while (command[i] != '/')
			i--;
		while (command[i + e] && command[i + e] != ' ')
			e++;
		ret = ft_strlower(ft_strsub(command, i + 1, e - 1));
		return (ret);
	}
	return (NULL);
}

char	*check_exec_rights(char *get_right_path, char *command)
{
	char *path;

	if (access((path = ft_strjoin(get_right_path, command)), X_OK)
	|| get_error_exec(path, 0))
	{
		get_error_exec(path, 1);
		free(path);
		return (NULL);
	}
	free(path);
	return (ft_strdup(command));
}

int		execute_command(char *get_right_path, char *command,
	char **argv, char **env)
{
	char	path[6000];

	if (command[0] == '/' || command[0] == '.')
		command = reduce_command(command);
	else
		command = check_exec_rights(get_right_path, command);
	if (command == NULL)
		return (free_after_exec(argv, get_right_path, env));
	g_pid = fork();
	signal(SIGINT, handle_signals_proc);
	if (g_pid < 0)
		return (0);
	if (g_pid == 0)
	{
		ft_strcpy(path, get_right_path);
		execve(ft_strcat(path, command), argv, env);
	}
	wait(&g_pid);
	free(command);
	return (free_after_exec(argv, get_right_path, env));
}
