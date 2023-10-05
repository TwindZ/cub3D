/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:09:54 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/05 08:48:22 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_vector(double *x, double *y, double angle)
{
	double old_x ;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	move_player(t_data *data, double move_speed)
{
	double	checkRadius;

	checkRadius = 0.5;
	if (move_speed < 0)
		checkRadius = -0.5;
	if(data->map[(int)(data->ray.pos.x + data->ray.dir.x * (move_speed
		+ checkRadius))][(int)data->ray.pos.y] == '0')
		data->ray.pos.x += data->ray.dir.x * move_speed;
	if(data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y + data->ray.dir.y
		* (move_speed + checkRadius))] == '0')
		data->ray.pos.y += data->ray.dir.y * move_speed;
}

void	strafe_player(t_data *data, double strafe_speed)
{
	double	checkRadius;

	checkRadius = 0.5;
	if (strafe_speed < 0)
		checkRadius = -0.5;
	if(data->map[(int)(data->ray.pos.x + data->ray.dir.y * (strafe_speed
		+ checkRadius))][(int)data->ray.pos.y] == '0')
		data->ray.pos.x += data->ray.dir.y * strafe_speed;
	if(data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y - data->ray.dir.x
		* (strafe_speed + checkRadius))] == '0')
		data->ray.pos.y -= data->ray.dir.x * strafe_speed;
}