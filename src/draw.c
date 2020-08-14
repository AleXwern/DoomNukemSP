/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/13 22:24:37 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	draw_sky(t_wolf *wlf, int scan)
{
	int		i;

	if (scan >= WINX)
		scan -= WINX;
	i = 0;
	while (i < wlf->start)
	{
		wlf->VRAMMain[WINY * wlf->x + i] = 0x0f8c3bff;
		/*wlf->VRAMMain[RINX * i + (wlf->x * 3)] = 31;
		wlf->VRAMMain[RINX * i + (wlf->x * 3) + 1] = 14;
		wlf->VRAMMain[RINX * i + (wlf->x * 3) + 2] = 1;*/
		i++;
	}
}

void	draw_stripe(t_wolf *wlf)
{
	while (wlf->start <= wlf->end)
	{
		wlf->VRAMMain[WINY * wlf->x + wlf->start] = wlf->testcolor;
		/*wlf->VRAMMain[RINX * wlf->start + (wlf->x * 3)] = B(wlf->testcolor);
		wlf->VRAMMain[RINX * wlf->start + (wlf->x * 3) + 1] = G(wlf->testcolor);
		wlf->VRAMMain[RINX * wlf->start + (wlf->x * 3) + 2] = R(wlf->testcolor);
		*/
		wlf->start++;
	}
}

void	wall_stripe(t_wolf *wlf)
{
	//wlf->testcolor = 0x22a800;
	draw_sky(wlf, wlf->sbox + wlf->x);
	draw_stripe(wlf);
	draw_floor(wlf, wlf->start);
}
