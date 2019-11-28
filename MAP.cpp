//
// Created by max on 5/10/2019.
//

#include "MAP.h"
#include "iostream"
#include "fstream"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

uc **get_new_map (uc **map) {
    uc **new_map = new uc*[CELLS_IN_ROW];
    int count = 0;

    create_map(new_map);

    for (int i = 0; i < CELLS_IN_ROW; i++) {
        for (int j = 0; j < CELLS_IN_COLUMN; j++) {

            count = get_counter(map, i , j);

            if (count == 3) {
                if (map[i][j] > 0) {
                    if (map[i][j] < 250) {
                        new_map[i][j] = map[i][j] + 1;
                    } else {
                        new_map[i][j] = 250;
                    }
                } else {
                    new_map[i][j] = LIFE;
                }
            }
            if (map[i][j] > 0 && count == 2) {
                if (map[i][j] > 0) {
                    if (map[i][j] < 250) {
                        new_map[i][j] = map[i][j] + 1;
                    } else {
                        new_map[i][j] = 250;
                    }
                } else {
                    new_map[i][j] = LIFE;
                }
            }

        }
    }

    delete_map(map);

    return new_map;
}

void save_game (uc **map) {

    ofstream fout;

    fout.open("LIFE.bin", ios_base::trunc | ios_base::binary);

    if (fout.is_open()) {

        for (int i = 0 ; i < CELLS_IN_ROW ; i++) {
            for (int j = 0 ; j < CELLS_IN_COLUMN ; j++) {
                fout.write((char *) &map[i][j] , sizeof(unsigned char));
            }
        }

        fout.close();
    }
}

void load_game (uc **map) {
    ifstream fin("LIFE.bin" , std::ios::binary);

    for (int i = 0 ; i < CELLS_IN_ROW ; i++) {

        for (int j = 0 ; j < CELLS_IN_COLUMN ; j++) {
            fin.read((char *)&map[i][j] , sizeof(unsigned char));
        }

    }

    fin.close();

}

void create_map (uc **map) {

    for (int i = 0; i < CELLS_IN_ROW; i++) {
        map[i] = new uc[CELLS_IN_COLUMN];
    }

    for (int i = 0; i < CELLS_IN_ROW; i++) {
        for (int j = 0; j < CELLS_IN_COLUMN; j++) {
            map[i][j] = NOT_LIFE;
        }
    }
}

void delete_map(uc **map) {
    for(int i = 0 ; i < CELLS_IN_ROW ; i++) {
        delete[] map[i];
    }

    delete(map);
}

