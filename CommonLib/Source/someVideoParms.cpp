//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEVIDEOPARMS_CPP_
#include "someVideoParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

VideoParms::VideoParms()
{
   reset();
}

void VideoParms::reset()
{
   BaseClass::reset();
   strcpy(BaseClass::mDefaultFileName, "Video_Parms.txt");

   mWindowW = 0;
   mWindowH = 0;
   mTimerThreadPeriod = 0;
   mImageFilename[0]=0;
   mImageW = 0;
   mImageH = 0;

   mTargetWidth = 0;
   mTargetHeight = 0;

   mForeColor[0] = 0;
   mForeColor[1] = 0;
   mForeColor[2] = 0;

   mBackColor[0] = 0;
   mBackColor[1] = 0;
   mBackColor[2] = 0;

   mWidthX = 0;
   mWidthY = 0;
   mTargetBorder = false;


}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void VideoParms::show()
{
   printf("\n");
   printf("VideoParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("WindowWH              %10d %4d\n", mWindowW,mWindowH);
   printf("TimerThreadPeriod     %10d\n",     mTimerThreadPeriod);
   printf("\n");
   printf("ImageFilename         %10s\n",     mImageFilename);
   printf("ImageWH               %10d %4d\n", mImageW, mImageH);

   printf("\n");
   printf("\n");
   printf("TargetWH              %10d %4d\n", mTargetWidth, mTargetHeight);

   printf("\n");
   printf("ForeColor             %10d %4d %4d\n", mForeColor[0], mForeColor[1], mForeColor[2]);
   printf("BackColor             %10d %4d %4d\n", mBackColor[0], mBackColor[1], mBackColor[2]);

   printf("\n");
   printf("WidthX                %10d\n", mWidthX);
   printf("WidthY                %10d\n", mWidthY);
   printf("TargetBorder          %10s\n", my_string_from_bool(mTargetBorder));
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void VideoParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerThreadPeriod"))   mTimerThreadPeriod = aCmd->argInt(1);

   if (aCmd->isCmd("WindowWH"))
   {
      mWindowW = aCmd->argInt(1);
      mWindowH = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ImageFilename"))   aCmd->copyArgString(1, mImageFilename,cMaxStringSize);
   if (aCmd->isCmd("ImageWH"))
   {
      mImageW = aCmd->argInt(1);
      mImageH = aCmd->argInt(2);
   }

   if (aCmd->isCmd("TargetWH"))
   {
      mTargetWidth = aCmd->argInt(1);
      mTargetHeight = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ForeColor"))
   {
      mForeColor[0] = aCmd->argInt(1);
      mForeColor[1] = aCmd->argInt(2);
      mForeColor[2] = aCmd->argInt(3);
   }

   if (aCmd->isCmd("BackColor"))
   {
      mBackColor[0] = aCmd->argInt(1);
      mBackColor[1] = aCmd->argInt(2);
      mBackColor[2] = aCmd->argInt(3);
   }

   if (aCmd->isCmd("WidthX"))        mWidthX = aCmd->argInt(1);
   if (aCmd->isCmd("WidthY"))        mWidthY = aCmd->argInt(1);
   if (aCmd->isCmd("TargetBorder"))  mTargetBorder = aCmd->argBool(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void VideoParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace