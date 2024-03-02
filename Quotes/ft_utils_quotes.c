/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:46:02 by descamil          #+#    #+#             */
/*   Updated: 2024/03/02 19:44:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	if (*s == (char)c)
		return (1);
	return (0);
}

void	ft_values(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data *));
	data->d_quote = 0;
	data->s_quote = 0;
	data->command_len = 0;
	data->envp = envp;
}

int	ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return (0);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] == s2[j] && s2[j] != '\0' && (k < len))
			{
				k++;
				j++;
				if (s2[j] == '\0')
					return (1);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
