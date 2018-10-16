#include "stdafx.h"

#include <iostream>
#include <stdexcept>

#include "SDL.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the program.

   int tRet;
   SDL_Window*   tWindow = 0;
   SDL_Renderer* tRenderer = 0;
   SDL_Texture*  tTexture = 0;
   SDL_Surface*  tWindowSurface = 0;
   SDL_Surface*  tImage = 0;

   try
   {
      tRet = SDL_Init(SDL_INIT_VIDEO);
      if (tRet) throw std::runtime_error("SDL_Init");

      // Create window.
      tWindow = SDL_CreateWindow("Video2",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         592, 460, SDL_WINDOW_SHOWN);
      if(tWindow == 0) throw std::runtime_error("SDL_CreateWindow");

      // Create renderer.
      tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (tRenderer == 0) throw std::runtime_error("SDL_CreateRenderer");

      // Load image.
      tImage = SDL_LoadBMP("..\\Files\\sails.bmp");
      if (tImage == 0) throw std::runtime_error("SDL_LoadBMP");

      // Create texture.
      tTexture = SDL_CreateTextureFromSurface(tRenderer,tImage);
      SDL_FreeSurface(tImage);
      if (tTexture == 0) throw std::runtime_error("SDL_CreateTextureFromSurface");

      // Draw the texture.
      SDL_RenderClear(tRenderer);
      SDL_RenderCopy(tRenderer, tTexture, NULL, NULL);
      SDL_RenderPresent(tRenderer);

      // Wait.
      printf("press enter\n");
      getchar();

   }
   catch (std::exception& e)
   {
      printf("main FAIL %s\n",e.what());
   }

   // Done.
   if (tTexture)  SDL_DestroyTexture(tTexture);
   if (tRenderer) SDL_DestroyRenderer(tRenderer);
   if (tWindow)   SDL_DestroyWindow(tWindow);
   SDL_Quit();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the program.

   printf("press enter\n");
   getchar();
   return 0;
}
