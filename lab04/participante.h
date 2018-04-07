typedef struct{
	int i, h_current, h_max;
} Player;

Player * start_player(int i, int h);

Player * modify_player(Player * p, int h);

void delete_player(Player * p);
