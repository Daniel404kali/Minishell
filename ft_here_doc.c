/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:40:44 by descamil          #+#    #+#             */
/*   Updated: 2024/03/04 16:15:52 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child1(t_mini *mini)
{
	int	fd_tmp;

	fd_tmp = open(".here_doc", O_RDONLY);
	if (pipe(mini->names->fd_pipe) == -1)
		ft_error_bonus("Pipe error", 1);
	mini->names->proc[mini->names->index] = fork();
	if (mini->names->proc[mini->names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (mini->names->proc[mini->names->index] == 0)
	{
		close(mini->names->fd_pipe[0]);
		dup2(fd_tmp, STDIN_FILENO);
		dup2(mini->names->fd_pipe[1], STDOUT_FILENO);
		close(fd_tmp);
		close(mini->names->fd_pipe[1]);
		ft_execute_bonus(mini, mini->here->comm1);
	}
	close(mini->names->fd_pipe[1]);
	mini->names->index++;
}

void	ft_child2(t_mini *mini)
{
	int		fd;

	mini->names->proc[mini->names->index] = fork();
	if (mini->names->proc[mini->names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (mini->names->proc[mini->names->index] == 0)
	{
		fd = open(mini->here->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); /* Salida del HERE_DOC -> Modificar */
		if (fd == -1)
		{
			close(mini->names->fd_pipe[0]);
			ft_error_bonus("Error open input", 1);
		}
		dup2(mini->names->fd_pipe[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(mini->names->fd_pipe[0]);
		close(fd);
		ft_execute_bonus(mini, mini->here->comm2);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_here_doc(t_mini *mini)
{
	char	*line;
	int		fd_tmp;
	int		value;
	
	value = ft_strlen_b(mini->here->limiter);
	mini->names->value = 'H';
	ft_setvalues(mini, mini->argv, mini->envp, mini->argc);
	fd_tmp = open(".here_doc", O_WRONLY | O_CREAT, 0644);
	if (fd_tmp == -1)
		ft_error_bonus("Error open", 1);
	while (1)
	{
		line = get_next_line(0);
		if ((ft_strlen_b(line) - 1) == value && ft_strncmp(line, mini->names->limiter, value) == 0)
			break ;
		if (write(fd_tmp, line, ft_strlen_b(line)) == -1)
			ft_error_bonus("Error write", 1);
	}
	ft_child1(mini);
	ft_child2(mini);
}