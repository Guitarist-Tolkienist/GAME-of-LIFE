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
    uc **new_map = new uc*[cells_in_row];
    int count = 0;

    create_map(new_map);

    for (int i = 0; i < cells_in_row; i++) {
        for (int j = 0; j < cells_in_column; j++) {

            count = get_counter(map, i , j);

            if (count == 3) {
                if (map[i][j] > 0) {
                    if (map[i][j] < 250) {
                        new_map[i][j] = map[i][j] + 1;
                    } else {
                        new_map[i][j] = 250;
                    }
                } else {
                    new_map[i][j] = life;
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
                    new_map[i][j] = life;
                }
            }

        }
    }

    delete_map(map);

    return new_map;
}

void save_game (uc **map) {

    ofstream fout;

    fout.open("life.bin", ios_base::trunc | ios_base::binary);

    if (fout.is_open()) {

        for (int i = 0 ; i < cells_in_row ; i++) {
            for (int j = 0 ; j < cells_in_column ; j++) {
                fout.write((char *) &map[i][j] , sizeof(unsigned char));
            }
        }

        fout.close();
    }
}

void load_game (uc **map) {
    ifstream fin("life.bin" , std::ios::binary);

    for (int i = 0 ; i < cells_in_row ; i++) {

        for (int j = 0 ; j < cells_in_column ; j++) {
            if(fin.read((char *)&map[i][j] , sizeof(unsigned char))){

            };
        }

    }

    fin.close();

}

void create_map (uc **map) {

    for (int i = 0; i < cells_in_row; i++) {
        map[i] = new uc[cells_in_column];
    }

    for (int i = 0; i < cells_in_row; i++) {
        for (int j = 0; j < cells_in_column; j++) {
            map[i][j] = not_life;
        }
    }
}

void delete_map(uc **map) {
    for(int i = 0 ; i < cells_in_row ; i++) {
        delete[] map[i];
    }

    delete(map);
}

void put_cell (SDL_Renderer *renderer, uc **map, int i, int  j, int x, int y, bool selected) {
    SDL_Rect cell, frame;

    int Color;

    cell.x = x;
    cell.y = y;
    cell.w = cell_size;
    cell.h = cell_size;

    frame.x = x - 1;
    frame.y = y - 1;
    frame.w = frame_size;
    frame.h = frame_size;

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
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            counter++;
        }
        // map[-1][0]
        if (map[cells_in_row - 1][0]) {
            counter++;
        }
        // map[-1][1]
        if (map[cells_in_row - 1][1]) {
            counter++;
        }
        // map[0][-1]
        if (map[0][cells_in_column - 1]) {
            counter++;
        }
        // map[0][+1]
        if (map[0][1]) {
            counter++;
        }
        // map[+1][-1]
        if (map[1][cells_in_column - 1]) {
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
    } else if (j == (cells_in_column - 1)) {
        // map[-1][-1]
        if (map[cells_in_row - 1][cells_in_column - 2]) {
            counter++;
        }
        // map[-1][0]
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            counter++;
        }
        // map[-1][1]
        if (map[cells_in_row - 1][0]) {
            counter++;
        }
        // map[0][-1]
        if (map[0][cells_in_column - 2]) {
            counter++;
        }
        // map[0][+1]
        if (map[0][0]) {
            counter++;
        }
        // map[+1][-1]
        if (map[1][cells_in_column - 2]) {
            counter++;
        }
        // map[+1][0]
        if ( map[1][cells_in_column - 1] ) {
            counter++;
        }
        // map[+1][+1]
        if (map[1][0]) {
            counter++;
        }
    } else {
        // map[-1][-1]
        if (map[cells_in_row - 1][j - 1]) {
            counter++;
        }
        // map[-1][0]
        if (map[cells_in_row - 1][j]) {
            counter++;
        }
        // map[-1][+1]
        if (map[cells_in_row - 1] [j + 1]) {
            counter++;
        }
        // map[0][-1]
        if (map[i][cells_in_column - 1]) {
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
    if (map[i - 1][cells_in_column - 1]) {
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
    if (map[i][cells_in_column - 1]) {
        counter++;
    }
    // map[0][+1]
    if (map[i][j + 1]) {
        counter++;
    }
    // map[+1][-1]
    if (map[i + 1][cells_in_column - 1]) {
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
        if (map[cells_in_row - 2][cells_in_column - 1]) {
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
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            counter++;
        }
        // map[0][+1]
        if (map[i][j + 1]) {
            counter++;
        }
        // map[+1][-1]
        if (map[0][cells_in_column - 1]) {
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
    } else if ( j == (cells_in_column - 1) ) {
        // map[-1][-1]
        if (map[cells_in_row - 2][cells_in_column - 2]) {
            counter++;
        }
        // map[-1][0]
        if (map[i - 1][j]) {
            counter++;
        }
        // map[-1][+1]
        if (map[cells_in_row - 2][0]) {
            counter++;
        }
        // map[0][-1]
        if (map[cells_in_row - 1][cells_in_column - 2]) {
            counter++;
        }
        // map[0][+1]
        if (map[cells_in_row - 1][0]) {
            counter++;
        }
        // map[+1][-1]
        if (map[0][cells_in_column - 2]) {
            counter++;
        }
        // map[+1][0]
        if (map[cells_in_row - 1][cells_in_column - 1]) {
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
    } else if (j == 0 && i != (cells_in_row - 1) ) {
        count = check_neighbours_left(map, j, i);
    } else if (i == cells_in_row - 1) {
        count = check_neighbours_down(map, j, i);
    } else if (j == cells_in_column - 1) {
        count = check_neighbours_right(map, j, i);
    } else {
        count = check_neighbours_inside(map, j, i);
    }

    return count;
}
void draw_map(SDL_Renderer *renderer, uc **map, int cursor_column, int cursor_row) {
//    SDL_Init(SDL_INIT_EVERYTHING);
//    TTF_Init();

    int R_back = 11;
    int G_back = 16;
    int B_back = 43;

    SDL_SetRenderDrawColor(renderer , R_back , G_back , B_back , 255);

    SDL_RenderClear(renderer);

    for (int y = 225 , i = 0; i < cells_in_row ; i++ , y += 27) {
        for (int x = 125 , j = 0 ; j < cells_in_column ; j++ , x += 27) {

            put_cell(renderer, map, i, j, x, y, i == cursor_row && j == cursor_column);
        }
    }

    SDL_RenderPresent(renderer);
}
