#pragma once

/*==============================================================================
Some video thread class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsThreads.h"
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

class VideoThread : public Ris::Threads::BaseThread
{
public:

   typedef Ris::Threads::BaseThread BaseClass;

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

   unsigned int mDrawEventType;

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

   // Thread run function. This is called by the base class immediately 
   // after the thread init function. It performs the thread processing.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated. It shuts down the child thread.
   void threadExitFunction() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Start and finish the video subsystem.
   void doVideoStart();
   void doVideoFinish();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. 

   // Post an event to draw something.
   void postDraw1(int aCode);

   // Draw something. This is requested by the posted event.
   void doVideoDraw1(SDL_Event* aEvent);

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
