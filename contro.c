#include <SDL2/SDL.h>
#include "SDL_image.h"
#include <stdio.h>
#include "engine.h"


#define MAX_BULLETS 1000






int main(int argc, char *argv[])
{
  SDL_Window *window;                    // Declare a window
  SDL_Renderer *renderer;                // Declare a renderer
  
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

//creates the characters

  Man man;
  man.x = 50;
  man.y = 0;
  man.currentSprite = 4;  
  man.alive = 1;
  man.visible = 1;
  man.facingLeft = 0;
  
  enemy.x = 250;
  enemy.y = 60;
  enemy.currentSprite = 4;
  enemy.facingLeft = 1;  
  enemy.alive = 1;
  enemy.visible = 1;

  
  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640,                               // width, in pixels
                            480,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderSetLogicalSize(renderer, 320, 240);

  
  SDL_Surface *sheet = IMG_Load("sheet.png");
  if(!sheet)
  {
    printf("Cannot find sheet\n");
    return 1;
  }
  
  man.sheetTexture = SDL_CreateTextureFromSurface(renderer, sheet);  
  SDL_FreeSurface(sheet);
  
  //load enemy
  sheet = IMG_Load("badman_sheet.png");
  if(!sheet)
  {
    printf("Cannot find sheet\n");
    return 1;
  }
  
  enemy.sheetTexture = SDL_CreateTextureFromSurface(renderer, sheet);  
  SDL_FreeSurface(sheet);  

  //load the bg  
  SDL_Surface *bg = IMG_Load("background.png");
  
  if(!sheet)
  {
    printf("Cannot find background\n");
    return 1;
  }
    
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, bg);
  SDL_FreeSurface(bg);

  //load the bullet  
  SDL_Surface *bullet = IMG_Load("bullet.png");
  
  if(!bullet)
  {
    printf("Cannot find bullet\n");
    return 1;
  }

  bulletTexture = SDL_CreateTextureFromSurface(renderer, bullet);
  SDL_FreeSurface(bullet);
  
    for(int i=0; i<MAX_BULLETS;i++) {printf("bullets contains %i, %p\n", i, &bullet[i]);
        }
  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;
  
  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &man);
    
    //Update logic
    updateLogic(&man);
    
    //Render display
    doRender(renderer, &man);
    
   
    SDL_Delay(1000/60);
  }
  
    //Destroys the bullets created
        for(int i = 0; i < MAX_BULLETS; i++)
        removeBullet(i);
    
  //Close and destroy the window
    obliterate_graphics(renderer, &man, window);
    /*
    SDL_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(man.sheetTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(enemy.sheetTexture);
   */
  return 0;
}

