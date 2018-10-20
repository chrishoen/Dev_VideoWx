/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "SDL.h"

#define  _SOMEVIDEOTHREAD_CPP_
#include "someVideoThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

VideoThread::VideoThread()
{
   // Set member variables.
   mValidFlag = false;

   mWindow = 0;
   mSurface = 0;
   mImage;
   mRenderer = 0;
   mBackground = 0;
   mShape = 0;

   mWindowW = 1920;
   mWindowH = 1080;
   mWindowW = 640;
   mWindowH = 480;
   mRectH = 200;
   mRectW = 200;

   mRectA.x = mWindowW/4 - mRectW/2;
   mRectA.y = mWindowH/2 - mRectH/2;
   mRectA.w = mRectW;
   mRectA.h = mRectH;

   mRectB.x = (3*mWindowW)/4 - mRectW/2;
   mRectB.y = mWindowH/2 - mRectH/2;
   mRectB.w = mRectW;
   mRectB.h = mRectH;

   mDrawEventType = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

VideoThread::~VideoThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void VideoThread::show()
{
   Prn::print(0, "VideoMsgPort");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It starts the child thread.

void VideoThread::threadInitFunction()
{
   int tRet = 0;
   Prn::print(Prn::ThreadInit1, "VideoThread::threadInitFunction");

   // Initialize the video subsystem.
   tRet = SDL_Init(SDL_INIT_VIDEO);
   if (tRet)
   {
      Prn::print(Prn::ThreadInit1, "ERROR SDL_Init");
      mValidFlag = false;
      return;
   }
   mValidFlag = true;

   // Initialize event types.
   mDrawEventType = SDL_RegisterEvents(1);

   // Create the window and renderer.
   doVideoStart();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately 
// after the thread init function. It performs the thread processing.

void VideoThread::threadRunFunction()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::threadRunFunction %s", my_string_from_bool(mValidFlag));
   if (!mValidFlag) return;

   // Draw some video.
   while (true)
   {
      SDL_Event tEvent;
      SDL_WaitEvent(&tEvent);
      Prn::print(Prn::ThreadRun3, "event %d", tEvent.type);
      if (tEvent.type == SDL_QUIT) break;
      if (tEvent.type == SDL_MOUSEBUTTONDOWN) break;
      if (tEvent.type == mDrawEventType)
      {
         doVideoDraw1(&tEvent);
      }
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It shuts down the child thread.

void VideoThread::threadExitFunction()
{
   Prn::print(Prn::ThreadInit1, "VideoThread::threadExitFunction");

   doVideoFinish();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Post an event to draw something.

void VideoThread::postDraw1(int aCode)
{
   // Guard.
   if (mDrawEventType < 1)
   {
      Prn::print(Prn::ThreadInit1, "ERROR event type not initialized");
      return;
   }

   // Post the event.
   SDL_Event tEvent;
   SDL_memset(&tEvent, 0, sizeof(tEvent)); /* or SDL_zero(tEvent) */
   tEvent.type = mDrawEventType;
   tEvent.user.code = aCode;
   tEvent.user.data1 = 0;
   tEvent.user.data2 = 0;
   SDL_PushEvent(&tEvent);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace