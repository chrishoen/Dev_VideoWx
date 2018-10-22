#pragma once

/*==============================================================================
Some namespace: sixdofs that are measured by a computer vision based system.
Target painter. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "cmnImageBitMap.h"
#include "svTargetParms.h"
#include "svObjectPointArray.h"

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
   TargetParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.

   // Constructor.
   ImagePainter();
   ImagePainter(TargetParms* aParms);
   void initialize(TargetParms* aParms);
   void reset();
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Paint the target image with a reference pattern. The input is a code that
   // specifies the pattern. This is used to display checkerboards and gray
   // cards.
   void doPaintTargetWithReference(
      int                aReferenceCode,    // Input   
      Cmn::ImageBitMap*& aTargetBitMap);    // Output

   // Paint the target image with a grid of object points. The input is a
   // list of target object points. The output is a target window image
   // matrix. This initializes the output window image matrix and then writes
   // pixel values to it. This paints all of the target object points as
   // pixels in the window image target region.
   void doPaintTargetWithGrid(
      Some::ObjectPointArray& aTargetObjectPoints,    // Input
      Cmn::ImageBitMap*&    aTargetBitMap);         // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   // Window painters.

   // Initialize the window image matrix to zeroes.
   void initializeTargetBitMap(
      Cmn::ImageBitMap*& aTargetBitMap);


   // Draw a checkerboard in the window image matrix target region.
   void drawCheckerBoard(
      Cmn::ImageBitMap*& aTargetBitMap,
      int       aWidthX,
      int       aWidthY);

   // Draw reticle in the window image matrix target region
   void drawReticle(
      Cmn::ImageBitMap*& aTargetBitMap,
      int       aWidthX,
      int       aWidthY);

   // Draw all zeroes in the window image matrix.
   void drawAllZeroes(
      Cmn::ImageBitMap*& aTargetBitMap);

   // Draw all ones in the window image matrix.
   void drawAllOnes(
      Cmn::ImageBitMap*& aTargetBitMap);

   // Draw a border around the window image target region.
   void drawBorder(
      Cmn::ImageBitMap*& aTargetBitMap);

   // Draw each point in a list of object points in the window image
   // matrix target region.
   void drawObjectPoints(
      Cmn::ImageBitMap*& aTargetBitMap,
      Some::ObjectPointArray& aObjectPoints);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


