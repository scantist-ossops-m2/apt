/*
 * Basic implementation of string_view
 *
 * (C) 2015 Julian Andres Klode <jak@debian.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#if !defined(APT_STRINGVIEW_H) && defined(APT_PKG_EXPOSE_STRING_VIEW)
#define APT_STRINGVIEW_H
#include <experimental/string_view>
#include <string>

namespace APT {
using StringView = std::experimental::string_view;
}

#endif
