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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_timeuuid.h"

#include <uuid/uuid.h>

static strsize timeuuid_safe = 1;

/* {{{ timeuuid_functions[]
 */
const zend_function_entry timeuuid_functions[] = {
    PHP_FE(timeuuid,    NULL)
    PHP_FE_END
};
/* }}} */

/* {{{ timeuuid_module_entry
 */
zend_module_entry timeuuid_module_entry = {
    STANDARD_MODULE_HEADER,
    "timeuuid",
    timeuuid_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINFO(timeuuid),
    PHP_TIMEUUID_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TIMEUUID
ZEND_GET_MODULE(timeuuid)
#endif

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(timeuuid)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "timeuuid support", "enabled");
    php_info_print_table_header(2, "timeuuid version", PHP_TIMEUUID_VERSION);
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto string timeuuid(string arg)
 Generate a new time UUID */
PHP_FUNCTION(timeuuid)
{
    uuid_t uuid;
    char uuid_str[37];

    if (!timeuuid_safe || uuid_generate_time_safe(uuid) == -1) {
        php_error_docref(NULL TSRMLS_CC,
            E_WARNING,
            "UUID skipped because generated in an unsafe manner \
(are you sure uuidd daemon is running?)");
        // uuid_generate_time_safe return an error only in first call
        // we have to keep in mind first status
        // to avoid next generations after an error occured!
        timeuuid_safe = 0;
        // In case of unsafe uuid (no garantee of unicity)
        // prefer ignore it and return an empty value
        return;
    }

    uuid_unparse(uuid, uuid_str);
    UUID_RETSTR(uuid_str);
}
/* }}} */
