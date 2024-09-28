/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:36:30 by mrochedy          #+#    #+#             */
/*   Updated: 2024/07/02 10:21:34 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*u_dest;
	const unsigned char	*u_src;

	if (!dest && !src)
		return (NULL);
	i = 0;
	u_dest = dest;
	u_src = src;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	size_t	size_to_copy;
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	size_to_copy = original_size;
	if (new_size < original_size)
		size_to_copy = new_size;
	ft_memcpy(new_ptr, ptr, size_to_copy);
	free(ptr);
	return (new_ptr);
}

int	remove_nl(char **str)
{
	int		len;
	int		i;
	char	*new_str;

	if (*str)
	{
		len = ft_strlen(*str);
		if (len > 0 && (*str)[len - 1] == '\n')
		{
			new_str = malloc(sizeof(char) * (len));
			if (!new_str)
				return (1);
			i = 0;
			while (i < len - 1)
			{
				new_str[i] = (*str)[i];
				i++;
			}
			new_str[i] = '\0';
			free(*str);
			*str = new_str;
		}
	}
	return (0);
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}
