/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:46:02 by descamil          #+#    #+#             */
/*   Updated: 2024/03/03 16:20:07 by descamil         ###   ########.fr       */
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

char	*ft_set_zero(char *ptr, int point)
{
	int		len;

	len = ft_strlen(ptr);
	while (len-- >= point)
		ptr[len] = '\0';
	return (ptr);
}

int	ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s++ == (char)c)
			return (1);
	}
	if (*s == (char)c)
		return (1);
	return (0);
}

int	ft_strlcpy(char *dest, const char *src, int len_dest)
{
	int	i;

	i = 0;
	if (len_dest <= ft_strlen(src))
	{
		if (len_dest == 0)
			return (ft_strlen(src));
		while (len_dest > 1)
		{	
			dest[i] = src[i];
			len_dest--;
			i++;
		}
		dest[i] = '\0';
		return (ft_strlen(src));
	}
	i = 0;
	while (i < len_dest - 1 && src[i] != '\0')
	{	
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

void	ft_values(t_data *data, char **argv, char **envp)
{
	data->str = malloc(ft_strlen(argv[1]) + 1);
	ft_strlcpy(data->str, argv[1], ft_strlen(argv[1]) + 1);
	data->value = ft_strlen(data->str);
	data->d_quote = 0;
	data->s_quote = 0;
	data->command_len = 0;
	data->envp = envp;
	data->len_var = 0;
	
}

int	ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return (1);
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
