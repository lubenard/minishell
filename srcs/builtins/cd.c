/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:05:11 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/12 21:28:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_cd(t_env *lkd_env, char *old_pwd, char *new_pwd)
{
	char new_line[5000];
	char old_line[5000];

	ft_strcpy(new_line, "setenv PWD=");
	set_env(lkd_env, ft_strcat(new_line, new_pwd));
	ft_strcpy(old_line, "setenv OLDPWD=");
	if (!old_pwd)
		ft_strcat(old_line, new_pwd);
	else
		ft_strcat(old_line, old_pwd);
	set_env(lkd_env, old_line);
}

int		get_shortcut_path(t_env *lkd_env, char **spec_path, char *path)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	if (path[0] == '~' && path[1] == '/' && ft_strlen(path) > 2)
	{
		while (path[2 + i])
			i++;
		str = ft_strsub(path, 2, i);
		free(path);
		path = find_in_env(lkd_env, ft_strdup("HOME"));
		str2 = ft_strjoin(path, "/");
		*spec_path = ft_strjoin(str2, str);
		free(str);
		free(str2);
		free(path);
		return (0);
	}
	return (1);
}

char	*handle_sortcut(t_env *lkd_env, char *path)
{
	char *spec_path;

	if (!get_shortcut_path(lkd_env, &spec_path, path))
		return (spec_path);
	else if (!ft_strcmp(path, "~")
	|| !ft_strcmp(path, "") || !ft_strcmp(path, "--")
	|| !ft_strcmp(path, "~/"))
	{
		free(path);
		path = find_in_env(lkd_env, ft_strdup("HOME"));
	}
	else if (!ft_strcmp(path, "-"))
	{
		free(path);
		path = find_in_env(lkd_env, ft_strdup("OLDPWD"));
	}
	return (path);
}

void	change_dir(t_env *lkd_env, char *path)
{
	char *curr_dir;
	char buff_dir[4097];
	char buff_dir2[4097];
	char *new_dir;

	curr_dir = getcwd(buff_dir, 4096);
	path = handle_sortcut(lkd_env, path);
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) == -1)
			ft_putstr_fd("cd : No such file or directory : ", 2);
		else if (access(path, R_OK) == -1)
			ft_putstr_fd("cd : Permission denied : ", 2);
		else
			ft_putstr_fd("cd : Not a directory : ", 2);
		ft_putendl_fd(path, 2);
	}
	else
		change_env_cd(lkd_env, curr_dir, (new_dir = getcwd(buff_dir2, 4096)));
	free(path);
}

void	cd(t_env *lkd_env, char *command)
{
	char	*extracted_path;

	extracted_path = extract_path(command);
	change_dir(lkd_env, extracted_path);
}
