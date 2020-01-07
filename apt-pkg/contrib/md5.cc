#include <config.h>

#include <apt-pkg/md5.h>
#include <gcrypt.h>

MD5Summation::MD5Summation() : SummationImplementation(GCRY_MD_MD5)
{
}

MD5SumValue MD5Summation::Result()
{
   MD5SumValue V;
   V.Set((unsigned char *)InternalResult());
   return V;
}
