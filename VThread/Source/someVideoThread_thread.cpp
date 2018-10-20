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
   // Set base class thread priority.
   BaseClass::setThreadPriorityHigh();

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

   mRectA.x = mWindowW / 2 - mRectW / 2;
   mRectA.y = mWindowH / 2 - mRectH / 2;
   mRectA.w = mRectW;
   mRectA.h = mRectH;
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
   Prn::print(Prn::ThreadInit1, "VideoThread::threadInitFunction");
   int tRet = SDL_Init(SDL_INIT_VIDEO);
   mValidFlag = tRet == 0;
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
   doVideoDraw1();

   // Wait.
   BaseClass::mTerminateSem.get();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It shuts down the child thread.

void VideoThread::threadExitFunction()
{
   Prn::print(Prn::ThreadInit1, "VideoThread::threadExitFunction");

   if (mRenderer) SDL_DestroyRenderer(mRenderer);
   if (mWindow)   SDL_DestroyWindow(mWindow);
   mRenderer = 0;
   mWindow = 0;

   SDL_Quit();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace