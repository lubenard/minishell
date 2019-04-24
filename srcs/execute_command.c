/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:46:50 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/24 14:55:25 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_absolute_path(char *command)
{
	if (access(command, F_OK) != -1)
		return (command);
	else
		return (NULL);
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
//		printf("J'explore %s\n", path[i]);
		while ((pDirent = readdir(pDir)) != NULL)
		{
//			printf("Je regarde ce fichier: %s\n", pDirent->d_name);
			if (ft_strcmp(pDirent->d_name, first_command) == 0)
			{
//				printf(">>>>>>>>>>>>>>>>>>>>>>>>>>Found it\n");
				closedir(pDir);
				return (path[i]);
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
//	printf("%d elements\n", i);
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (tmp)
	{
		env[i] = tmp->env_line;
//		printf("env[%d] vaut mtn %s\n", i, env[i]);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

int		execute_command(char *get_right_path, char *command, char **argv, char **env)
{
	pid_t process;
	int status;
	pid_t wait_result;
	int i;
	char path[6000];

	i = 0;
	process = fork();
	if (process < 0)
		return (0);
	if (process == 0)
	{
/*		printf(">>>>>>>> Je lance mon process\n");
		printf("Ma commande est %s\n", command);
		printf("mon get_right_path est %s\n", get_right_path);
		while (argv[i])
			printf("Argv are %s\n", argv[i++]);
		i = 0;
		while (env[i])
			printf("env are %s\n", env[i++]); */
		ft_strcpy(path, get_right_path);
		status = execve(ft_strcat(path, command), argv, env);
	}
	while ((wait_result = wait(&status)) == -1)
	{
		//printf("Process %lu returned result: %d\n", (unsigned long) wait_result, status);
		printf("an error happened\n");
		break ;
	}
//	printf("All children have finished.\n");
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	free(env);
	free(command);
	return (0);
}
