/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brulutaj <brulutaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:37:17 by chsassi           #+#    #+#             */
/*   Updated: 2024/11/19 22:13:38 by brulutaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/time.h>
# include "mlx.h"
# include "mlx_int.h"
# include <X11/Xlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include "libft.plus/includes/libft.h"

# define BASE_HEX "0123456789abcdef"
# define PLAYER_TEXTURE "./src/textures/xpms/player.xpm"
# define PI 3.14159265358979323846
# define SCREEN_W 1080
# define SCREEN_H 720
# define ROT 0.050
# define MINIMAP_TILE 6
# define MINIMAP_STROKE 2

typedef enum s_color
{
	RED = 0x00ff0000,
	GREEN = 0x0000ff00,
	BLUE = 0x000000ff,
	WHITE = 0x00ffffff,
	BLACK = 0x00000000,
	GREY = 0x00a9a9a9
}	t_color;

typedef enum s_error
{
	ARG_ERROR,
	MALLOC_E,
	OPEN_E,
	MISSING_EL,
	MISSING_MAP,
	ERROR_MAP,
	OPEN_MAP,
	INCORRECT_CHAR,
	NO_PLAYER,
	MULTIPLE_PLAYER,
	NOT_PLAYABLE
}	t_error;

typedef struct s_element
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*ceiling;
	char	*floor;
}			t_element;

typedef struct s_map
{
	char	**map;
	int		rows;
}			t_map;

typedef struct s_draw
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
	int		ceiling;
	int		floor;
	int		size_texture;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
}			t_draw;

typedef struct s_event
{
	bool	walk_forw;
	bool	walk_back;
	bool	walk_left;
	bool	walk_right;
	bool	show_minimap;
	bool	show_legend;
	bool	rotate_left;
	bool	rotate_right;
}			t_event;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_player
{
	t_point		pos;
	t_point		dir;
	t_point		plane;
	double		angle;
	double		velox;
	double		velox_mult;
	bool		collision;
}				t_player;

typedef struct s_algo
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	double		camera_x;
	bool		collision;
	bool		side_collision;
	int			width;
	int			height;
	int			draw_start;
	int			draw_end;
	int			line_height;
	t_point		hit_point;
}				t_algo;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img		*frame;
	t_img		*weapon;
}				t_mlx;

typedef struct s_all
{
	double		time;
	double		old_time;
	t_draw		texture;
	t_map		map;
	t_event		event;
	t_algo		algo;
	t_mlx		window;
	t_player	player;
}				t_all;

// ----Parsing----

	// Get_elements
void		complete_gnl(int fd);
int			find_start(char *texture, char *flag);
char		*get_path_texture(char	**texture, char *flag);
char		**get_mtx_elements(char *name_file);
t_element	get_elements(char *name_file, t_element info_elements);

	// Get_map
bool		empty_line(char *str);
bool		is_external_row(char *str);
char		**lst_to_mtx(t_list *head);
char		*get_map_rows(int fd, int flag);
char		**get_map(char *name_file);

	// Get_player
t_player	set_pos_angle(int x, int y, int pov, t_player player);
void		set_info_player(int x, int y, int pov, t_all *pAll);

	// Get_rgb_values
bool		check_fc_value(char *str);
int			*rgb_values(char *s);
int			get_rgb(int *rgb_values);
bool		get_rgb_colors(t_element info_element, t_all *pAll);

	// Get_texture_and_colors
int			*rgb_values(char *s);
int			get_rgb(int *rgb_values);
bool		get_rgb_colors(t_element info_element, t_all *pAll);
bool		load_wall_textures(t_element info_elements, t_all *pAll);

	// Init_all
bool		get_texture_and_colors(char *name_file, t_all *pAll);
void		get_player_info(t_map *map, t_all *pAll);
bool		get_map_info(char *map_file, t_all *pAll);
void		init_algo(t_all *pAll);
bool		init_all(t_all *pAll, char *name_file);

	// Playability
bool		is_player_inside_map(char **map, int row, int col);
bool		correct_char_set(char **map);
bool		is_surrounded(char **map, int row, int col);
bool		closed_map(char **map);
bool		is_map_playable(char **map);

	// Utils
bool		exists(char **map, int row, int col);
bool		is_char_set(int c);
bool		extern_char(int c);
bool		is_inside_col(int col, int len);
bool		is_player(int c);

// ----Print----

	// Print_error
void		error(int flag);

// ----Game----
int			game_loop(t_all *pAll);
int			start_game(t_all *pAll, char *name_file);

	// Events
int			on_key_press(int key, t_all *ptr);
int			on_key_release(int key, t_all *ptr);

	// Movement
int			rotate_player(t_all *cubed);
int			rot_action(t_all *cubed, double old_dirx,
				double old_planex, double rot);
bool		is_new_x_valid(t_all *cubed, double new_x);
bool		is_new_y_valid(t_all *cubed, double new_y);
void		calc_lateral_move(t_all *cubed, double *dx, double *dy);
void		calc_forward_backward_move(t_all	*cubed, double *dx, double *dy);
void		get_new_position(t_all *cubed, double *new_x, double *new_y);
int			move_player(t_all *cubed);

	// Minimap
char		get_map_char(t_all *pAll, int x, int y);
void		draw_minimap(t_all *ptr);

// ----Utils----

	// Free
void		free_element(t_element *pElement);
void		free_map(t_map *pMap);
int			quit_game(t_all *pAll);

	// Drawing
void		draw_legend(t_all *pAll);
t_img		*load_texture(void *mlx, char *file_path);
void		render_weapon(t_all *pAll, int weapon_x, int weapon_y);
bool		draw_pixel(t_all *pAll, int x, int y, int color);
void		draw_rectangle(t_all *pAll, t_point start, t_point end, int color);
void		draw_line(t_all *pAll, int col);

	// Algo
void		dda(t_all *pAll);
void		calculate_ray(t_all *pAll);
void		check_perp_distance(t_all *pAll);
void		set_info_line(t_all *pAll, int col);
void		raycast(t_all *pAll);
size_t		create_trgb(char *data, int offset);
void		render_wall_texture(t_all *pAll, t_point start,
				t_point end, t_img *texture);
void		check_orientation(t_all *pAll, t_point start, t_point end);
void		determine_x_coord(t_all *pAll, t_img *texture);
void		calculate_delta_dist(t_all *pAll);
void		calculate_hit_point(t_all *pAll);
void		calculate_perp_distance(t_all *pAll);
void		calculate_ray(t_all *pAll);

#endif