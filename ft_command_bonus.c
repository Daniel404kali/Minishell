/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:31:58 by descamil          #+#    #+#             */
/*   Updated: 2024/02/25 17:42:53 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_bonus(char *str, int i)
{
	perror(str);
	exit(i);
}

char	*ft_remove_path_bonus(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	**ft_create_path_bonus(t_mini *mini)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (mini->names->envp[++i] != NULL)
	{
		if (ft_strnstr(mini->names->envp[i], "PATH=", 5))
			path = ft_split_bonus(mini->names->envp[i], ':');
	}
	ft_remove_path_bonus(path[0], path[0], 5, 0);
	return (path);
}

char	*ft_validate_comm_bonus(t_mini *mini, int i)
{
	if (access(*mini->names->entire_comm, X_OK) == 0
		&& ft_strrchr_bonus(*mini->names->entire_comm, '/'))
		return (*mini->names->entire_comm);
	if (access(*mini->names->entire_comm, X_OK) != 0
		&& ft_strrchr_bonus(*mini->names->entire_comm, '/'))
		ft_error_bonus("Error", 127);
	mini->names->command = ft_strjoin_bonus("/", mini->names->entire_comm[0]);
	while (mini->names->path[i] != NULL)
	{
		mini->names->path_comm = ft_strjoin_bonus(mini->names->path[i++], mini->names->command);
		if (access(mini->names->path_comm, X_OK) == 0)
			return (mini->names->path_comm);
	}
	ft_error_bonus("Command not found", 127);
	return (NULL);
}

void	ft_execute_bonus(t_mini *mini, char *argv)
{
	mini->names->entire_comm = ft_split_bonus(argv, ' ');
	if (mini->names->entire_comm == NULL)
		ft_error_bonus("Bad split", 1);
	mini->names->route = ft_validate_comm_bonus(mini, 1);
	if (mini->names->fd_infile == -1)
	{
		mini->names->fd_infile = 0;
		if (mini->names->route != NULL)
			ft_error_bonus("Failed open input", 1);
		else
			write (2, "Command not found\n", 19);
	}
	execve(mini->names->route, mini->names->entire_comm, mini->names->envp);
}
