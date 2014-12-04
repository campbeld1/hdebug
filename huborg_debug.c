#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_syslog.h"
 
#define PHP_HUBORG_DEBUG_VERSION "1.0"
#define PHP_HUBORG_DEBUG_EXTNAME "huborg_debug"
 
extern zend_module_entry huborg_debug_module_entry;
#define phpext_huborg_debug_ptr &huborg_debug_module_entry

zend_op_array* (*old_compile_file)(zend_file_handle* file_handle, int type TSRMLS_DC);
zend_op_array* huborg_debug_compile_file(zend_file_handle*, int TSRMLS_DC);
 
// declaration of a custom my_function()
PHP_FUNCTION(my_function);
PHP_MINIT_FUNCTION(huborg_debug);
 
// list of custom PHP functions provided by this extension
// set {NULL, NULL, NULL} as the last record to mark the end of list
static zend_function_entry my_functions[] = {
    PHP_FE(my_function, NULL)
    {NULL, NULL, NULL}
};
 
// the following code creates an entry for the module and registers it with Zend.
zend_module_entry huborg_debug_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_HUBORG_DEBUG_EXTNAME,
    my_functions,
    PHP_MINIT(huborg_debug), // name of the MINIT function or NULL if not applicable
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    NULL, // name of the MINFO function or NULL if not applicable
#if ZEND_MODULE_API_NO >= 20010901
    PHP_HUBORG_DEBUG_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
 
ZEND_GET_MODULE(huborg_debug)


PHP_MINIT_FUNCTION(huborg_debug)
{
old_compile_file = zend_compile_file;
zend_compile_file = huborg_debug_compile_file;

return SUCCESS;
}
 
// implementation of a custom my_function()
PHP_FUNCTION(my_function)
{
    RETURN_STRING("This is my function", 1);
}

zend_op_array *huborg_debug_compile_file(zend_file_handle *file_handle, int type TSRMLS_DC)
{
zend_op_array *op_array;
char str_result[MAXPATHLEN+80];



op_array = old_compile_file(file_handle, type TSRMLS_CC);
if (op_array) {
openlog("php-milter", LOG_PID, LOG_MAIL);
zend_sprintf(str_result,"Compiling: %s", file_handle->filename);
syslog(1, str_result);
closelog();
//zend_printf("Compiling: %s", file_handle->filename);
}
return op_array;
}