void put_cell (SDL_Renderer *renderer, uc **map, int i, int  j, int x, int y, bool selected) {
    SDL_Rect cell, frame;

    int Color;

    cell.x = x;
    cell.y = y;
    cell.w = CELL_SIZE;
    cell.h = CELL_SIZE;

    frame.x = x - 1;
    frame.y = y - 1;
    frame.w = FRAME_SIZE;
    frame.h = FRAME_SIZE;

    if (selected) {
        SDL_SetRenderDrawColor(renderer , 250 , 0 , 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer , 2 , 16 , 43, 255);
    }

    SDL_RenderDrawRect(renderer, &frame);

    if (map[i][j] > 0) {
        Color = min(5*map[i][j], 255);
        SDL_SetRenderDrawColor(renderer, Color, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    SDL_RenderFillRect(renderer, &cell);
}

int check_neighbours_up(uc **map, int j, int i) {
    int counter = 0;

    if (j == 0) {
        // map[-1][-1]
        if (map[CELLS_IN_ROW - 1][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[-1][0]
        if (map[CELLS_IN_ROW - 1][0]) {
            counter++;
        }
        // map[-1][1]
        if (map[CELLS_IN_ROW - 1][1]) {
            counter++;
        }
        // map[0][-1]
        if (map[0][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[0][+1]
        if (map[0][1]) {
            counter++;
        }
        // map[+1][-1]
        if (map[1][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[+1][0]
        if (map[1][0]) {
            counter++;
        }
        // map[+1][+1]
        if (map[1][1]) {
            counter++;
        }
    } else if (j == (CELLS_IN_COLUMN - 1)) {
        // map[-1][-1]
        if (map[CELLS_IN_ROW - 1][CELLS_IN_COLUMN - 2]) {
            counter++;
        }
        // map[-1][0]
        if (map[CELLS_IN_ROW - 1][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[-1][1]
        if (map[CELLS_IN_ROW - 1][0]) {
            counter++;
        }
        // map[0][-1]
        if (map[0][CELLS_IN_COLUMN - 2]) {
            counter++;
        }
        // map[0][+1]
        if (map[0][0]) {
            counter++;
        }
        // map[+1][-1]
        if (map[1][CELLS_IN_COLUMN - 2]) {
            counter++;
        }
        // map[+1][0]
        if ( map[1][CELLS_IN_COLUMN - 1] ) {
            counter++;
        }
        // map[+1][+1]
        if (map[1][0]) {
            counter++;
        }
    } else {
        // map[-1][-1]
        if (map[CELLS_IN_ROW - 1][j - 1]) {
            counter++;
        }
        // map[-1][0]
        if (map[CELLS_IN_ROW - 1][j]) {
            counter++;
        }
        // map[-1][+1]
        if (map[CELLS_IN_ROW - 1] [j + 1]) {
            counter++;
        }
        // map[0][-1]
        if (map[i][j - 1]) {
            counter++;
        }
        // map[0][+1]
        if (map[i][j + 1]) {
            counter++;
        }
        // map[+1][-1]
        if (map[i + 1][j - 1]) {
            counter++;
        }
        // map[+1][0]
        if (map[i + 1][j]) {
            counter++;
        }
        // map[+1][+1]
        if (map[i + 1][j + 1]) {
            counter++;
        }
    }

    return counter;
}
int check_neighbours_left(uc **map, int j, int i) {
    int counter = 0;

    // map[-1][-1]
    if (map[i - 1][CELLS_IN_COLUMN - 1]) {
        counter++;
    }
    // map[-1][0]
    if (map[i - 1][j]) {
        counter++;
    }
    // map[-1][+1]
    if (map[i - 1][j + 1]) {
        counter++;
    }
    // map[0][-1]
    if (map[i][CELLS_IN_COLUMN - 1]) {
        counter++;
    }
    // map[0][+1]
    if (map[i][j + 1]) {
        counter++;
    }
    // map[+1][-1]
    if (map[i + 1][CELLS_IN_COLUMN - 1]) {
        counter++;
    }
    // map[+1][0]
    if (map[i + 1][j]) {
        counter++;
    }
    // map[+1][+1]
    if (map[i + 1][j + 1]) {
        counter++;
    }

    return counter;
}
int check_neighbours_down(uc **map, int j, int i) {
    int counter = 0;

    if ( j == 0 ) {
        // map[-1][-1]
        if (map[CELLS_IN_ROW - 2][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[-1][0]
        if (map[i - 1][j]) {
            counter++;
        }
        // map[-1][+1]
        if (map[i - 1] [j + 1]) {
            counter++;
        }
        // map[0][-1]
        if (map[CELLS_IN_ROW - 1][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[0][+1]
        if (map[i][j + 1]) {
            counter++;
        }
        // map[+1][-1]
        if (map[0][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[+1][0]
        if (map[0][0]) {
            counter++;
        }
        // map[+1][+1]
        if (map[0][1]) {
            counter++;
        }
    } else if ( j == (CELLS_IN_COLUMN - 1) ) {
        // map[-1][-1]
        if (map[CELLS_IN_ROW - 2][CELLS_IN_COLUMN - 2]) {
            counter++;
        }
        // map[-1][0]
        if (map[i - 1][j]) {
            counter++;
        }
        // map[-1][+1]
        if (map[CELLS_IN_ROW - 2][0]) {
            counter++;
        }
        // map[0][-1]
        if (map[CELLS_IN_ROW - 1][CELLS_IN_COLUMN - 2]) {
            counter++;
        }
        // map[0][+1]
        if (map[CELLS_IN_ROW - 1][0]) {
            counter++;
        }
        // map[+1][-1]
        if (map[0][CELLS_IN_COLUMN - 2]) {
            counter++;
        }
        // map[+1][0]
        if (map[CELLS_IN_ROW - 1][CELLS_IN_COLUMN - 1]) {
            counter++;
        }
        // map[+1][+1]
        if (map[0][0]) {
            counter++;
        }
    } else {
        // map[-1][-1]
        if (map[i - 1][j - 1]) {
            counter++;
        }
        // map[-1][0]
        if (map[i - 1][j]) {
            counter++;
        }
        // map[-1][+1]
        if (map[i - 1][j + 1]) {
            counter++;
        }
        // map[0][-1]
        if (map[i][j - 1]) {
            counter++;
        }
        // map[0][+1]
        if (map[i][j + 1]) {
            counter++;
        }
        // map[+1][-1]
        if (map[0][j - 1]) {
            counter++;
        }
        // map[+1][0]
        if (map[0][j]) {
            counter++;
        }
        // map[+1][+1]
        if (map[0][j + 1]) {
            counter++;
        }
    }

    return counter;
}
int check_neighbours_right(uc **map, int j, int i) {
    int counter = 0;

    // map[-1][-1]
    if (map[i - 1][j - 1]) {
        counter++;
    }
    // map[-1][0]
    if (map[i - 1][j]) {
        counter++;
    }
    // map[-1][+1]
    if (map[i - 1][0]) {
        counter++;
    }
    // map[0][-1]
    if (map[i][j - 1]) {
        counter++;
    }
    // map[0][+1]
    if (map[i][0]) {
        counter++;
    }
    // map[+1][-1]
    if (map[i + 1][j - 1]) {
        counter++;
    }
    // map[+1][0]
    if (map[i + 1][j]) {
        counter++;
    }
    // map[+1][+1]
    if (map[i + 1][0]) {
        counter++;
    }

    return counter;
}
int check_neighbours_inside(uc **map, int j, int i) {
    int counter = 0;
    // map[-1][-1]
    if (map[i - 1][j - 1]) {
        counter++;
    }
    // map[-1][0]
    if (map[i - 1][j]) {
        counter++;
    }
    // map[-1][+1]
    if (map[i - 1][j + 1]) {
        counter++;
    }
    // map[0][-1]
    if (map[i][j - 1]) {
        counter++;
    }
    // map[0][+1]
    if (map[i][j + 1]) {
        counter++;
    }
    // map[+1][-1]
    if (map[i + 1][j - 1]) {
        counter++;
    }
    // map[+1][0]
    if (map[i + 1][j]) {
        counter++;
    }
    // map[+1][+1]
    if (map[i + 1][j + 1]) {
        counter++;
    }

    return counter;
}

int get_counter(uc **map, int i, int j) {
    int count = 0;

    if (i == 0) {
        count = check_neighbours_up(map, j, i);
    } else if (j == 0 && i != (CELLS_IN_ROW - 1) ) {
        count = check_neighbours_left(map, j, i);
    } else if (i == CELLS_IN_ROW - 1) {
        count = check_neighbours_down(map, j, i);
    } else if (j == CELLS_IN_COLUMN - 1) {
        count = check_neighbours_right(map, j, i);
    } else {
        count = check_neighbours_inside(map, j, i);
    }

    return count;
}
void draw_map(SDL_Renderer *renderer, uc **map, int cursor_column, int cursor_row) {

    int R_back = 11;
    int G_back = 16;
    int B_back = 43;

    SDL_SetRenderDrawColor(renderer , R_back , G_back , B_back , 255);

    SDL_RenderClear(renderer);

    for (int y = 0 , i = 0; i < CELLS_IN_ROW ; i++ , y += FRAME_SIZE) {
        for (int x = 0 , j = 0 ; j < CELLS_IN_COLUMN ; j++ , x += FRAME_SIZE) {

            put_cell(renderer, map, i, j, x, y, i == cursor_row && j == cursor_column);
        }
    }

    SDL_RenderPresent(renderer);
}
