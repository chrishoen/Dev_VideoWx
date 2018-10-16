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
   SDL_Window*  tWindow;
   SDL_Surface* tWindowSurface;
   SDL_Surface* tImage;

   try
   {
      tRet = SDL_Init(SDL_INIT_VIDEO);
      if (tRet) throw std::runtime_error("SDL_Init");
      

      tWindow = SDL_CreateWindow("Video2",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         592, 460, SDL_WINDOW_SHOWN);
      if(tWindow == 0) throw std::runtime_error("SDL_CreateWindow");

      tWindowSurface = SDL_GetWindowSurface(tWindow);
      if (tWindowSurface == 0) throw std::runtime_error("SDL_CreateWindowSurface");

      tImage = SDL_LoadBMP("..\\Files\\sails.bmp");
      if (tImage == 0) throw std::runtime_error("SDL_LoadBMP");


      SDL_BlitSurface(tImage, NULL, tWindowSurface, NULL);

      SDL_UpdateWindowSurface(tWindow);
      SDL_FreeSurface(tImage);

      printf("press enter\n");
      getchar();

   }
   catch (std::exception& e)
   {
      printf("main FAIL %s\n",e.what());
   }

   SDL_DestroyWindow(tWindow);
   SDL_Quit();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the program.

   printf("press enter\n");
   getchar();
   return 0;
}
