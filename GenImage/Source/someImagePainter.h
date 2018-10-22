#pragma once

/*==============================================================================
Some namespace: sixdofs that are measured by a computer vision based system.
Target painter. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

#include "someVideoParms.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a set of funtions that paint a target window image.

class ImagePainter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Target reference types.
   static const int cCheckerBoard  = 1;
   static const int cAllZeroes     = 2;
   static const int cAllOnes       = 3;
   static const int cReticle       = 4;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   VideoParms* mP;

   // Color.
   cv::Scalar mForeColor;
   cv::Scalar mBackColor;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.

   // Constructor.
   ImagePainter();
   ImagePainter(VideoParms* aParms);
   void initialize(VideoParms* aParms);
   void reset();
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Paint the target image with a reference pattern. The input is a code that
   // specifies the pattern. This is used to display checkerboards and gray
   // cards.
   void doPaintTargetWithReference(
      int      aReferenceCode,    // Input   
      cv::Mat& aTarget);          // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   // Window painters.

   // Initialize the window image matrix to zeroes.
   void initializeTargetBitMap(
      cv::Mat& aTarget);

   // Draw a checkerboard in the window image matrix target region.
   void drawCheckerBoard(
      cv::Mat& aTarget,
      int      aWidthX,
      int      aWidthY);

   // Draw reticle in the window image matrix target region
   void drawReticle(
      cv::Mat& aTarget,
      int      aWidthX,
      int      aWidthY);

   // Draw all zeroes in the window image matrix.
   void drawAllZeroes(
      cv::Mat& aTarget);

   // Draw all ones in the window image matrix.
   void drawAllOnes(
      cv::Mat& aTarget);

   // Draw a border around the window image target region.
   void drawBorder(
      cv::Mat& aTarget);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


