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

typedef unsigned char uc;

void draw_map(SDL_Renderer *renderer , uc **map , int cursor_column , int cursor_row) ;

int check_neighbours_left(uc  **map , int j , int i) ;
int check_neighbours_up(uc  **map , int j , int i) ;
int check_neighbours_down(uc  **map , int j , int i) ;
int check_neighbours_right(uc  **map , int j , int i) ;
