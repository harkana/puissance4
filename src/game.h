#ifndef _GAME_H_
# define _GAME_H_

#define TOKEN_EMPTY 1
#define TOKEN_YELLOW 2
#define TOKEN_RED 3
#define DEFAULT_WIDTH 12
#define DEFAULT_HEIGHT 12
#define NB_PLAYERS 2

typedef struct s_player {
  char	*name;
  int	win;
  int	token;  
}	       t_player;

typedef struct s_grid {
  int	width;
  int	height;
  int	**mask;
}	       t_grid;

typedef struct s_game {
  int		is_continue;
  t_grid	*grid;
  t_player	*players;
  int		nb_player;
  char		*error;
} t_game;


t_game	*init_game();
void	init_grid(t_game *, int, int);
void	init_players(t_game *);

void	render(t_game *);

int     is_align(t_game *, int, int);

int	insert_in_column(t_game *, int, int);

void	free_game(t_game *);
#endif
