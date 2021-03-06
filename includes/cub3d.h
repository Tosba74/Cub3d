/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:09:32 by bmangin           #+#    #+#             */
/*   Updated: 2021/07/08 15:58:49by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define NORTH 1
# define SOUTH 0
# define EAST 2
# define WESH 3

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_Q 12
# define KEY_E 14
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ENTER 36
# define KEY_SPACE 49
# define KEY_ESC 53

# define MOV_UP 0b00000001
# define MOV_DOWN 0b00000010
# define MOV_LEFT 0b00000100
# define MOV_RIGHT 0b00001000
# define TURN_LEFT 0b00010000
# define TURN_RIGHT 0b01000000

# define SPEED 0.1
# define SPEEDTURN 0.05

# define X_RES 1200
# define Y_RES 800

# include <errno.h>
# include <math.h>
# include <fcntl.h>

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"

// LIST SPRITE
typedef struct s_lst
{
	float	x;
	float	y;
	int		id;
	void	*next;
}			t_lst;

// SPRITES VAR
typedef struct s_sprite
{
	float	sprite_x;
	float	sprite_y;
	float	invdet;
	float	transform_x;
	float	transform_y;
	int		screen_x;
	int		sprite_w;
	int		sprite_h;
	int		start_draw_x;
	int		start_draw_y;
	int		end_draw_x;
	int		end_draw_y;
	int		text_x;
	int		text_y;
	int		d;
	char	*road;
}				t_sprite;

// COLLUMN PXL
typedef struct s_col
{
	int		x;
	int		start;
	int		size_max;
	int		color;
}			t_col;

// IMAGE
typedef struct s_img
{
	char	*road;
	void	*img;
	int		*addr;
	int		w;
	int		h;
	int		endian;
	int		bytes;
	int		sizeline;
}			t_img;

// WALL_SIZE
typedef struct s_wall
{
	int		start;
	int		stop;
	int		height;
}			t_wall;

//TEXTURES
typedef struct s_texture
{
	t_img	cardino[4];
	t_img	sprite[6];
	t_wall	wall;
	float	wallX;
	float	step;
	float	text_pos;
	int		text_width;
	int		text_height;
	int		text_num;
	int		text_x;
	int		text_y;
	int		f[3];
	int		c[3];
	int		floor;
	int		ceiling;
}			t_texture;

// RAY
typedef struct s_ray
{
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
	float	cameraX;
	float	rayDirX;
	float	rayDirY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	float	perpWallDist;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	char	camera;
}			t_ray;

// WINDOWS
typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	int		keypress;
}			t_win;

// MAP
typedef struct s_map
{
	char	**map;
	int		line;
	int		collumn;
	int		nb_player;
	int		nb_sprite;
}			t_map;

//ALL
typedef struct s_global
{
	t_map		map;
	t_win		win;
	t_ray		ray;
	t_texture	tex;
	t_sprite	sprite;
	t_lst		*lst;
	int			time;
	int			zbuffer[X_RES];
}				t_g;

// test.c
void		ft_print_map(t_g g);
void		ft_print_cardino(t_img img, char *str);
void		ft_print_img(t_g g);
void		ft_print_ray(t_g g);
void		test(t_g g);

// raycasting.c
float		ft_dda(t_g *g, int x_win);

// draw_sprite.c
void		draw_sprite(t_g *g, t_ray *ray, t_texture *t);

// draw_screen.c
void		draw_screen(t_g *g);

// move.c
void		move(t_g *g);

// minimap
int			minimap(t_g *g);

// proc_win.c
int			close_window(t_g *g);
int			key_deal(int key, void *param);
int			key_death(int key, void *param);
int			update(void *param);

// read_map.c
void		ft_complet_data(t_g *g, char *line);
void		ft_complet_map(t_g *g, char *line, int fd, int ret);

// init_global.c
void		ft_init_player(t_ray *ray, t_map *map, char *line, int i);
void		ft_init_global(t_g *global);

// sprite_tools.c
void		lstadd_frt(t_lst **lst, t_lst *new);
t_lst		*lst_new(float x, float y, int id);
void		clear_lst(t_lst **lst);
int			in_lst(t_lst *lst, float x, float y);
int			lst_size(t_lst *lst);

// mlx_tools.c
void		my_pixel_put(t_win *win, int x, int y, int color);
void		draw_col(t_win *win, t_col col);
void		get_texture(t_g *g);

// tools.c
void		map_flood_fill(char **map, int x, int y);
void		reset_map(char **map);
void		skip_space_eol(char *s);
int			check_extention(char *s, char *ext);
int			iscardino(t_g *g, char *s, int nb);
int			is_wall(t_g g, int x, int y);

// main.c
void		ft_err(int err);

// void		draw_line(t_vector p0, t_vector p1, t_g *g, int rgb);
#endif
