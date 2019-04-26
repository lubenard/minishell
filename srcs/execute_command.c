/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/26 10:41:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	struct dirent	*pDirent;
	DIR				*pDir;

	i = 0;
	if (first_command[0] == '/' || (first_command[0] == '.' && first_command[1] == '/'))
		return (search_absolute_path(first_command));
	if (path == NULL)
		return (NULL);
	while (path[i + 1])
	{
		pDir = opendir(path[i]);
		while ((pDirent = readdir(pDir)) != NULL)
		{
			if (ft_strcmp(pDirent->d_name, first_command) == 0)
			{
				closedir(pDir);
				return (ft_strdup(path[i]));
			}
		}
		closedir(pDir);
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
	int i;
	int e;
	char *ret;

	i = 0;
	e = 0;
	if (command[0] == '/' && command[1])
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

int		execute_command(char *get_right_path, char *command, char **argv, char **env)
{
	pid_t process;
	int status;
	pid_t wait_result;
	int i;
	char path[6000];

	i = 0;
	if (command[0] == '/' || command[0] == '.')
		command = reduce_command(command);
	process = fork();
	if (process < 0)
		return (0);
	if (process == 0)
	{
	/*	printf(">>>>>>>> Je lance mon process\n");
		printf("Ma commande est %s\n", command);
		printf("mon get_right_path est %s\n", get_right_path);
		while (argv[i])
			printf("Argv are %s\n", argv[i++]);
		i = 0;
		while (env[i])
			printf("env are %s\n", env[i++]);*/
		ft_strcpy(path, get_right_path);
		status = execve(ft_strcat(path, command), argv, env);
	}
	while ((wait_result = wait(&status)) == -1)
	{
		printf("an error happened\n");
		break ;
	}
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(get_right_path);
	free(argv);
	free(env);
	free(command);
	return (0);
}
