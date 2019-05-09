/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:57:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/09 13:57:46 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*error_setenv(char *command, int i, int e)
{
	int k;

	if (ft_strrchr(command, i, ' ') != NULL)
	{
		ft_putstr_fd("setenv: invalid syntax\n", 2);
		ft_putstr_fd("the correct syntax is t=1\n", 2);
		return (NULL);
	}
	k = i;
	while (command[k])
	{
		if (command[k] > 127 || command[k] < 0
		|| command[k] == '"' || command[k] == '\'')
		{
			ft_putstr_fd("setenv: invalid syntax\n", 2);
			ft_putstr_fd("Invalid character\n", 2);
			return (NULL);
		}
		k++;
	}
	return (ft_strsub(command, i, e));
}

char	*extract_first_env(char *command, int mode)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	if (mode == 0)
	{
		while (command[i] != '=' && command[i])
			++i;
		return (ft_strsub(command, 0, i));
	}
	else
	{
		while (command[i] && command[i] != ' ')
			++i;
		while (command[i] == ' ' || command[i] == '\t')
			++i;
		while (command[i + e] && command[i + e] != '=')
			++e;
		if (e == 0)
			return (ft_strdup(command));
		return (error_setenv(command, i, e));
	}
}

void	set_env3(t_env *lkd_env, t_env *new_element,
	char *to_search, char *to_add)
{
	free(to_search);
	if (lkd_env->prev || lkd_env->next)
	{
		new_element = new_maillon();
		lkd_env->next = new_element;
		lkd_env->next->prev = lkd_env;
		ft_strcpy(lkd_env->next->env_line, to_add);
	}
	else
		ft_strcpy(lkd_env->env_line, to_add);
	free(to_add);
}

int		set_env2(t_env **lkd_env, t_env **tmp,
	char **to_extract, char **to_search)
{
	t_env *tmp2;

	*to_extract = extract_first_env((*lkd_env)->env_line, 0);
	if (ft_strcmp(*to_extract, *to_search) == 0)
	{
		free(*to_extract);
		tmp2 = (*lkd_env)->prev;
		unset_env(*lkd_env, *to_search);
		*lkd_env = tmp2;
		while ((*lkd_env)->prev)
			(*lkd_env) = (*lkd_env)->prev;
		while (*lkd_env)
		{
			if (!(*lkd_env)->next)
				*tmp = *lkd_env;
			*lkd_env = (*lkd_env)->next;
		}
		return (1);
	}
	return (0);
}

void	set_env(t_env *lkd_env, char *command)
{
	t_env	*new_element;
	t_env	*tmp;
	char	*to_add;
	char	*to_search;
	char	*to_extract;

	new_element = NULL;
	if (ft_strchr(command, '=') == 0
	|| !(to_search = extract_first_env(command, 1)))
		return ;
	to_add = extract_params(command);
	while (lkd_env)
	{
		if (set_env2(&lkd_env, &tmp, &to_extract, &to_search) == 1)
			break ;
		if (!lkd_env->next)
			tmp = lkd_env;
		lkd_env = lkd_env->next;
		free(to_extract);
	}
	if (!lkd_env)
		lkd_env = tmp;
	set_env3(lkd_env, new_element, to_search, to_add);
}
