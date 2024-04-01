/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:30:03 by ixu               #+#    #+#             */
/*   Updated: 2023/11/13 16:40:48 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline_char(t_list *list)
{
	t_list	*last_node;
	int		i;

	if (list == NULL)
		return (0);
	last_node = list;
	while (last_node->next != NULL)
		last_node = last_node->next;
	i = 0;
	while (last_node->str_buf[i] != '\0')
	{
		if (last_node->str_buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_lstadd_back(t_list **lst, char *buf)
{
	t_list	*ptr;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (-2);
	new_node->next = NULL;
	new_node->str_buf = buf;
	if (*lst == NULL)
	{
		*lst = new_node;
		return (1);
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_node;
	return (1);
}

void	free_list(t_list **list)
{
	t_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		free(temp->str_buf);
		*list = temp;
		temp = temp->next;
		free(*list);
	}
	*list = NULL;
}

int	ft_strlen(t_list *list)
{
	int		i;
	int		str_len;
	t_list	*temp;

	str_len = 0;
	temp = list;
	while (temp != NULL)
	{
		i = 0;
		while (temp->str_buf[i] != '\0')
		{
			if (temp->str_buf[i] == '\n')
			{
				str_len++;
				break ;
			}
			str_len++;
			i++;
		}
		temp = temp->next;
	}
	return (str_len);
}

char	*ft_str_cpy(char *str, t_list *list)
{
	int		i;
	int		j;
	t_list	*temp;

	j = 0;
	temp = list;
	while (temp != NULL)
	{
		i = 0;
		while (temp->str_buf[i] != '\0')
		{
			if (temp->str_buf[i] == '\n')
			{
				str[j++] = temp->str_buf[i];
				break ;
			}
			str[j] = temp->str_buf[i];
			i++;
			j++;
		}
		temp = temp->next;
	}
	str[j] = '\0';
	return (str);
}
