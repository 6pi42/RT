/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_conf2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 15:31:16 by amathias          #+#    #+#             */
/*   Updated: 2016/07/18 15:31:26 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	connect_check_button2(GtkWidget *widget, t_map *map)
{
	if (ft_strsearch("transparence",
		(char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),
			map->config.transparence);
	else if (ft_strsearch("ombre", (char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),
		map->config.ombre);
	else if (ft_strsearch("print_neg",
		(char*)gtk_widget_get_name(widget)) != -1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),
		map->config.print_neg);
}
