// Cryptographic API Base
#include <config.h>

#include <apt-pkg/fileutl.h>

#include "hashsum_template.h"
#include <algorithm>
#include <unistd.h>
#include <assert.h>

#include <gcrypt.h>

struct SummationImplementation::Private {
   gcry_md_hd_t hd;
};

SummationImplementation::~SummationImplementation() {
   delete d;
}
SummationImplementation::SummationImplementation(int hashtype) : d(nullptr) {
   if (hashtype == 0)
      return;

   d = new Private();
   gcry_md_open(&d->hd, hashtype, 0);
}

// Summation::AddFD - Add content of file into the checksum		/*{{{*/
// ---------------------------------------------------------------------
/* */

bool SummationImplementation::Add(const unsigned char *inbuf, unsigned long long inlen)
{
   assert(d != nullptr);
   gcry_md_write(d->hd, inbuf, inlen);
   return true;
}
const unsigned char *SummationImplementation::InternalResult()
{
   gcry_md_hd_t hd;

   assert(d != nullptr);

   gcry_md_copy(&hd, d->hd);
   return gcry_md_read(hd, 0);
}

bool SummationImplementation::AddFD(int const Fd, unsigned long long Size) {
   unsigned char Buf[64 * 64];
   bool const ToEOF = (Size == 0);
   while (Size != 0 || ToEOF)
   {
      unsigned long long n = sizeof(Buf);
      if (!ToEOF) n = std::min(Size, n);
      ssize_t const Res = read(Fd, Buf, n);
      if (Res < 0 || (!ToEOF && Res != (ssize_t) n)) // error, or short read
	 return false;
      if (ToEOF && Res == 0) // EOF
	 break;
      Size -= Res;
      Add(Buf,Res);
   }
   return true;
}
bool SummationImplementation::AddFD(FileFd &Fd, unsigned long long Size) {
   unsigned char Buf[64 * 64];
   bool const ToEOF = (Size == 0);
   while (Size != 0 || ToEOF)
   {
      unsigned long long n = sizeof(Buf);
      if (!ToEOF) n = std::min(Size, n);
      unsigned long long a = 0;
      if (Fd.Read(Buf, n, &a) == false) // error
	 return false;
      if (ToEOF == false)
      {
	 if (a != n) // short read
	    return false;
      }
      else if (a == 0) // EOF
	 break;
      Size -= a;
      Add(Buf, a);
   }
   return true;
}
									/*}}}*/
