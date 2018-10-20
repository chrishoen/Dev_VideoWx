/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "SDL.h"

#include "someVideoThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoStart()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::doVideoStart");

   try
   {
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Show SDL info.

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "VideoDrivers***************************************************");
      int tNumVideoDrivers = SDL_GetNumVideoDrivers();
      Prn::print(Prn::ThreadRun1, "NumVideoDrivers        %1d", tNumVideoDrivers);
      for (int i = 0; i < tNumVideoDrivers; i++)
      {
         Prn::print(Prn::ThreadRun1, "VideoDriver            %s", SDL_GetVideoDriver(i));
      }

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "VideoDisplays***************************************************");
      int tNumVideoDisplays = SDL_GetNumVideoDisplays();
      Prn::print(Prn::ThreadRun1, "NumVideoDisplays       %1d", tNumVideoDisplays);

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "RendererDrivers************************************************");
      int tNumRenderDrivers = SDL_GetNumRenderDrivers();
      Prn::print(Prn::ThreadRun1, "NumRenderDrivers       %1d", tNumRenderDrivers);
      for (int i = 0; i < tNumRenderDrivers; i++)
      {
         SDL_GetRenderDriverInfo(i, &mRenderInfo);
         showRenderInfo("RenderDriver", &mRenderInfo);
      }

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Create window.

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "CreateWindow***************************************************");
      unsigned int tWindowFlags = 0;
      tWindowFlags |= SDL_WINDOW_SHOWN;
      // tWindowFlags |= SDL_WINDOW_FULLSCREEN;
      // tWindowFlags |= SDL_WINDOW_OPENGL;

      mWindow = SDL_CreateWindow("VideoThread",
         //    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1),
         mWindowW, mWindowH, tWindowFlags);
      if (mWindow == 0) throw "SDL_CreateWindow";

      showWindowFlags(mWindow);

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Create renderer.

      Prn::print(Prn::ThreadRun1, "CreateRenderer*************************************************");

      int tRenderDriverIndex = -1;
      tRenderDriverIndex = 0;
      unsigned int tRenderFlags = 0;
      tRenderFlags |= SDL_RENDERER_ACCELERATED;
      tRenderFlags |= SDL_RENDERER_PRESENTVSYNC;

      mRenderer = SDL_CreateRenderer(mWindow, tRenderDriverIndex, tRenderFlags);
      if (mRenderer == 0) throw "SDL_CreateRenderer";

      // Set renderer to the same size as the window.
      SDL_RenderSetLogicalSize(mRenderer, mWindowW, mWindowH);

      // Show.
      SDL_GetRendererInfo(mRenderer, &mRenderInfo);
      showRenderInfo("Renderer", &mRenderInfo);

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Draw the window.

      Prn::print(Prn::ThreadRun1, "DrawWindow*****************************************************");

      // Set renderer to blue.
      SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

      // Clear the window and make it all blue.
      SDL_RenderClear(mRenderer);

      // Render the changes above.
      SDL_RenderPresent(mRenderer);

      // Show.
      showWindowFlags(mWindow);
   }
   catch (const char* aString)
   {
      Prn::print(Prn::ThreadRun1, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoFinish()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::doVideoFinish");

   if (mRenderer) SDL_DestroyRenderer(mRenderer);
   if (mWindow)   SDL_DestroyWindow(mWindow);
   mRenderer = 0;
   mWindow = 0;

   SDL_Quit();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoDraw1(int aCode)
{
   Prn::print(Prn::ThreadRun1, "VideoThread::doVideoDraw1 %d",aCode);

   try
   {
      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Draw the window.

      if (aCode == 0)
      {
         // Set renderer to blue.
         Prn::print(Prn::ThreadRun1, "blue");
         SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
      }

      if (aCode == 1)
      {
         // Set renderer to red.
         Prn::print(Prn::ThreadRun1, "red");
         SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
      }

      // Clear the window and make it all blue.
      SDL_RenderClear(mRenderer);

      // Render the changes above.
      SDL_RenderPresent(mRenderer);
   }
   catch (const char* aString)
   {
      Prn::print(Prn::ThreadRun1, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//name;space