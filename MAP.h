//
// Created by max on 5/10/2019.
//

#ifndef RESERACT_MAP_H
#define RESERACT_MAP_H

#endif //RESERACT_MAP_H

#include <SDL2/SDL.h>

const int height_of_map = 1000;
const int width_of_map = 1000;

const int cells_in_row = 25;
const int cells_in_column = 25;

const int frame_size = 26;
const int cell_size = 24;

const int life = 1;
const int not_life = 0;

typedef unsigned char uc;

uc **get_new_map (uc **map);
void create_map (uc **map);
void save_game (uc **map) ;
void load_game (uc **map) ;
void delete_map(uc **map);

void draw_map(SDL_Renderer *renderer , uc **map , int cursor_column , int cursor_row) ;

int check_neighbours_left(uc **map, int j, int i);
int check_neighbours_up(uc **map, int j, int i);
int check_neighbours_down(uc **map, int j, int i);
int check_neighbours_right(uc **map, int j, int i);
int check_neighbours_inside(uc **map, int j, int i);
int get_counter(uc **map, int i, int j);

