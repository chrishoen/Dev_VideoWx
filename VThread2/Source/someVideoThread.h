#pragma once

/*==============================================================================
Some video thread class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsQCallThread.h"
#include "SDL.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an example SDL2 video thread that creates a window and renderer
// and draws a filled recatngle.
//   
// It inherits from BaseQCallThread to obtain a call queue based thread
// functionality.

class VideoThread : public Ris::Threads::BaseQCallThread
{
public:

   typedef Ris::Threads::BaseQCallThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   bool mValidFlag;

   SDL_Window*      mWindow;
   SDL_Surface*     mSurface;
   SDL_Surface*     mImage;
   SDL_Renderer*    mRenderer;
   SDL_Texture*     mBackground;
   SDL_Texture*     mShape;
   SDL_RendererInfo mRenderInfo;
   SDL_Rect         mRectA;
   SDL_Rect         mRectB;

   int mWindowW;
   int mWindowH;
   int mRectW;
   int mRectH;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   VideoThread();
  ~VideoThread();
  void show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads.

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running. It starts the child thread.
   void threadInitFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated. It shuts down the child thread.
   void threadExitFunction() override;

   // Execute periodically. This is called by the base class timer. It sends
   // a periodic echo request message.
   void executeOnTimer(int aTimerCount) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. 

   // Example test qcall.

   // The qcall. This is a call that is queued to this thread.
   Ris::Threads::QCall1<int> mDraw1QCall;

   // Execute something. This is bound to the qcall.
   void executeDraw1(int aCode);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Draw some video.
   void doVideoStart();
   void doVideoFinish();
   void doVideoDraw1(int aCode);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Utilities.
   void showWindowFlags(SDL_Window* aWindow);
   void showRenderInfo(const char* aLabel, SDL_RendererInfo* aInfo);
   void showDisplayInfo(int tDisplayIndex);
   void showError();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _SOMEVIDEOTHREAD_CPP_
         VideoThread* gVideoThread;
#else
extern   VideoThread* gVideoThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
