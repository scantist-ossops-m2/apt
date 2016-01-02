// -*- mode: cpp; mode: fold -*-
// Description								/*{{{*/
// $Id: tagfile.cc,v 1.37.2.2 2003/12/31 16:02:30 mdz Exp $
/* ######################################################################

   Fast scanner for RFC-822 type header information

   This uses a rotating buffer to load the package information into.
   The scanner runs over it and isolates and indexes a single section.

   This defines compat functions for the external code.

   ##################################################################### */
									/*}}}*/

#include<config.h>
#define APT_COMPILING_TAGFILE_COMPAT_CC
#include <apt-pkg/tagfile.h>

using std::string;
using std::experimental::string_view;


bool pkgTagSection::Exists(const char* const Tag) const
{
   return Exists(string_view(Tag));
}

bool pkgTagSection::Find(const char *Tag,unsigned int &Pos) const
{
   return Find(string_view(Tag), Pos);
}

bool pkgTagSection::Find(const char *Tag,const char *&Start,
		         const char *&End) const
{
   return Find(string_view(Tag), Start, End);
}

string pkgTagSection::FindS(const char *Tag) const
{
   return Find(string_view(Tag)).to_string();
}

string pkgTagSection::FindRawS(const char *Tag) const
{
   return FindRaw(string_view(Tag)).to_string();
}

signed int pkgTagSection::FindI(const char *Tag,signed long Default) const
{
    return FindI(string_view(Tag), Default);
}

unsigned long long pkgTagSection::FindULL(const char *Tag, unsigned long long const &Default) const
{
   return FindULL(string_view(Tag), Default);
}
									/*}}}*/

bool pkgTagSection::FindB(const char *Tag, bool const &Default) const
{
   return FindB(string_view(Tag), Default);
}

bool pkgTagSection::FindFlag(const char * const Tag, uint8_t &Flags,
			     uint8_t const Flag) const
{
    return FindFlag(string_view(Tag), Flags, Flag);
}

bool pkgTagSection::FindFlag(const char *Tag,unsigned long &Flags,
			     unsigned long Flag) const
{
   return FindFlag(string_view(Tag), Flags, Flag);
}
