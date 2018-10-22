/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someImagePainter.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

ImagePainter::ImagePainter()
{
   reset();
}

ImagePainter::ImagePainter(VideoParms* aParms)
{
   mP = aParms;
   reset();
}

void ImagePainter::initialize(VideoParms* aParms)
{
   mP = aParms;
   reset();
}

void ImagePainter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize the window image matrix to zeroes.

void ImagePainter::initializeTargetBitMap(
   cv::Mat& aTarget)
{
   // Set color from parms.
   mForeColor = cv::Scalar(mP->mTargetColor[0], mP->mTargetColor[1], mP->mTargetColor[2]);
   mBackColor = cv::Scalar(0,0,0);

   // Create new image.
   aTarget = cv::Mat(mP->mTargetHeight, mP->mTargetWidth, CV_8UC3, mBackColor);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Paint the target image with a reference pattern. The input is a code that
// specifies the pattern. This is used to display checkerboards and gray
// cards.

void ImagePainter::doPaintTargetWithReference(
   int      aReferenceCode,   // Input
   cv::Mat& aTarget)          // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Paint into window image.

   initializeTargetBitMap(aTarget);

   switch (aReferenceCode)
   {
   case cCheckerBoard:
   {
      // Show checkerboard.
      drawCheckerBoard(aTarget, mP->mWidthX, mP->mWidthY);
      drawBorder(aTarget);     
   }
   break;
   case cAllZeroes:
   {
      // Show all ones.
      drawAllZeroes(aTarget);
   }
   break;
   case cAllOnes:
   {
      // Show all ones.
      drawAllOnes(aTarget);
   }
   break;
   case cReticle:
   {
      // Show reticle.
      drawReticle(aTarget, mP->mWidthX, mP->mWidthY);
      drawBorder(aTarget);
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a checkerboard in the window image matrix target region.

void ImagePainter::drawCheckerBoard(
   cv::Mat& aTarget,
   int      aWidthX,
   int      aWidthY)
{
   // Draw the points.
   int tX = aWidthX*2;
   int tY = aWidthY*2;

   for (int iY = 0; iY < aTarget.rows; iY++)
   {
      for (int jX = 0; jX < aTarget.cols; jX++)
      {
         int tN1 = (2 * iY) / tY;
         int tM1 = (2 * jX) / tX;
         int tI = (3 * tN1 + tM1 + 1) % 2;

         if (tI)
         {
            aTarget.at<cv::Scalar>(iY,jX) = mForeColor;
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a reticle in the window image matrix target region.

void ImagePainter::drawReticle(
   cv::Mat& aTarget,
   int      aWidthX,
   int      aWidthY)
{
   // Draw the points.
   int tX = aWidthX * 2;
   int tY = aWidthY * 2;

   // Guard.
   if (!mP->mTargetBorder) return;

   for (int iY = 0; iY < aTarget.rows; iY++)
   {
      aTarget.at<cv::Scalar>(iY, aWidthY) = mForeColor;
      aTarget.at<cv::Scalar>(iY, aTarget.cols - aWidthY) = mForeColor;

      aTarget.at<cv::Scalar>(iY, 288) = mForeColor;
   }

   for (int iX = 0; iX < aTarget.cols; iX++)
   {
      aTarget.at<cv::Scalar>(aWidthX, iX) = mForeColor;
      aTarget.at<cv::Scalar>(aTarget.rows - aWidthX, iX) = mForeColor;
      
      aTarget.at<cv::Scalar>(240, iX) = mForeColor;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw all zeroes in the target window matrix.

void ImagePainter::drawAllZeroes(
   cv::Mat& aTarget)
{
   for (int iY = 0; iY < aTarget.rows; iY++)
   {
      for (int jX = 0; jX < aTarget.cols; jX++)
      {
         aTarget.at<cv::Scalar>(iY, jX) = mBackColor;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw all ones in the target window matrix.

void ImagePainter::drawAllOnes(
   cv::Mat& aTarget)
{
   for (int iY = 0; iY < aTarget.rows; iY++)
   {
      for (int jX = 0; jX < aTarget.cols; jX++)
      {
         aTarget.at<cv::Scalar>(iY, jX) = mForeColor;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a border around the window image target region.

void ImagePainter::drawBorder(
   cv::Mat& aTarget)
{
   // Guard.
   if (!mP->mTargetBorder) return;

   for (int iY = 0; iY < aTarget.rows; iY++)
   {
      aTarget.at<cv::Scalar>(iY,              0) = mForeColor;
      aTarget.at<cv::Scalar>(iY, aTarget.cols-1) = mForeColor;
   }

   for (int iX = 0;  iX < aTarget.cols; iX++)
   {
      aTarget.at<cv::Scalar>(0,              iX) = mForeColor;
      aTarget.at<cv::Scalar>(aTarget.rows-1, iX) = mForeColor;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace