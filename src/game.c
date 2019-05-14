#include "game.h"
#include <stdlib.h>
#include <stdio.h>

const char empty[5][50] = {
			   "++++++++++",
			   "+        +",
			   "+        +",
			   "+        +",
			   "++++++++++"
};

const char red[5][50] = {
			 "++++++++++",
			 "+  \e[0;31m++++\e[m  +",
			 "+ \e[0;31m+\e[m    \e[0:31m+\e[m +",
			 "+  \e[0;31m++++\e[m  +",
			 "++++++++++"
};

const char yellow[5][50] = {
			    "++++++++++",
			    "+  \e[1;33m++++\e[m  +",
			    "+ \e[1;33m+\e[m    \e[1;33m+\e[m +",
			    "+  \e[1;33m++++\e[m  +",
			    "++++++++++"
};

t_game	*init_game()
{
  t_game	*game;

  if ((game = malloc(sizeof(*game))) == 0)
    {
      return (0);
    }
  game->is_continue = 1;
  game->grid = 0;
  game->players = 0;
  game->nb_player = NB_PLAYERS;
  game->error = 0;
  return (game);
}

void	init_grid(t_game *game, int width, int height)
{
  t_grid	*grid;
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((grid = malloc(sizeof(*grid))) == 0)
    {
      return;
    }
  grid->width = width;
  grid->height = height;
  grid->mask = 0;
  if ((grid->mask = malloc(sizeof(grid->mask) * (width + 1))) == 0)
    {
      return;
    }
  while (i < width)
    {
      if ((grid->mask[i] = malloc(sizeof(*grid->mask) * (height + 1))) == 0)
	{
	  return;
	}
      while (j < height)
	{
	  grid->mask[i][j] = TOKEN_EMPTY;
	  j++;
	}
      grid->mask[i][j] = 0;
      i++;
      j = 0;
    }
  grid->mask[i] = 0;
  game->grid = grid;
}

int	insert_in_column(t_game *game, int token, int column)
{
  int	i;
  int	j;

  i = column;
  j = 0;
  if (i >= game->grid->width)
    {
      return (0);
    }
  while (j < game->grid->height && game->grid->mask[j][i] == TOKEN_EMPTY)
    j++;
  game->grid->mask[j - 1][i] = token;
  return (1);
}

void	init_players(t_game *game)
{
  t_player	*players;

  if ((players = malloc(sizeof(*players) * (game->nb_player))) == 0)
    {
      return;
    }
  players[0].win = 0;
  players[1].win = 0;
  game->players = players;
}

int	is_align(t_game *game, int nb, int token)
{
  int	**mask;
  int	i;
  int	j;
  int	count;
  int	align;

  i = 0;
  j = 0;
  mask = game->grid->mask;
  while (i < game->grid->height)
    {
      while (j < game->grid->width)
	{
	  align = 1;
	  count = 0;
	  while (count < nb && (count + i) < game->grid->height)
	    {
	      if (mask[i + count][j] != token)
		{
		  align = 0;
		}
	      count++;
	    }
	  if (align && count == 4)
	    return (align);
	  count = 0;
	  align = 1;
	  while (count < nb && (count + j) < game->grid->width)
	    {
	      if (mask[i][j + count] != token)
		{
		  align = 0;
		}
	      count++;
	    }
	  if (align && count == 4)
	    return (align);
	  count = 0;
	  align = 1;
	  while (count < nb && (count + j) < game->grid->width && (count + i) < game->grid->height)
	    {
	      if (mask[i + count][j + count] != token)
		{
		  align = 0;
		}
	      count++;
	    }
	  if (align && count == 4)
	    return (align);     	  
	  count = 0;
	  align = 1;
	  while (count < nb && (j - count) >= 0 && (i + count) < game->grid->height)
	    {
	      if (mask[i + count][j - count] != token)
	  	{
	  	  align = 0;
	  	}
	      count++;
	    }
	  if (align && count == 4)
	    return (align);
	  j++;
	}
      i++;
      j = 0;
    }
  return (0);
}

void	render(t_game *game)
{
  int		i;
  int		j;
  int		k;
  t_grid	*grid;

  grid = game->grid;
  i = 0;
  j = 0;
  k = 0;
  while (i < grid->height)
    {
      k = 0;
      while (k < 5)
	{
	  j = 0;
	  while (j < grid->width)
	    {
	      if (grid->mask[i][j] == TOKEN_EMPTY)
		{
		  printf("%s", empty[k]);
		}
	      else if (grid->mask[i][j] == TOKEN_RED)
		{
		  printf("%s", red[k]);
		}
	      else if (grid->mask[i][j] == TOKEN_YELLOW)
		{
		  printf("%s", yellow[k]);
		}
	      j++;
	    }
	  printf("\n");
	  k++;	  
	}
      i++;
    }
  printf("\n");
}

void	free_game(t_game *game)
{
  int	n;

  n = 0;
  while (n < game->grid->height)
    {
      free(game->grid->mask[n]);
      n++;
    }
  free(game->grid);
  free(game->players);
  free(game);
}
