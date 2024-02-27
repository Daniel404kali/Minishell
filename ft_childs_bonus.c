/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_childs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:34:29 by descamil          #+#    #+#             */
/*   Updated: 2024/02/25 17:47:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setvalues(t_mini *mini, char **argv, char **envp, int argc)
{
	mini->names->index = 0;
	mini->names->argc = argc;
	mini->names->argv = argv;
	mini->names->envp = envp;
	mini->names->path = ft_create_path_bonus(mini);
	mini->names->output = mini->names->argv[mini->names->argc - 1];
	if (mini->names->value == 'M')
	{
		mini->names->fd = 0;
		mini->names->comm_midd = 3;
		mini->names->input = mini->names->argv[1];
		mini->names->num_comm = mini->names->argc - 3 + 1;
		mini->names->proc = malloc(mini->names->num_comm * sizeof(int));
	}
	else if (mini->names->value == 'H')
	{
		mini->names->proc = malloc(2 * sizeof(int));
		mini->names->limiter = argv[2];
	}
}

void	ft_first_comm(t_mini *mini)
{
	if (pipe(mini->names->fd_pipe) == -1)
		ft_error_bonus("Pipe error", 1);
	mini->names->proc[mini->names->index] = fork();
	if (mini->names->proc[mini->names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (mini->names->proc[mini->names->index] == 0)
	{
		close(mini->names->fd_pipe[0]);
		mini->names->fd_infile = open(mini->names->input, O_RDONLY);
		dup2(mini->names->fd_infile, STDIN_FILENO);
		dup2(mini->names->fd_pipe[1], STDOUT_FILENO);
		close(mini->names->fd_infile);
		close(mini->names->fd_pipe[1]);
		ft_execute_bonus(mini, mini->names->argv[2]);
	}
	mini->names->fd_tmp = mini->names->fd_pipe[0];
	mini->names->index++;
	close(mini->names->fd_pipe[1]);
}

void	ft_midd_comm(t_mini *mini)
{
	if (pipe(mini->names->fd_pipe) == -1)
		ft_error_bonus("Pipe Error", 1);
	mini->names->proc[mini->names->index] = fork();
	if (mini->names->proc[mini->names->index] == -1)
		ft_error_bonus("Failed in Fork()", 1);
	if (mini->names->proc[mini->names->index] == 0)
	{
		close(mini->names->fd_pipe[0]);
		dup2(mini->names->fd_tmp, STDIN_FILENO);
		dup2(mini->names->fd_pipe[1], STDOUT_FILENO);
		close(mini->names->fd_tmp);
		close(mini->names->fd_pipe[1]);
		ft_execute_bonus(mini, mini->names->argv[mini->names->comm_midd]);
	}
	mini->names->fd_tmp = mini->names->fd_pipe[0];
	mini->names->index++;
	mini->names->comm_midd++;
	close(mini->names->fd_pipe[1]);
}

void	ft_last_comm(t_mini *mini)
{
	int		fd;

	mini->names->proc[mini->names->index] = fork();
	if (mini->names->proc[mini->names->index] == -1)
		ft_error_bonus("Filed in fork()", 1);
	if (mini->names->proc[mini->names->index] == 0)
	{
		fd = open(mini->names->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			close(mini->names->fd_tmp);
			ft_error_bonus("Error open input", 1);
		}
		dup2(mini->names->fd_tmp, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(mini->names->fd_tmp);
		close(fd);
		ft_execute_bonus(mini, mini->names->argv[mini->names->argc - 2]);
	}
	mini->names->index++;
}
