/*
   Copyright (C) 2007 - 2008 MySQL AB, 2008 - 2009 Sun Microsystems, Inc.

   The MySQL Connector/C++ is licensed under the terms of the GPL
   <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>, like most
   MySQL Connectors. There are special exceptions to the terms and
   conditions of the GPL as it is applied to this software, see the
   FLOSS License Exception
   <http://www.mysql.com/about/legal/licensing/foss-exception.html>.
*/
/*
  Some common definitions and inclusions for C/C++ tests.
*/

#ifndef __C_CPP_TYPES_H_
#define __C_CPP_TYPES_H_

#if defined(_WIN32) || defined(_WIN64)
/* MySQL 5.1 might have defined it before in include/config-win.h */
#ifdef strncasecmp
#undef strncasecmp
#endif

#define strncasecmp(s1,s2,n) _strnicmp(s1,s2,n)

#ifndef atoll
#define atoll(x) _atoi64((x))
#endif
#else
#include <string.h>
# ifdef __hpux
#  ifdef _PA_RISC2_0
#   define atoll(__a) atol(__a)
#   define strtoull(__a, __b, __c) strtoul(__a, __b, __c)
#  else
#   include <inttypes.h>
#   define atoll(__a) strtoimax(__a, NULL, 10)
#   define strtoull(__a, __b, __c) strtoumax(__a, __b, __c)
#  endif
# endif
#endif

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include <list>
#include <cctype>
/*#include <locale>*/

#ifndef _ABSTRACT
#define _ABSTRACT
#endif

#ifndef _PURE
#define _PURE =0
#endif

#ifndef L64
#ifdef _WIN32
#define L64(x) x##i64
#else
#define L64(x) x##LL
#endif
#endif

#ifndef UL64
#ifdef _WIN32
#define UL64(x) x##ui64
#else
#define UL64(x) x##ULL
#endif
#endif


/*----------------------------------------------------------------------------
ci_char_traits : Case-insensitive char traits.
Taken from : http://gcc.gnu.org/onlinedocs/libstdc++/21_strings/gotw29a.txt
and adapted as template for both 'char' and 'wchar_t' types.
----------------------------------------------------------------------------*/
template <typename charT> struct ci_char_traits
: public std::char_traits<charT>
// just inherit all the other functions
//  that we don't need to override
{
  static bool eq (charT c1, charT c2)
  {
    return std::tolower(c1) == std::tolower(c2);
  }

  static bool ne (charT c1, charT c2)
  {
    return std::tolower(c1) != std::tolower(c2);
  }

  static bool lt (charT c1, charT c2)
  {
    return std::tolower(c1) < std::tolower(c2);
  }

  static int compare (const charT* s1, const charT* s2, size_t n)
  {
    return strncasecmp(s1, s2, n);
  }

  static const charT* find (const charT* s, int n, charT a)
  {
    while (  --n >= 0 && std::tolower(*s) != std::tolower(a))
    {
      ++s;
    }
    return (n >= 0 ? s : 0);
  }
};

//Some stubs for unicode use. Following usual win scheme
#ifdef UNICODE_32BIT
typedef std::basic_string
<wchar_t,
std::char_traits<wchar_t>,
std::allocator<wchar_t> >
String;

#ifndef _T
#define _T(strConst) L ## strConst
#endif

#else
typedef std::basic_string
<char,
std::char_traits<char>,
std::allocator<char> >
String;

typedef std::basic_string
<char,
ci_char_traits<char>,
std::allocator<char> >
ciString;

#ifndef _T
#define _T(strConst) strConst
#endif

#endif

typedef std::vector<String> List;
typedef List::iterator Iterator;

typedef std::map<String, String> Properties;
typedef Properties::iterator  PropsIterator;

#endif /* __C_CPP_TYPES_H_ */
