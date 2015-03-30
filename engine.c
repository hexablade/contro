#include <SDL2/SDL.h>
#include "SDL_image.h"
#include <stdio.h>
#include "engine.h"


#define MAX_BULLETS 1000


void addBullet(float x, float y, float dx);
void removeBullet(int i);
int processEvents(SDL_Window *window, Man *man);
void doRender(SDL_Renderer *renderer, Man *man);
void updateLogic(Man *man);


void obliterate_graphics(){
    SDL_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(man.sheetTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(enemy.sheetTexture);
}