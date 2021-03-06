/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:25:29 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/14 01:20:31 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

#define	THREAD	5

void	ray_check(t_wolf *wlf)
{
	wlf->hit = 0;
	while (wlf->hit == 0)
	{
		if (wlf->sidedx < wlf->sidedy)
		{
			wlf->sidedx += wlf->deltadx;
			wlf->mapx += wlf->stepx;
			wlf->side = 0;
		}
		else
		{
			wlf->sidedy += wlf->deltady;
			wlf->mapy += wlf->stepy;
			wlf->side = 1;
		}
		if (wlf->map[wlf->flr][wlf->mapy][wlf->mapx] > 1)
			wlf->hit = 1;
	}
}

void	ray_prep(t_wolf *wlf)
{
	wlf->deltadx = fabs(1 / wlf->raydx);
	wlf->deltady = fabs(1 / wlf->raydy);
	if (wlf->raydx < 0)
	{
		wlf->stepx = -1;
		wlf->sidedx = (wlf->posx - wlf->mapx) * wlf->deltadx;
	}
	else
	{
		wlf->stepx = 1;
		wlf->sidedx = (wlf->mapx + 1.0 - wlf->posx) * wlf->deltadx;
	}
	if (wlf->raydy < 0)
	{
		wlf->stepy = -1;
		wlf->sidedy = (wlf->posy - wlf->mapy) * wlf->deltady;
	}
	else
	{
		wlf->stepy = 1;
		wlf->sidedy = (wlf->mapy + 1.0 - wlf->posy) * wlf->deltady;
	}
}

void	rc_init(t_wolf *wlf)
{
	wlf->camx = 2 * wlf->x / (double)(WINX) - 1.0;
	wlf->raydx = wlf->dirx + wlf->planex * wlf->camx;
	wlf->raydy = wlf->diry + wlf->planey * wlf->camx;
	wlf->mapx = (int)wlf->posx;
	wlf->mapy = (int)wlf->posy;
	ray_prep(wlf);
	ray_check(wlf);
	if (wlf->side == 0)
		wlf->walldist = (wlf->mapx - wlf->posx + (1 - wlf->stepx) / 2) /
				wlf->raydx;
	else
		wlf->walldist = (wlf->mapy - wlf->posy + (1 - wlf->stepy) / 2) /
				wlf->raydy;
	if (wlf->walldist < 0.0001)
		wlf->walldist += 0.01;
}

void	t_render(void *ptr)
{
	t_wolf *wlf;

	wlf = (t_wolf*)ptr;
	//wlf->x = -1;
	while (wlf->x < WINX)
	{
		rc_init(wlf);
		wlf->lineh = (int)(WINY / wlf->walldist);
		wlf->start = -wlf->lineh / 2 + WINY / 2;
		if (wlf->start < 0)
			wlf->start = 0;
		wlf->end = wlf->lineh / 2 + WINY / 2;
		if (wlf->end >= WINY)
			wlf->end = WINY - 1;
		if (wlf->side == 1)
			wlf->testcolor = 0x701170ff;
		else
			wlf->testcolor = 0x990909ff;
		wall_stripe(wlf);
		wlf->x += THREAD;
	}
}

void	render(t_wolf *wlf)
{
	t_wolf	cp[THREAD];
	Thread	tr[THREAD];
	int		id;

	id = -1;
	while (++id < THREAD)
	{
		cp[id] = *wlf;
		cp[id].x = id;
		tr[id] = threadCreate(t_render, &cp[id], 4000, 0x3F, -1, false);
	}
	id = -1;
	while (++id < THREAD)
	{
		threadJoin(tr[id], U64_MAX);
		threadFree(tr[id]);
	}
}
