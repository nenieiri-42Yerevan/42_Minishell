/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:36:04 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/19 18:08:55 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_and_split(t_var *env_lst)
{
	char	**path;

	path = 0;
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PATH", 5) == 0)
		{
			path = ft_split(env_lst->value, ':');
			break ;
		}
		env_lst = env_lst->next;
	}
	return (path);
}

static char	*find_path(t_var *env_lst, char *command)
{
	char	**path;
	char	*value;
	int		i;

	i = -1;
	path = find_and_split(env_lst);
	while (path != 0 && path[++i] != 0)
	{
		value = strjoin_base(path[i], command, '/');
		if (access(value, F_OK | X_OK) == 0)
		{
			arr_free(path);
			return (value);
		}
		free(value);
	}
	if (path != 0)
		arr_free(path);
	return (0);
}

char	*find_command(t_command *command, t_var *env_lst)
{
	char	*path;

	path = 0;
	if (ft_strchr(command->args[0], '/') != 0)
		path = ft_strdup(command->args[0]);
	else
	{
		path = find_path(env_lst, command->args[0]);
		if (path != 0)
		{
			free(command->args[0]);
			command->args[0] = ft_strdup(path);
		}
	}
	return (path);
}