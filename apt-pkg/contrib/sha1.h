// -*- mode: cpp; mode: fold -*-
// Description								/*{{{*/
/* ######################################################################

   SHA1SumValue - Storage for a SHA-1 hash.
   SHA1Summation - SHA-1 Secure Hash Algorithm.
   
   This is a C++ interface to a set of SHA1Sum functions, that mirrors
   the equivalent MD5 classes. 

   ##################################################################### */
									/*}}}*/
#ifndef APTPKG_SHA1_H
#define APTPKG_SHA1_H

#include "hashsum_template.h"


typedef  HashSumValue<160> SHA1SumValue;

struct SHA1Summation : public SummationImplementation
{
   SHA1SumValue Result();
   SHA1Summation();
};

#endif
