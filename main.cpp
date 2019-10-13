#include <iostream>
#include <SDL2/SDL.h>
#include "MAP.h"

using namespace std;

int main() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 0;
    }
    SDL_Window *screen = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          width_of_map, height_of_map, SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);

    SDL_Event event;

    uc **map = new uc *[cells_in_row];
    create_map(map);

    int cursor_row = 0;
    int cursor_column = 0;

    draw_map(renderer, map, cursor_column, cursor_row);


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
                        delete_map(map);
                        return 0;
                    case SDLK_SPACE:
                        if (map[cursor_row][cursor_column] == not_life) {
                            map[cursor_row][cursor_column] = life;
                        } else {
                            map[cursor_row][cursor_column] = not_life;
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
