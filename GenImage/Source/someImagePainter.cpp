/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "prnPrint.h"

#include "svSysParms.h"
#include "svTargetParms.h"
#include "svPixelFunctions.h"
#include "svRCIndex.h"

#include "svImagePainter.h"

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

ImagePainter::ImagePainter(TargetParms* aParms)
{
   mP = aParms;
   reset();
}

void ImagePainter::initialize(TargetParms* aParms)
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
      Cmn::ImageBitMap*& aBitMap)
{
   // Create new bitmap.
   aBitMap = new Cmn::ImageBitMap(mP->mTargetHeight, mP->mTargetWidth);

   // Set color from parms.
   aBitMap->mColor[1] = mP->mTargetColor[1];
   aBitMap->mColor[0] = mP->mTargetColor[0];
   aBitMap->mColor[2] = mP->mTargetColor[2];

   // Set offsets from parms.
   aBitMap->mOffsetX = mP->mTargetPixelOffset1.mCol + mP->mTargetPixelOffset2.mCol;
   aBitMap->mOffsetY = mP->mTargetPixelOffset1.mRow + mP->mTargetPixelOffset2.mRow;
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
   int                aReferenceCode,   // Input
   Cmn::ImageBitMap*& aBitMap)          // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Paint into window image.

   initializeTargetBitMap(aBitMap);

   switch (aReferenceCode)
   {
   case cCheckerBoard:
   {
      // Show checkerboard.
      drawCheckerBoard(aBitMap, mP->mWidthX, mP->mWidthY);
      drawBorder(aBitMap);     
   }
   break;
   case cAllZeroes:
   {
      // Show all ones.
      drawAllZeroes(aBitMap);
   }
   break;
   case cAllOnes:
   {
      // Show all ones.
      drawAllOnes(aBitMap);
   }
   break;
   case cReticle:
   {
      // Show all ones.
      drawReticle(aBitMap, mP->mWidthX, mP->mWidthY);
      drawBorder(aBitMap);
   }
   break;
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Paint the target image with a grid of object points. The input is a
// list of target object points. The output is a target window image
// matrix. This initializes the output window image matrix and then writes
// pixel values to it. This paints all of the target object points as
// pixels in the window image target region.

void ImagePainter::doPaintTargetWithGrid(
   Some::ObjectPointArray& aTargetObjectPoints,    // Input
   Cmn::ImageBitMap*&    aBitMap)                // Output
{
   // Initialize.
   initializeTargetBitMap(aBitMap);

   // Draw object points.
   drawObjectPoints(
      aBitMap, 
      aTargetObjectPoints);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a checkerboard in the window image matrix target region.

void ImagePainter::drawCheckerBoard(
   Cmn::ImageBitMap*& aBitMap,
   int                aWidthX,
   int                aWidthY)
{
   // Draw the points.
   int tX = aWidthX*2;
   int tY = aWidthY*2;

   for (int iY = 0; iY < aBitMap->mRows; iY++)
   {
      for (int jX = 0; jX < aBitMap->mCols; jX++)
      {
         int tN1 = (2 * iY) / tY;
         int tM1 = (2 * jX) / tX;
         int tI = (3 * tN1 + tM1 + 1) % 2;

         if (tI)
         {
            aBitMap->set(iY,jX,true);
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a reticle in the window image matrix target region.

void ImagePainter::drawReticle(
   Cmn::ImageBitMap*& aBitMap,
   int                aWidthX,
   int                aWidthY)
{
   // Draw the points.
   int tX = aWidthX * 2;
   int tY = aWidthY * 2;

   // Guard.
   if (!mP->mTargetBorder) return;

   for (int iY = 0; iY < aBitMap->mRows; iY++)
   {
      aBitMap->set(iY, aWidthY, true);
      aBitMap->set(iY, aBitMap->mCols - aWidthY, true);


      aBitMap->set(iY, 288, true);
   }

   for (int iX = 0; iX < aBitMap->mCols; iX++)
   {
      aBitMap->set(aWidthX, iX, true);
      aBitMap->set(aBitMap->mRows - aWidthX, iX, true);
      
      aBitMap->set(240, iX, true);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw all zeroes in the target window matrix.

void ImagePainter::drawAllZeroes(
   Cmn::ImageBitMap*& aBitMap)
{
   aBitMap->setAllZeroes();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw all ones in the target window matrix.

void ImagePainter::drawAllOnes(
   Cmn::ImageBitMap*& aBitMap)
{
   aBitMap->setAllOnes();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a border around the window image target region.

void ImagePainter::drawBorder(
   Cmn::ImageBitMap*& aBitMap)
{
   // Guard.
   if (!mP->mTargetBorder) return;

   for (int iY = 0; iY < aBitMap->mRows; iY++)
   {
      aBitMap->set( iY, 0                , true);
      aBitMap->set( iY, aBitMap->mCols - 1, true);
   }

   for (int iX = 0;  iX < aBitMap->mCols; iX++)
   {
      aBitMap->set(0,               iX, true );
      aBitMap->set(aBitMap->mRows-1, iX, true );
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw each point in a list of object points in the window image
// matrix target region.

void ImagePainter::drawObjectPoints(
   Cmn::ImageBitMap*&    aBitMap,
   Some::ObjectPointArray& aObjectPoints)
{
   // Get x,y limits.
   int ny = aObjectPoints.size().height;
   int nx = aObjectPoints.size().width;

   // Local point variable.
   cv::Point3d tPoint;

   // For all of the points in the object point array.
   // Loop through Y from the top to the bottom.
   for (int iy = 0; iy < ny; iy++)
   {
      // Loop through X from the left to the right.
      for (int ix = 0; ix < nx; ix++)
      {
         // Get the point from the array.
         tPoint = aObjectPoints(iy,ix);

         // If the point is not valid then skip to the end of the loop.
         if (!isValid(tPoint)) continue;

         // Convert the object point to pixel coordinates.
         RCIndex tPixel;

         Some::convertObjectPointToPixel(
            tPoint,       // Input
            tPixel);      // Output

         // If the pixel is in bounds.
         if (isObjectPixelInBounds(tPixel))
         {
            // Set the matrix at the row and column.
            aBitMap->set(tPixel.mRow, tPixel.mCol, true);
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace