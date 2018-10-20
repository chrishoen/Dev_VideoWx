
#include "stdafx.h"

#include "risThreadsProcess.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void main_initialize(int argc,char** argv)
{
   // Enter process.
   Ris::Threads::enterProcessHigh();

   // Initialize print facility.
   Prn::resetPrint();
   Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::SerialInitP1,    true);
   Prn::setFilter(Prn::SerialInitP2,    true);
   Prn::setFilter(Prn::SerialRxRunP1,   false);
   Prn::setFilter(Prn::SerialRxRunP2,   false);
   Prn::setFilter(Prn::SerialTxRunP1,   false);
   Prn::setFilter(Prn::SerialTxRunP2,   false);
   Prn::setFilter(Prn::SerialErrorP1,   true);
   Prn::setFilter(Prn::SerialErrorP2,   true);

   Prn::setFilter(Prn::SerialInitM1,    true);
   Prn::setFilter(Prn::SerialInitM2,    true);
   Prn::setFilter(Prn::SerialRxRunM1,   false);
   Prn::setFilter(Prn::SerialRxRunM2,   false);
   Prn::setFilter(Prn::SerialTxRunM1,   false);
   Prn::setFilter(Prn::SerialTxRunM2,   false);
   Prn::setFilter(Prn::SerialErrorM1,   true);
   Prn::setFilter(Prn::SerialErrorM2,   true);

   Prn::setFilter(Prn::ThreadInit1,     true);
   Prn::setFilter(Prn::ThreadInit1,     true);
   Prn::setFilter(Prn::ThreadRun1,      true);
   Prn::setFilter(Prn::ThreadRun2,      true);
   Prn::setFilter(Prn::ThreadRun3,      true);
   Prn::setFilter(Prn::ThreadRun4,      true);

   Prn::setFilter(Prn::View01,          true);
   Prn::setFilter(Prn::View02,          true);
   Prn::setFilter(Prn::View11,          true,  1);
   Prn::setFilter(Prn::View12,          true,  1);
   Prn::setFilter(Prn::View21,          false, 2);
   Prn::setFilter(Prn::View21,          false, 2);

   // Done.
   Prn::print(0,"VThread Program**********************************************BEGIN");

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   Prn::print(0,"VThread Program**********************************************END");

   // Close print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
