/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:23:28 by mgalmari          #+#    #+#             */
/*   Updated: 2024/11/13 16:09:18 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path_texture(char	*texture, char *flag)
{
	char	*info;
	int		index;
	int		i;

	i = 0;
	index = ft_strlen(flag);
	while (texture && check_spaces(texture[index]))
		index++;
	info = ft_calloc(ft_strlen(texture) - index, sizeof(char));
	if (!info)
		return (error(MALLOC_E), NULL);
	while (texture && texture[index])
	{
		info[i] = texture[index];
		i++;
		index++;
	}
	return (info);
}

char	*get_info_element(char *name_file, char *flag)
{
	char	*texture;
	int		fd;

	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		return (close(fd), error(OPEN_E), NULL);
	texture = gnl(fd);
	while (texture && ft_strncmp(texture, flag, ft_strlen(flag)))
	{
		free(texture);
		texture = gnl(fd);
	}
	close(fd);
	if (!texture || (texture && !texture[0]))
		return (free(texture), error(MISSING_EL), NULL);
	return (get_path_texture(texture, flag));
}

t_element	get_elements(char *name_file)
{
	t_element	info_elements;

	info_elements = (t_element){0};
	info_elements.texture_nord = get_info_element(name_file, "NO");
	if (!info_elements.texture_nord)
		return ((t_element){0});
	info_elements.texture_sud = get_info_element(name_file, "SO");
	if (!info_elements.texture_sud)
		return ((t_element){0});
	info_elements.texture_est = get_info_element(name_file, "EA");
	if (!info_elements.texture_est)
		return ((t_element){0});
	info_elements.texture_ovest = get_info_element(name_file, "WE");
	if (!info_elements.texture_ovest)
		return ((t_element){0});
	info_elements.floor = get_info_element(name_file, "F");
	if (!info_elements.floor)
		return ((t_element){0});
	info_elements.ceiling = get_info_element(name_file, "C");
	if (!info_elements.ceiling)
		return ((t_element){0});
	return (info_elements);
}
