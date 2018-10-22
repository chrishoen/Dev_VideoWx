//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEVIDEOSETTINGS_CPP_
#include "someVideoSettings.h"

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

VideoSettings::VideoSettings()
{
   reset();
}

void VideoSettings::reset()
{
   BaseClass::reset();
   strcpy(BaseClass::mDefaultFileName, "Video_Settings.txt");

   mWindowW = 0;
   mWindowH = 0;
   mTimerThreadPeriod = 0;
   mImageFilename[0]=0;
   mImageW = 0;
   mImageH = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void VideoSettings::show()
{
   printf("\n");
   printf("VideoSettings************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("WindowWH             %12d %12d\n", mWindowW,mWindowH);
   printf("TimerThreadPeriod    %12d\n", mTimerThreadPeriod);
   printf("\n");
   printf("ImageFilename        %12s\n", mImageFilename);
   printf("ImageWH              %12d %12d\n", mImageW, mImageH);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void VideoSettings::execute(Ris::CmdLineCmd* aCmd)
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

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void VideoSettings::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace