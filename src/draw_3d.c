typedef struct s_player
{
	int	x;
	int y;
	int height;
	float angle;
	float fov;
}	t_player;

#define PI 3.14159
t_player *get_player(int x, int y, char angle)
{
	t_player player;

	player.x = x;
	player.y = y;
	if (angle == 'N')
		player.angle = 0.5 * PI;
	if (angle == "E")
		player.angle = 0;
	if (angle == 'S')
		player.angle = 1.5 * PI;
	if (angle == 'W')
		player.angle = PI;
	player.height = 32;
	player.fov = PI / 3;
}