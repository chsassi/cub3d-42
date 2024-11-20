/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:40:35 by chsassi           #+#    #+#             */
/*   Updated: 2024/11/20 15:40:36 by chsassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	check_spaces(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}
