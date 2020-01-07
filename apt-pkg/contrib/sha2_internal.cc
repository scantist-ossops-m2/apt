#include <config.h>

#include <apt-pkg/sha2.h>
#include <gcrypt.h>

SHA256Summation::SHA256Summation() : SummationImplementation(GCRY_MD_SHA256)
{
}

SHA512Summation::SHA512Summation() : SummationImplementation(GCRY_MD_SHA512)
{
}

SHA512SumValue SHA512Summation::Result()
{
   SHA512SumValue V;
   V.Set((unsigned char *)InternalResult());
   return V;
}

SHA256SumValue SHA256Summation::Result()
{
   SHA256SumValue V;
   V.Set((unsigned char *)InternalResult());
   return V;
}
