#include <SDL2/SDL.h>
#include "SDL_image.h"
#include <stdio.h>
#include "engine.h"


#define MAX_BULLETS 1000


void addBullet(float x, float y, float dx){
    
    int found = -1;
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        if(bullets[i] == NULL)
        {
            found = i;
            break;
        }
        
        if(found >= 0)
        {
            int i = found;
            bullets[i] = malloc(sizeof(Bullet));
            bullets[i]->x = x;
            bullets[i]->y = y;
            bullets[i]->dx = dx;
        }
        
    }
}


void removeBullet(int i)
{
    if(bullets[i])
    {
        free(bullets[i]);
        bullets[i] = NULL;
    }
}
int processEvents(SDL_Window *window, Man *man)
{
    SDL_Event event;
    int done = 0;
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                //quit out of the game
                done = 1;
                break;
        }
    }
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(!man->shooting)
    {
        if(state[SDL_SCANCODE_LEFT])
        {
            man->x -= 3;
            man->walking = 1;
            man->facingLeft = 1;
            
            if(globalTime % 6 == 0)
            {
                man->currentSprite++;
                man->currentSprite %= 4;
            }
        }
        else if(state[SDL_SCANCODE_RIGHT])
        {
            man->x += 3;
            man->walking = 1;
            man->facingLeft = 0;
            
            if(globalTime % 6 == 0)
            {
                man->currentSprite++;
                man->currentSprite %= 4;
            }
        }
        else
        {
            man->walking = 0;
            man->currentSprite = 4;
        }
    }
    
    if(!man->walking)
    {
        if(state[SDL_SCANCODE_SPACE])// && !man->dy)
        {
            if(globalTime % 6 == 0)
            {
                if(man->currentSprite == 4)
                    man->currentSprite = 5;
                else
                    man->currentSprite = 4;
                
                if(!man->facingLeft)
                {
                    addBullet(man->x+35, man->y+20, 3);
                }
                else
                {
                    addBullet(man->x+5, man->y+20, -3);
                }
            }
            
            man->shooting = 1;
        }
        else
        {
            man->currentSprite = 4;
            man->shooting = 0;
        }
    }
    
    if(state[SDL_SCANCODE_UP] && !man->dy)
    {
        man->dy = -8;
    }
    if(state[SDL_SCANCODE_DOWN])
    {
        //man->y += 10;
    }
    
    return done;
}


void doRender(SDL_Renderer *renderer, Man *man);
void updateLogic(Man *man);


void obliterate_graphics(void){
    SDL_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(man.sheetTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(enemy.sheetTexture);
}