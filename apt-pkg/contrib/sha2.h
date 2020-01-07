// -*- mode: cpp; mode: fold -*-
// Description                                                          /*{{{*/
/* ######################################################################

   SHA{512,256}SumValue - Storage for a SHA-{512,256} hash.
   SHA{512,256}Summation - SHA-{512,256} Secure Hash Algorithm.
   
   This is a C++ interface to a set of SHA{512,256}Sum functions, that mirrors
   the equivalent MD5 & SHA1 classes. 

   ##################################################################### */
                                                                        /*}}}*/
#ifndef APTPKG_SHA2_H
#define APTPKG_SHA2_H

#include <cstring>

#include "hashsum_template.h"


typedef HashSumValue<512> SHA512SumValue;
typedef HashSumValue<256> SHA256SumValue;

struct SHA256Summation : public SummationImplementation
{
   SHA256SumValue Result();
   SHA256Summation();
};

struct SHA512Summation : public SummationImplementation
{
   SHA512SumValue Result();
   SHA512Summation();
};


#endif
