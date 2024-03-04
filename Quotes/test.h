/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:28:36 by descamil          #+#    #+#             */
/*   Updated: 2024/03/03 16:19:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#define BLACK         "\033[0;30m"
#define DARK_RED      "\033[0;31m"
#define DARK_GREEN    "\033[0;32m"
#define DARK_YELLOW   "\033[0;33m"
#define DARK_BLUE     "\033;0;34m"
#define DARK_PURPLE   "\033[0;35m"
#define DARK_CYAN     "\033[0;36m"
#define LIGHT_GRAY    "\033[0;37m"
#define DARK_GRAY     "\033[1;30m"
#define RED           "\033[1;31m"
#define GREEN         "\033[1;32m"
#define YELLOW        "\033[1;33m"
#define BLUE          "\033[1;34m"
#define PURPLE        "\033[1;35m"
#define CYAN          "\033[1;36m"
#define BRIGHT_WHITE  "\033[1;37m"
#define RESET         "\033[0m"

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		value;
	int		len_var;
	int		d_quote;
	int		s_quote;
	int		command_len;
	
	char	*str;
	char	*any;
	char	*rm_str;

	char	**envp;
}			t_data;

int		ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);
int		ft_translate(t_data *data, int i);

int		ft_count_quotes(t_data *data);
int		ft_valid_quotes(t_data *data, int i);
int		ft_single_quotes(t_data *data, int i, int q, int valid);
int		ft_double_quotes(t_data *data, int i, int q, int valid);
int		ft_strnstr(const char *s1, const char *s2, size_t len);

int		ft_remove_quotes(t_data *data);

char	*ft_set_zero(char *ptr, int point);
char	*ft_strjoin(char const *s1, char const *s2);

void	ft_values(t_data *data, char **argv, char **envp);


#endif