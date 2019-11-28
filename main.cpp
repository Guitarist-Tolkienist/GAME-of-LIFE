#include <iostream>
#include <SDL2/SDL.h>
#include "MAP.h"

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 0;
    }

    SDL_Window *screen = SDL_CreateWindow("Game of LIFE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH_OF_MAP, HEIGHT_OF_MAP, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);

    SDL_Event event;

    uc **map = new uc*[CELLS_IN_ROW];
    create_map(map);

    int cursor_row = 0;
    int cursor_column = 0;

    draw_map(renderer, map, cursor_column, cursor_row);

    while (SDL_WaitEvent(&event)) {

        switch (event.type) {
            case SDL_QUIT:
                delete_map(map);
                return 0;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        cursor_column++;
                        if (cursor_column > CELLS_IN_COLUMN - 1) {
                            cursor_column = 0;
                        }
                        break;
                    case SDLK_LEFT:
                        cursor_column--;
                        if (cursor_column < 0) {
                            cursor_column = CELLS_IN_COLUMN - 1;
                        }
                        break;
                    case SDLK_DOWN:
                        cursor_row++;
                        if (cursor_row > CELLS_IN_ROW - 1) {
                            cursor_row = 0;
                        }
                        break;
                    case SDLK_UP:
                        cursor_row--;
                        if (cursor_row < 0) {
                            cursor_row = CELLS_IN_ROW - 1;
                        }
                        break;
                    case SDLK_ESCAPE:
                        delete_map(map);
                        return 0;
                    case SDLK_SPACE:
                        map[cursor_row][cursor_column] == NOT_LIFE ? map[cursor_row][cursor_column] = LIFE : map[cursor_row][cursor_column] = NOT_LIFE;
                        break;
                    case SDLK_RETURN:
                        map = get_new_map(map);
                        break;
                    case SDLK_l:
                        load_game(map);
                        break;
                    case SDLK_s:
                        save_game(map);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        draw_map(renderer, map, cursor_column, cursor_row);
    }
}
