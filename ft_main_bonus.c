/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:29:36 by descamil          #+#    #+#             */
/*   Updated: 2024/02/26 16:47:21 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_bonus(t_mini *mini, int i)
{
	int	state;

	while (mini->names->proc[i] && i + 1 < mini->names->index)
		waitpid(mini->names->proc[i++], NULL, 0);
	waitpid(mini->names->proc[i], &state, 0);
	return (state);
}

void	ft_error_write(char *str)
{
	write(2, str, ft_strlen_b(str));
	exit(1);
}

// static void	ft_free_path(t_mini *mini, int i)
// {
// 	unlink(".here_doc");
// 	while (mini->names->path[i])
// 		free(mini->names->path[i++]);
// 	free(mini->names->path);
// 	free(mini->names->proc);
// }

void	ft_multiple(t_mini *mini, char **argv, char **envp, int argc)
{
	mini->names->value = 'M';
	ft_setvalues(mini, argv, envp, argc);
	ft_first_comm(mini);
	while (--mini->names->num_comm > 2)
		ft_midd_comm(mini);
	ft_last_comm(mini);
	close(mini->names->fd_pipe[0]);
	close(mini->names->fd_pipe[1]);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_names	names;
// 	int		state;
// 	int		i;

// 	i = 0;
// 	if (argc < 5)
// 		ft_error_write("Few args\n");
// 	if (ft_strnstr(argv[1], "here_doc", 8) == 1)
// 	{
// 		if (argc != 6)
// 			ft_error_write("Few args for here_doc");
// 		names.value = 'H';
// 		ft_setvalues(&names, argv, envp, argc);
// 		ft_here_doc(&names);
// 	}
// 	else
		// ft_multiple(&names, argv, envp, argc);
// 	state = ft_wait_bonus(&names, 0);
// 	ft_free_path(&names, 0);
// 	return (WEXITSTATUS(state));
// }
