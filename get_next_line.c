/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:29:50 by ixu               #+#    #+#             */
/*   Updated: 2023/11/13 17:10:43 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	create_list(t_list **list, int fd)
{
	int		chars_read;
	char	*buf;
	int		status;

	while (!has_newline_char(*list))
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (-2);
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read <= 0)
		{
			free(buf);
			return (chars_read);
		}
		buf[chars_read] = '\0';
		status = ft_lstadd_back(list, buf);
		if (status == -2)
		{
			free(buf);
			return (-2);
		}
	}
	return (1);
}

static char	*list_to_str(t_list *list, int *status)
{
	char	*str;

	str = (char *)malloc((ft_strlen(list) + 1) * sizeof(char));
	if (str == NULL)
	{
		*status = -2;
		return (NULL);
	}
	str = ft_str_cpy(str, list);
	return (str);
}

static void	fill_new_node(t_list *list, t_list **new_node, char **buf)
{
	t_list	*last_node;
	int		i;
	int		j;

	last_node = list;
	while (last_node->next != NULL)
		last_node = last_node->next;
	i = 0;
	j = 0;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		(*buf)[j++] = last_node->str_buf[i];
	(*buf)[j] = '\0';
	(*new_node)->str_buf = *buf;
	(*new_node)->next = NULL;
}

static void	update_list(t_list **list, int *status)
{
	char	*buf;
	t_list	*new_node;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (buf == NULL || new_node == NULL)
	{
		free(new_node);
		free(buf);
		free_list(list);
		*status = -2;
		return ;
	}
	fill_new_node(*list, &new_node, &buf);
	free_list(list);
	*list = NULL;
	if (new_node->str_buf[0])
		*list = new_node;
	else
	{
		free(buf);
		free(new_node);
	}
}

/*
	If malloc fails, status = -2;
	if there is error in reading, status = -1;
	if reading is successful, status = 1.
*/

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = create_list(&list, fd);
	if (status == -1 || status == -2 || list == NULL)
	{
		free_list(&list);
		return (NULL);
	}
	next_line = list_to_str(list, &status);
	if (status == -2)
	{
		free_list(&list);
		return (NULL);
	}
	update_list(&list, &status);
	if (status == -2)
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
