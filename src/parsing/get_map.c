/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:23:28 by mgalmari          #+#    #+#             */
/*   Updated: 2024/11/22 16:40:33 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!check_spaces(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_external_row(char *str)
{
	int	i;

	i = 0;
	if (empty_line(str))
		return (false);
	while (str && str[i])
	{
		if (!extern_char(str[i]))
			return (false);
		i++;
	}
	return (true);
}

char	**lst_to_mtx(t_list *head)
{
	char	**map;
	t_list	*tmp;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(head);
	tmp = head;
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
		return (NULL);
	while (tmp && i < size)
	{
		map[i] = ft_strdup((char *)tmp->content);
		if (!map[i])
			return (free_mtx(map), ft_lstclear(&head, free), NULL);
		i++;
		tmp = tmp->next;
	}
	map[i] = NULL;
	return (ft_lstclear(&head, free), map);
}

char	*get_map_rows(int fd, int flag)
{
	char	*read_line;
	char	*content;

	read_line = gnl(fd);
	if (flag == 0)
	{
		while (read_line && !is_external_row(read_line))
		{
			free(read_line);
			read_line = gnl(fd);
			if (!read_line)
			{
				complete_gnl(fd);
				return (error(MISSING_MAP), free(read_line), NULL);
			}
		}
	}
	if (!read_line || empty_line(read_line))
		return (free(read_line), NULL);
	content = ft_strdup(read_line);
	free(read_line);
	return (content);
}

char	**get_map(char *name_file)
{
	t_list	*head;
	t_list	*node;
	int		fd;
	char	*content;

	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		return (close(fd), NULL);
	head = NULL;
	content = get_map_rows(fd, 0);
	while (content)
	{
		node = ft_lstnew((void *)ft_strdup(content));
		if (empty_line(content) || !node)
			return (complete_gnl(fd), ft_lstclear(&head, free),
				close(fd), free(content), NULL);
		free(content);
		ft_lstadd_back(&head, node);
		content = get_map_rows(fd, 1);
	}
	complete_gnl(fd);
	close(fd);
	if (!head)
		return (NULL);
	return (lst_to_mtx(head));
}
