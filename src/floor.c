/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 01:20:40 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/13 22:24:46 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	draw_floor(t_wolf *wlf, int y)
{
	while (y < WINY)
	{
		wlf->VRAMMain[WINY * wlf->x + y] = 0x3d96f5ff;
		/*wlf->VRAMMain[RINX * y + (wlf->x * 3)] = 1;
		wlf->VRAMMain[RINX * y + (wlf->x * 3) + 1] = 13;
		wlf->VRAMMain[RINX * y + (wlf->x * 3) + 2] = 6;*/
		y++;
	}
}

void	render_floor(t_wolf *wlf, int y)
{
	y = WINY / 2;
	wlf->raydx0 = wlf->dirx - wlf->planex;
	wlf->raydy0 = wlf->diry - wlf->planey;
	wlf->raydx1 = wlf->dirx + wlf->planex;
	wlf->raydy1 = wlf->diry + wlf->planey;
	while (y < WINY)
	{
		wlf->pos = y - WINY / 2;
		wlf->posz = WINY * 0.5;
		wlf->rowdist = wlf->posz / wlf->pos;
		wlf->flstepx = wlf->rowdist * (wlf->raydx1 - wlf->raydx0) / WINX;
		wlf->flstepy = wlf->rowdist * (wlf->raydy1 - wlf->raydy0) / WINX;
		wlf->floorx = wlf->posx + wlf->rowdist * wlf->raydx0;
		wlf->floory = wlf->posy + wlf->rowdist * wlf->raydy0;
		draw_floor(wlf, y);
		y++;
	}
}

void	move_skybox(t_wolf *wlf)
{
	double	adjy;

	wlf->sbox = 0;
	adjy = (wlf->diry + 1.0) / 2;
	if (wlf->dirx > 0)
	{
		wlf->sbox = WINX * adjy;
	}
	else
	{
		wlf->sbox = WINX - WINX * adjy;
	}
}
