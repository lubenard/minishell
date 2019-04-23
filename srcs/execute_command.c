/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/23 15:15:14 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_absolute_path(char *command)
{
	(void)command;
	return (command);
}

char	*external_command(char **path, char *first_command)
{
	int				i;
	struct dirent	*pDirent;
	DIR				*pDir;

	i = 0;
	if (first_command[0] == '/' || (first_command[0] == '.' && first_command[1] == '.'))
		return (search_absolute_path(first_command));
	while (path[i+1])
	{
		pDir = opendir(path[i]);
		printf("J'explore %s\n", path[i]);
		while ((pDirent = readdir(pDir)) != NULL)
		{
			printf("Je regarde ce fichier: %s\n", pDirent->d_name);
			if (ft_strcmp(pDirent->d_name, first_command) == 0)
			{
				printf(">>>>>>>>>>>>>>>>>>>>>>>>>>Found it\n");
				return (path[i]);
			}
		}
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
	printf("%d elements\n", i);
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (tmp->next)
	{
		env[i] = tmp->env_line;
		printf("env[%d] vaut mtn %s\n", i, env[i]);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

int		execute_command(char *get_right_path, char *command,char **argv, char **env)
{
	pid_t process;
	(void)get_right_path;
	(void)env;
	int status;
	pid_t wait_result;

	process = fork();
	if (process < 0)
		return (0);
	if (process == 0)
	{
		argv[0] = "ls";
		execv(argv[0], argv);
		return (2);
	}

	while ((wait_result = wait(&status)) != -1)
	{
		printf("Process %lu returned result: %d\n", (unsigned long) wait_result, status);
	}
    printf("All children have finished.\n");

	printf("Command is '%s', argv are: \n", command);
	int i = 0;
	while (argv[i])
		printf("%s ", argv[i++]);
	return (0);
}
