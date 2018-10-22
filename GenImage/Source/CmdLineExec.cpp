
#include "stdafx.h"

#include "risAlphaDir.h"
#include "someVideoParms.h"
#include "someImagePainter.h"

#include "CmdLineExec.h"

using namespace Some;

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))    executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))    executeGo5(aCmd);
   if (aCmd->isCmd("Parms"))  executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   Some::gVideoParms.reset();
   Some::gVideoParms.readSection("default");

   Some::ImagePainter tPainter(&Some::gVideoParms);
   cv::Mat tImage;
   tPainter.doPaintTargetWithReference(aCmd->argInt(1),tImage);

   char tBuffer[100];
   cv::imwrite(Ris::getAlphaFilePath_Image(tBuffer, gVideoParms.mImageFilename),tImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   char tBuffer[100];
   Prn::print(0,"ImageFilename %s",Ris::getAlphaFilePath_Image(tBuffer,gVideoParms.mImageFilename));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   int blockSize = 75;
   int imageSize = blockSize * 8;
   cv::Mat chessBoard(imageSize, imageSize, CV_8UC3, cv::Scalar::all(0));
   unsigned char color = 0;

   for (int i = 0; i < imageSize; i = i + blockSize) {
      color = ~color;
      for (int j = 0; j < imageSize; j = j + blockSize) {
         cv::Mat ROI = chessBoard(cv::Rect(i, j, blockSize, blockSize));
         ROI.setTo(cv::Scalar::all(color));
         color = ~color;
      }
   }

   char tBuffer[200];
   cv::imwrite(Ris::getAlphaFilePath_Image(tBuffer, gVideoParms.mImageFilename), chessBoard );
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   Some::gVideoParms.reset();
   Some::gVideoParms.readSection("default");
   Some::gVideoParms.show();
}

