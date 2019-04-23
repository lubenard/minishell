/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:05:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/04/23 19:42:08 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_path(char *command)
{
	int i;
	int e;

	i = 2;
	e = 0;
	while (command[i] == ' ')
		i++;
	while (command[i + e])
		e++;
	return(ft_strsub(command, i, e));
}

void	change_env_cd(t_env *lkd_env, char *old_pwd, char *new_pwd)
{
	char new_line[5000];
	char old_line[5000];

	while (lkd_env)
	{
		if (ft_strncmp(lkd_env->env_line, "PWD", 2) == 0)
		{
			ft_strcpy(new_line, "PWD=");
			ft_strcpy(lkd_env->env_line, ft_strcat(new_line, new_pwd));
		}
		if (ft_strncmp(lkd_env->env_line, "OLDPWD", 5) == 0)
		{
			ft_strcpy(old_line, "OLDPWD=");
			ft_strcpy(lkd_env->env_line, ft_strcat(old_line, old_pwd));
		}
		lkd_env = lkd_env->next;
	}
}

char	*find_home_path(t_env *lkd_env)
{
	int e;

	e = 0;
	while (lkd_env)
	{
		if (ft_strncmp(lkd_env->env_line, "HOME", 3) == 0)
		{
			while (lkd_env->env_line[4 + e])
				e++;
			return (ft_strsub(lkd_env->env_line, 4, e));
		}
		lkd_env = lkd_env->next;
	}
	return (ft_strdup("~#"));
}

void	change_dir(t_env *lkd_env, char *path)
{
	char *curr_dir;
	char buff_dir[4097];
	char buff_dir2[4097];
	char *new_dir;

	if (ft_strcmp(path, "~/") == 0)
	{
		//free(path);
		path = find_home_path(lkd_env);
	}
	curr_dir = getcwd(buff_dir, 4096);
	if (chdir(path) != 0)
		ft_putstr("Error during cd\n");
	else
		change_env_cd(lkd_env, curr_dir, (new_dir = getcwd(buff_dir2, 4096)));
}

void	cd(t_env *lkd_env, char *command)
{
	char	*extracted_path;

	extracted_path = extract_path(command);
	change_dir(lkd_env, extracted_path);
	free(extracted_path);
}
