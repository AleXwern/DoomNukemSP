/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/14 01:15:51 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	key_defaults(t_wolf *wlf)
{
	wlf->keydown = 0;
	wlf->keyleft = 0;
	wlf->keyright = 0;
	wlf->keyup = 0;
}

void	wolf_default(t_wolf *wlf)
{
	wlf->flr = 0;
	wlf->posx = 2.5;
	wlf->posy = 2.5;
	wlf->dirx = 1.0;
	wlf->diry = 0.0;
	wlf->planex = 0.0;
	wlf->planey = 0.66;
	wlf->rotsp = 0.03;
	wlf->movsp = 0.04;
	wlf->rng = 0.0;
	wlf->texbool = 1;
	wlf->sbox = WINX / 2;
	wlf->mxflr--;
	wlf->cur = 0;
	wlf->sel = -1;
	wlf->plr = 0;
	wlf->plrck = 0;
	wlf->cycle = &render;
	wlf->threads = 3;
	wlf->syssmg[0] = ft_strdup("You encountered a strong beast!");
	wlf->syssmg[1] = ft_strdup("What will you do?");
	key_defaults(wlf);
}

void	error_out(char *msg, t_wolf *wlf, int y)
{
	printf("Feedback: %s", msg);
	while (aptMainLoop())
	{
		scanKeys();
		if (keysDown() == KEY_A)
			break;
	}
	gfxExit();
	exit(0);
	/*
	if (wlf->syssmg[0])
	{
		free(wlf->syssmg[0]);
		free(wlf->syssmg[1]);
	}
	if (wlf->gfx)
		destroy_gfx(wlf, -1);
	if (y > 0)
		free_layer(wlf, wlf->flr, -1, y);
	if (wlf->map)
		free_map(wlf, -1, -1);
	exit(0);*/
}

void	setup(t_wolf *wlf)
{
	int				key;
	circlePosition	pos;

	wolf_default(wlf);
	if (wlf->map[0][(int)wlf->posy][(int)wlf->posx] != 1)
		error_out(SPW_ERROR, wlf, 0);
	while (aptMainLoop())
	{
		scanKeys();
		key_hold(hidKeysDown(), wlf);
		key_release(hidKeysUp(), wlf);
		hidCircleRead(&pos);
		move(wlf);
		render(wlf);
		printf("Dir %f %f\nPos %f %f\nKey %ld %ld\nCircle %d %d\n---\n", wlf->dirx, wlf->diry, wlf->posx, wlf->posy, hidKeysDown(), hidKeysUp(), pos.dx, pos.dy);
		gspWaitForVBlank();
	}
}

int		main(int ac, char **av)
{
	t_wolf	*wlf;

	if (!(wlf = (t_wolf*)malloc(sizeof(t_wolf))))
		error_out(WLF_ERROR, wlf, 0);
	ft_bzero(wlf, sizeof(t_wolf));
	wlf->tile = 3;
	wlf->mxflr = 1;
	wlf->winb = 1;
	gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
	gfxSetDoubleBuffering(GFX_TOP, false);
	wlf->VRAMMain = (int*)gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	consoleInit(GFX_BOTTOM, NULL);
	comp_map(wlf, av[3]);
	//comp_gfx(wlf, 0);
	setup(wlf);
	return (0);
}
