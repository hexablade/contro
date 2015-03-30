#include <SDL2/SDL.h>
#include "SDL_image.h"
#include <stdio.h>

#define MAX_BULLETS 1000


typedef struct
{
    float x, y, dy;
    short life;
    char *name;
    int currentSprite, walking, facingLeft, shooting, visible;
    int alive;
    
    SDL_Texture *sheetTexture;
} Man;

typedef struct
{
    float x, y, dx;
} Bullet;



void addBullet(float x, float y, float dx);
void removeBullet(int i);
int processEvents(SDL_Window *window, Man *man);
void doRender(SDL_Renderer *renderer, Man *man);
void updateLogic(Man *man);
void obliterate_graphics();
