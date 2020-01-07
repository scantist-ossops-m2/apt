#include <config.h>

#include <apt-pkg/sha1.h>
#include <gcrypt.h>

SHA1Summation::SHA1Summation() : SummationImplementation(GCRY_MD_SHA1)
{
}

SHA1SumValue SHA1Summation::Result()
{
   SHA1SumValue V;
   V.Set((unsigned char *)InternalResult());
   return V;
}
