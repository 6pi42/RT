/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaget <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 06:17:54 by apaget            #+#    #+#             */
/*   Updated: 2016/06/06 16:13:32 by apaget           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	leave_event(GtkWidget *widget, GdkEventCrossing *event, t_map *map)
{
	(void)event;
	(void)widget;
	gtk_widget_set_sensitive(GTK_WIDGET(map->interface), TRUE);
}
