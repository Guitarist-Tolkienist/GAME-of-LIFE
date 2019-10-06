//
// Created by max on 5/10/2019.
//

#include "MAP.h"
#include "iostream"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

void put_cell (SDL_Renderer *renderer , uc **map , int i , int  j , int x , int y , bool selected) {
    SDL_Rect r;
    SDL_Rect frame;

    int Color;

    r.x = x;
    r.y = y;
    r.w = 24;
    r.h = 24;

    frame.x = x - 1;
    frame.y = y - 1;
    frame.w = 26;
    frame.h = 26;

    if (selected) {
        SDL_SetRenderDrawColor(renderer , 250 , 0 , 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer , 2 , 16 , 43, 255);
    }

    SDL_RenderDrawRect(renderer , &frame);

    if (map[i][j] > 0) {
        Color = min(5*map[i][j] , 255);
        SDL_SetRenderDrawColor(renderer, Color , 0 , 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255 , 255, 255);
    }

    SDL_RenderFillRect(renderer , &r);
}

int check_neighbours_up(uc **map , int j ,int i) {
    int count = 0;

    if (j == 0) {
        // map[-1][-1]
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            count++;
        }
        // map[-1][0]
        if (map[cells_in_row - 1][0]) {
            count++;
        }
        // map[-1][1]
        if (map[cells_in_row - 1][1]) {
            count++;
        }
        // map[0][-1]
        if (map[0][cells_in_column - 1]) {
            count++;
        }
        // map[0][+1]
        if (map[0][1]) {
            count++;
        }
        // map[+1][-1]
        if (map[1][cells_in_column - 1]) {
            count++;
        }
        // map[+1][0]
        if (map[1][0]) {
            count++;
        }
        // map[+1][+1]
        if (map[1][1]) {
            count++;
        }
    } else if (j == (cells_in_column - 1)) {
        // map[-1][-1]
        if (map[cells_in_row - 1][cells_in_column - 2]) {
            count++;
        }
        // map[-1][0]
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            count++;
        }
        // map[-1][1]
        if (map[cells_in_row - 1][0]) {
            count++;
        }
        // map[0][-1]
        if (map[0][cells_in_column - 2]) {
            count++;
        }
        // map[0][+1]
        if (map[0][0]) {
            count++;
        }
        // map[+1][-1]
        if (map[1][cells_in_column - 2]) {
            count++;
        }
        // map[+1][0]
        if ( map[1][cells_in_column - 1] ) {
            count++;
        }
        // map[+1][+1]
        if (map[1][0]) {
            count++;
        }
    } else {
        // map[-1][-1]
        if (map[cells_in_row - 1][j - 1]) {
            count++;
        }
        // map[-1][0]
        if (map[cells_in_row - 1][j]) {
            count++;
        }
        // map[-1][+1]
        if (map[cells_in_row - 1] [j + 1]) {
            count++;
        }
        // map[0][-1]
        if (map[i][cells_in_column - 1]) {
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

    return count;
}
int check_neighbours_left(uc **map , int j , int i) {
    int count = 0;

    // map[-1][-1]
    if (map[i - 1][cells_in_column - 1]) {
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
    if (map[i][cells_in_column - 1]) {
        count++;
    }
    // map[0][+1]
    if (map[i][j + 1]) {
        count++;
    }
    // map[+1][-1]
    if (map[i + 1][cells_in_column - 1]) {
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

    return count;
}
int check_neighbours_down(uc **map , int j , int i) {
    int count = 0;

    if ( j == 0 ) {
        // map[-1][-1]
        if (map[cells_in_row - 2][cells_in_column - 1]) {
            count++;
        }
        // map[-1][0]
        if (map[i - 1][j]) {
            count++;
        }
        // map[-1][+1]
        if (map[i - 1] [j + 1]) {
            count++;
        }
        // map[0][-1]
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            count++;
        }
        // map[0][+1]
        if (map[i][j + 1]) {
            count++;
        }
        // map[+1][-1]
        if (map[0][cells_in_column - 1]) {
            count++;
        }
        // map[+1][0]
        if (map[0][0]) {
            count++;
        }
        // map[+1][+1]
        if (map[0][1]) {
            count++;
        }
    } else if ( j == (cells_in_column - 1) ) {
        // map[-1][-1]
        if (map[cells_in_row - 2][cells_in_column - 2]) {
            count++;
        }
        // map[-1][0]
        if (map[i - 1][j]) {
            count++;
        }
        // map[-1][+1]
        if (map[cells_in_row - 2][0]) {
            count++;
        }
        // map[0][-1]
        if (map[cells_in_row - 1][cells_in_column - 2]) {
            count++;
        }
        // map[0][+1]
        if (map[cells_in_row - 1][0]) {
            count++;
        }
        // map[+1][-1]
        if (map[0][cells_in_column - 2]) {
            count++;
        }
        // map[+1][0]
        if (map[cells_in_row - 1][cells_in_column - 1]) {
            count++;
        }
        // map[+1][+1]
        if (map[0][0]) {
            count++;
        }
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
        if (map[0][j - 1]) {
            count++;
        }
        // map[+1][0]
        if (map[0][j]) {
            count++;
        }
        // map[+1][+1]
        if (map[0][j + 1]) {
            count++;
        }
    }

    return count;
}
int check_neighbours_right(uc **map , int j , int i) {
    int count = 0;

    // map[-1][-1]
    if (map[i - 1][j - 1]) {
        count++;
    }
    // map[-1][0]
    if (map[i - 1][j]) {
        count++;
    }
    // map[-1][+1]
    if (map[i - 1][0]) {
        count++;
    }
    // map[0][-1]
    if (map[i][j - 1]) {
        count++;
    }
    // map[0][+1]
    if (map[i][0]) {
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
    if (map[i + 1][0]) {
        count++;
    }

    return count;
}

void draw_map(SDL_Renderer *renderer , uc **map , int cursor_column , int cursor_row) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

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
