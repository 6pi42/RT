/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 14:57:10 by apaget            #+#    #+#             */
/*   Updated: 2016/07/16 16:00:11 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	connect_signal_gtk(t_map *map)
{
	g_signal_connect(GTK_WINDOW(map->window), "key_press_event",
													(void*)key_press, map);
	//g_signal_connect(GTK_WINDOW(map->window), "key_release_event",
	//												(void*)key_release, map);
}
