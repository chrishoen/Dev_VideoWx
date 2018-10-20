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

void VideoThread::doVideoDraw2()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::doVideoDraw2");

   try
   {
      int tRet = 0;

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
      // Draw the window.

      Prn::print(Prn::ThreadRun1, "DrawWindow*****************************************************");

      mSurface = SDL_GetWindowSurface(mWindow);
      if (mSurface == 0) throw "SDL_GetWindowSurface";

      mImage = SDL_LoadBMP("C:/Alpha/Image/sails.bmp");
      if (mImage == 0) throw "SDL_LoadBMP";

      tRet = SDL_BlitSurface(mImage, NULL, mSurface, NULL);
      if (tRet) throw "SDL_BlitSurface";

      tRet = SDL_UpdateWindowSurface(mWindow);
      if (tRet) throw "SDL_UpdateWindowSurface";

      showWindowFlags(mWindow);

      SDL_FreeSurface(mImage);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Wait.

      showDisplayInfo(0);
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
}//namespace