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

   // Set timer period.
   BaseClass::mTimerPeriod = 1000;

   // Initialize QCalls.
   mDraw1QCall.bind(this, &VideoThread::executeDraw1);

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

   // Initialize the video subsystem.
   int tRet = SDL_Init(SDL_INIT_VIDEO);
   mValidFlag = tRet == 0;

   // Create the window and renderer.
   doVideoStart();
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
// Execute periodically. This is called by the base class timer.

void VideoThread::executeOnTimer(int aTimerCount)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute something.

void VideoThread::executeDraw1(int  aCode)
{
   doVideoDraw1(aCode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace