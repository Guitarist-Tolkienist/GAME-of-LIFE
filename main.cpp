#include <iostream>
#include <SDL2/SDL.h>
#include "MAP.h"
#include <fstream>

using namespace std;

uc **get_new_map (uc **map);
void create_map (uc **map);
void save_game (uc **map) ;
void load_game (uc **map) ;

int main() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 0;
    }
    SDL_Window *screen = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_of_map, height_of_map ,SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);

    SDL_Event event;

    uc **map = new uc*[cells_in_row];

    create_map(map);

    bool run_game = true;

    int cursor_row = 0;
    int cursor_column = 0;

    draw_map(renderer , map , cursor_column , cursor_row);

    while (run_game) {

        while (SDL_WaitEvent(&event)) {

            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT :
                            cursor_column++;
                            if (cursor_column > cells_in_column - 1) {
                                cursor_column = 0;
                            }
                            break;
                        case SDLK_LEFT :
                            cursor_column--;
                            if (cursor_column < 0) {
                                cursor_column = cells_in_column - 1;
                            }
                            break;
                        case SDLK_DOWN :
                            cursor_row++;
                            if (cursor_row > cells_in_row - 1) {
                                cursor_row = 0;
                            }
                            break;
                        case SDLK_UP :
                            cursor_row--;
                            if (cursor_row < 0) {
                                cursor_row = cells_in_row - 1;
                            }
                            break;
                        case SDLK_ESCAPE:
                            run_game = false;
                        case SDLK_SPACE:
                            if (map[cursor_row][cursor_column] == 0) {
                                map[cursor_row][cursor_column] = 1;
                            } else {
                                map[cursor_row][cursor_column] = 0;
                            }
                            break;
                        case SDLK_RETURN :
                            map = get_new_map(map);
                            break;
                        case SDLK_l:
                            load_game(map);
                            break;
                        case SDLK_s:
                            save_game(map);
                            break;
                        default :
                            break;
                    }
                    break;
                default:
                    break;
            }
            draw_map(renderer, map, cursor_column, cursor_row);
        }

    }

    return 0;
}

uc **get_new_map (uc **map) {
    uc **new_map = new uc*[cells_in_row];
    int count = 0;

    for (int i = 0; i < cells_in_row; i++) {
        new_map[i] = new uc [cells_in_column];
    }

    for (int i = 0; i < cells_in_row; i++) {
        for (int j = 0; j < cells_in_column; j++) {
            new_map[i][j] = 0;
        }
    }

    for (int i = 0; i < cells_in_row; i++) {
        for (int j = 0; j < cells_in_column; j++) {

            count = 0;

            if (i == 0) {
                count = check_neighbours_up(map, j, i);
            } else if (j == 0 && i != (cells_in_row - 1) ) {
                count = check_neighbours_left(map, j, i);
            } else if (i == cells_in_row - 1) {
                count = check_neighbours_down(map, j, i);
            } else if (j == cells_in_column - 1) {
                count = check_neighbours_right(map, j, i);
            } else {
                // map[-1][-1]
                if (map[i - 1][j - 1]) {
                    count++;
                }
                // map[-1][0]
                if (map[i - 1][j]) {
                    count++;
                }
                // map[-1][+1]
                if (map[i - 1][j + 1]) {
                    count++;
                }
                // map[0][-1]
                if (map[i][j - 1]) {
                    count++;
                }
                // map[0][+1]
                if (map[i][j + 1]) {
                    count++;
                }
                // map[+1][-1]
                if (map[i + 1][j - 1]) {
                    count++;
                }
                // map[+1][0]
                if (map[i + 1][j]) {
                    count++;
                }
                // map[+1][+1]
                if (map[i + 1][j + 1]) {
                    count++;
                }
            }

            if (count == 3) {
                if (map[i][j] > 0) {
                    if (map[i][j] < 250) {
                        new_map[i][j] = map[i][j] +1;
                    } else {
                        new_map[i][j] = 250;
                    }
                } else {
                    new_map[i][j] = 1;
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
                    new_map[i][j] = 1;
                }
            }


        }
    }
    for (int i = 0; i < cells_in_row; i++) {
        delete[] map[i];
    }

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

    map[0][0] = 123;

    cout << endl;
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
            map[i][j] = 0;
        }
    }
}

