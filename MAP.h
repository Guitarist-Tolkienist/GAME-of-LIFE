//
// Created by max on 5/10/2019.
//

#ifndef RESERACT_MAP_H
#define RESERACT_MAP_H

#endif //RESERACT_MAP_H

#include <SDL2/SDL.h>

const int HEIGHT_OF_MAP = 1000;
const int WIDTH_OF_MAP = 1000;

const int CELLS_IN_ROW = 40;
const int CELLS_IN_COLUMN = 40;

const int FRAME_SIZE = 25;
const int CELL_SIZE = 23;

const int LIFE = 1;
const int NOT_LIFE = 0;

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

