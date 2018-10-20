#pragma once

/*==============================================================================
Some serial thread class.
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
// This is a serial message thread that transmits and receives byte content
// messages via a serial message child thread which manages a serial message
// port.
//
// It provides the capability to send messages via the child thread serial
// port and it provides handlers for messages received via the child thread
// serial port. When the child thread receives a message it invokes a qcall
// that was registered by this thread to defer execution of a message handler
//  that is a member of this thread.
//   
// It inherits from BaseQCallThread to obtain a call queue based thread
// functionality.

class  VideoThread : public Ris::Threads::BaseThreadWithTermSem
{
public:

   typedef Ris::Threads::BaseThreadWithTermSem BaseClass;

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

   void showWindowFlags(SDL_Window* aWindow);
   void showRenderInfo(const char* aLabel, SDL_RendererInfo* aInfo);
   void showDisplayInfo(int tDisplayIndex);

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
