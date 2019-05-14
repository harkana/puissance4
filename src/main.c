#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "readline.h"
#include "empty.h"

int	main(void)
{
  t_game	*game;
  int		n;
  char		*line;
  
  n = 0;
  if ((game = init_game()) == 0)
    {
      return (EXIT_FAILURE);
    }
  init_grid(game, DEFAULT_WIDTH, DEFAULT_HEIGHT);
  init_players(game);
  while (n < game->nb_player)
    {      
      printf("Player %d :\n", n + 1);
      printf("Entrez votre nom : ");
      fflush(stdout);
      line = readline();
      if (!is_empty(line))
	{
	  game->players[n].name = strdup(line);
	  game->players[n].token = n + 2;      
	  n++;
	}
      free(line);
    }
  while (game->is_continue)
    {
      n = 0;
      while (n < game->nb_player && game->is_continue)
	{
	  render(game);
	  printf("player %s, it's your turn\n", game->players[n].name);
	  line = readline();
	  if (strlen(line) == 0 || !insert_in_column(game, game->players[n].token, atoi(line) - 1))
	    {
	      printf("replay :\n");
	      n--;
	    }
	  free(line);
	  if (is_align(game, 4, game->players[n].token))
	    {
	      game->players[n].win = 1;
	      game->is_continue = 0;
	    }
	  n++;
	}
    }
  n = 0;
  while (n < game->nb_player)
    {
      if (game->players[n].win == 1)
	{
	  render(game);
	  printf("%s has win\n", game->players[n].name);
	}
      n++;
    }
  free_game(game);
  return (0);
}
