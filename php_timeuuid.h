/*
  +----------------------------------------------------------------------+
  | The MIT Licence (MIT)                                                |
  +----------------------------------------------------------------------+
  | Copyright (c) 2014 Mickael BLATIERE                                  |
  +----------------------------------------------------------------------+
  | Permission is hereby granted, free of charge, to any person          |
  | obtaining a copy of this software and associated documentation files |
  | (the "Software"), to deal in the Software without restriction,       |
  | including without limitation the rights to use, copy, modify, merge, |
  | publish, distribute, sublicense, and/or sell copies of the Software, |
  | and to permit persons to whom the Software is furnished to do so,    |
  | subject to the following conditions:                                 |
  |                                                                      |
  | The above copyright notice and this permission notice shall be       |
  | included in all copies or substantial portions of the Software.      |
  |                                                                      |
  | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      |
  | EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   |
  | MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                |
  | NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  |
  | BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   |
  | ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    |
  | CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     |
  | SOFTWARE.                                                            |
  +----------------------------------------------------------------------+
  | Author: Mickael BLATIERE <blatiere@gmail.com>                        |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_TIMEUUID_H
#define PHP_TIMEUUID_H

extern zend_module_entry timeuuid_module_entry;
#define phpext_timeuuid_ptr &timeuuid_module_entry

#define PHP_TIMEUUID_VERSION "0.2.0"

#ifdef PHP_WIN32
#    define PHP_TIMEUUID_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_TIMEUUID_API __attribute__ ((visibility("default")))
#else
#    define PHP_TIMEUUID_API
#endif

#if PHP_MAJOR_VERSION < 7
typedef int  strsize;
#define UUID_RETSTR(a)    RETURN_STRING(a,1)
#else
typedef size_t strsize;
#define UUID_RETSTR(a)    RETURN_STRING(a)
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(timeuuid);

PHP_FUNCTION(timeuuid);

#ifdef ZTS
#define TIMEUUID_G(v) TSRMG(timeuuid_globals_id, zend_timeuuid_globals *, v)
#else
#define TIMEUUID_G(v) (timeuuid_globals.v)
#endif

#endif    /* PHP_TIMEUUID_H */
