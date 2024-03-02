/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:29:19 by descamil          #+#    #+#             */
/*   Updated: 2024/03/02 19:51:25 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	total_size;
	char	*ptr_chr;

	if ((nmemb == SIZE_MAX) || (size == SIZE_MAX))
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	ptr_chr = (char *)ptr;
	while (i < total_size)
		ptr_chr[i++] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_total;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	size_total = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)ft_calloc(sizeof(char), size_total + 1);
	if (ptr == NULL)
		return (NULL);
	while ((char *)s1 && (char)s1[i] != '\0')
		ptr[j++] = (char)s1[i++];
	j = 0;
	while ((char *)s2 && (char)s2[j] != '\0')
		ptr[i++] = (char)s2[j++];
	ptr[i] = '\0';
	if (s1)
		free((char *)s1);
	return (ptr);
}

int	ft_count_quotes(t_data *data)
{
	int	size;
	int	i = 0;
	
	size = ft_strlen(data->str);
	while (size-- > 0)
	{
		if (data->str[i] == '\"')
			data->d_quote++;
		else if (data->str[i] == '\'')
			data->s_quote++;
		i++;
	}
	if (data->d_quote % 2 != 0 || data->s_quote % 2 != 0)
		return (0);
	if ((data->s_quote + data->d_quote) == ft_strlen(data->str))
		return (0);
	if (data->d_quote == 0)
		data->d_quote = -1;
	if (data->s_quote == 0)
		data->s_quote = -1;
	return (1);
}

int	ft_single_quotes(t_data *data, int i, int q)
{
	if (data->str[i] == q && data->str[i + 1] == q)
		return (i + 2);
	else
	{
		i++;
		while (data->str[i++] != q)
			data->command_len++;
		return (i);
	}
	return (-1);
}

char	*ft_remove(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

char	*ft_find(t_data *data, char *str)
{
	char	*any;
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if(ft_strnstr(data->envp[i++], str, ft_strlen(str)) == 1)
		{
			any = data->envp[i];
			any = ft_remove(any, any, ft_strlen(any), 0);
			return (any);
		}
	}
	return ("");
}

char	*ft_div_join(t_data *data, char *any, int i)
{
	char 	*tmp;
	char	*final;
	int		length;
	int		k;
	int		j;

	k = i;
	j = 0;
	length = 0;
	while (data->str[k++] != '\0')
		length++;
	k = i;
	tmp = malloc(length + 1);
	while (data->str[k] != '\0')
	{
		tmp[j++] = data->str[k];
		data->str[k++] = '\0';
	}
	final = ft_strjoin(data->str, any);
	final = ft_strjoin(final, tmp);
	free(tmp);
	return (final);
}

int	ft_translate(t_data *data, int i)
{
	char	*tmp;
	char	*any;
	int		k;
	int		j;
	
	j = 0;
	k = i;
	while (data->str[k + j] != '\"' && data->str[k + j] != '\'')
		j++;
	tmp = malloc(j + 1);
	j = 0;
	while (data->str[k] != '\"' && data->str[k] != '\'')
		tmp[j++] = data->str[k++];
	tmp[j] = '\0';
	any = ft_find(data, tmp);
	data->str = ft_div_join(data, any, i);
	free(tmp);
	return (ft_strlen(data->str));
}

int	ft_double_quotes(t_data *data, int i, int q)
{
	if (data->str[i] == q && data->str[i + 1] == q)
		return (i + 2);
	else
	{
		i++;
		while (data->str[i++] != q)
		{
			if (data->str[i] == '$')
				data->command_len = ft_translate(data, i + 1);
			else
				data->command_len++;
		}
		return (i);
	}
	return (-1);
}

int	ft_valid_quotes(t_data *data, int i)
{
	if (data->str[i] == '\'')
	{
		i = ft_single_quotes(data, i, '\'');
		if (i == -1)
			return (-1);
	}
	else if (data->str[i] == '\"')
	{
		i = ft_double_quotes(data, i, '\"');
		if (i == -1)
			return (-1);
	}
	else
	{
		data->command_len++;
		i++;
	}
	return (i);
}
