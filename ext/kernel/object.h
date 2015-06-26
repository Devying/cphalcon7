
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifndef PHALCON_KERNEL_OBJECT_H
#define PHALCON_KERNEL_OBJECT_H

#include "php_phalcon.h"

/** Class Retrieving/Checking */
zend_class_entry *phalcon_class_exists(const zval *class_name, int autoload) PHALCON_ATTR_NONNULL;
zend_class_entry *phalcon_class_exists_ex(const zval *class_name, int autoload) PHALCON_ATTR_NONNULL;
zend_class_entry *phalcon_class_str_exists(const char *class_name, uint32_t class_len, int autoload) PHALCON_ATTR_NONNULL;
int phalcon_interface_exists(const zval *interface_name, int autoload TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_class(zval *result, const zval *object, int lower TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_class_ns(zval *result, const zval *object, int lower TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_ns_class(zval *result, const zval *object, int lower TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_called_class(zval *return_value TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_parent_class(zval *result, const zval *object, int lower TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_object_vars(zval *result, zval *object, int check_access TSRMLS_DC) PHALCON_ATTR_NONNULL;
void phalcon_get_class_methods(zval *result, zval *object, int check_access TSRMLS_DC) PHALCON_ATTR_NONNULL;
zend_class_entry* phalcon_fetch_class(const zval *class_name TSRMLS_DC) PHALCON_ATTR_NONNULL;
zend_class_entry* phalcon_fetch_self_class(TSRMLS_D);
zend_class_entry* phalcon_fetch_parent_class(TSRMLS_D);
zend_class_entry* phalcon_fetch_static_class(TSRMLS_D);

#define PHALCON_GET_CLASS_CONSTANT(return_value, ce, const_name) \
	do { \
		if (FAILURE == phalcon_get_class_constant(return_value, ce, const_name, strlen(const_name)+1 TSRMLS_CC)) { \
			PHALCON_MM_RESTORE(); \
			return; \
		} \
	} while (0)
/** Class constants */
int phalcon_get_class_constant(zval *return_value, const zend_class_entry *ce, const char *constant_name, uint32_t constant_length TSRMLS_DC) PHALCON_ATTR_NONNULL;

/** Cloning */
int phalcon_clone(zval *destination, zval *obj TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_instance_of(zval *result, const zval *object, const zend_class_entry *ce TSRMLS_DC);
int phalcon_is_instance_of(zval *object, const char *class_name, unsigned int class_length TSRMLS_DC);
int phalcon_instance_of_ev(const zval *object, const zend_class_entry *ce TSRMLS_DC);
int phalcon_zval_is_traversable(zval *object TSRMLS_DC);

/** Method exists */
int phalcon_method_exists(const zval *object, const zval *method_name TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_method_exists_ex(const zval *object, const char *method_name, uint32_t method_len TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_method_exists_ce(const zend_class_entry *ce, const zval *method_name TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_method_exists_ce_ex(const zend_class_entry *ce, const char *method_name, uint32_t method_len TSRMLS_DC) PHALCON_ATTR_NONNULL;

/** Isset properties */
int phalcon_isset_property(zval *object, const char *property_name, uint32_t property_length TSRMLS_DC) PHALCON_ATTR_NONNULL;

/**
 * Checks if string property exists on object
 */
PHALCON_ATTR_NONNULL static inline int phalcon_isset_property_zval(zval *object, const zval *property TSRMLS_DC)
{
	if (Z_TYPE_P(property) == IS_STRING) {
		return phalcon_isset_property(object, Z_STRVAL_P(property), Z_STRLEN_P(property) + 1 TSRMLS_CC);
	}

	return 0;
}

/** Reading properties */
zval* phalcon_fetch_property_this_quick(zval *object, const char *property_name, uint32_t property_length, ulong key, int silent TSRMLS_DC);
int phalcon_read_property(zval **result, zval *object, const char *property_name, uint32_t property_length, int silent TSRMLS_DC);
int phalcon_read_property_zval(zval **result, zval *object, const zval *property, int silent TSRMLS_DC);
int phalcon_return_property_quick(zval *return_value, zval **return_value_ptr, zval *object, const char *property_name, uint32_t property_length, ulong key TSRMLS_DC);

/**
 * Reads a property from this_ptr (with pre-calculated key)
 * Variables must be defined in the class definition. This function ignores magic methods or dynamic properties
 */
PHALCON_ATTR_NONNULL static inline int phalcon_read_property_this_quick(zval **result, zval *object, const char *property_name, uint32_t property_length, ulong key, int silent TSRMLS_DC)
{
	zval *tmp = phalcon_fetch_property_this_quick(object, property_name, property_length, key, silent TSRMLS_CC);
	if (EXPECTED(tmp != NULL)) {
		*result = tmp;
		Z_ADDREF_P(*result);
		return SUCCESS;
	}

	ALLOC_INIT_ZVAL(*result);
	return FAILURE;
}

/**
 * Reads a property from this_ptr
 * Variables must be defined in the class definition. This function ignores magic methods or dynamic properties
 */
PHALCON_ATTR_NONNULL static inline int phalcon_read_property_this(zval **result, zval *object, const char *property_name, uint32_t property_length, int silent TSRMLS_DC)
{
#ifdef __GNUC__
	if (__builtin_constant_p(property_name) && __builtin_constant_p(property_length)) {
		return phalcon_read_property_this_quick(result, object, property_name, property_length, zend_inline_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
	}
#endif

	return phalcon_read_property_this_quick(result, object, property_name, property_length, zend_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
}

PHALCON_ATTR_NONNULL static inline zval* phalcon_fetch_nproperty_this_quick(zval *object, const char *property_name, uint32_t property_length, ulong key, int silent TSRMLS_DC)
{
#ifdef __GNUC__
	if (__builtin_constant_p(property_name) && __builtin_constant_p(property_length)) {
		zval *result = phalcon_fetch_property_this_quick(object, property_name, property_length, zend_inline_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
		return result ? result : EG(uninitialized_zval_ptr);
	}
#endif

	zval *result = phalcon_fetch_property_this_quick(object, property_name, property_length, zend_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
	return result ? result : EG(uninitialized_zval_ptr);
}

PHALCON_ATTR_NONNULL static inline zval* phalcon_fetch_nproperty_this(zval *object, const char *property_name, uint32_t property_length, int silent TSRMLS_DC)
{
#ifdef __GNUC__
	if (__builtin_constant_p(property_name) && __builtin_constant_p(property_length)) {
		return phalcon_fetch_nproperty_this_quick(object, property_name, property_length, zend_inline_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
	}
#endif

	return phalcon_fetch_nproperty_this_quick(object, property_name, property_length, zend_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
}

PHALCON_ATTR_NONNULL static inline zval* phalcon_fetch_nproperty_this_zval(zval *object, const zval *property, int silent TSRMLS_DC)
{
	return phalcon_fetch_nproperty_this_quick(object, Z_STRVAL_P(property), Z_STRLEN_P(property), zend_hash_func(Z_STRVAL_P(property), Z_STRLEN_P(property) + 1), silent TSRMLS_CC);
}

PHALCON_ATTR_NONNULL static inline zval* phalcon_fetch_property_this(zval *object, const char *property_name, uint32_t property_length, int silent TSRMLS_DC)
{
#ifdef __GNUC__
	if (__builtin_constant_p(property_name) && __builtin_constant_p(property_length)) {
		return phalcon_fetch_property_this_quick(object, property_name, property_length, zend_inline_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
	}
#endif

	return phalcon_fetch_property_this_quick(object, property_name, property_length, zend_hash_func(property_name, property_length + 1), silent TSRMLS_CC);
}

/**
 * Returns an object's member
 */
PHALCON_ATTR_NONNULL3(1,3,4) static inline int phalcon_return_property(zval *return_value, zval **return_value_ptr, zval *object, const char *property_name, uint32_t property_length TSRMLS_DC)
{
#ifdef __GNUC__
	if (__builtin_constant_p(property_name) && __builtin_constant_p(property_length)) {
		return phalcon_return_property_quick(return_value, return_value_ptr, object, property_name, property_length, zend_inline_hash_func(property_name, property_length + 1) TSRMLS_CC);
	}
#endif

	return phalcon_return_property_quick(return_value, return_value_ptr, object, property_name, property_length, zend_hash_func(property_name, property_length + 1) TSRMLS_CC);
}


/** Updating properties */
int phalcon_update_property_long(zval *obj, const char *property_name, uint32_t property_length, long value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_string(zval *object, const char *property_name, uint32_t property_length, const char *str, uint32_t str_length TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_bool(zval *obj, const char *property_name, uint32_t property_length, int value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_null(zval *obj, const char *property_name, uint32_t property_length TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_zval(zval *obj, const char *property_name, uint32_t property_length, zval *value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_zval_long(zval *obj, const zval *property, int value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_zval_zval(zval *obj, const zval *property, zval *value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_empty_array(zval *object, const char *property, uint32_t property_length TSRMLS_DC) PHALCON_ATTR_NONNULL;

int phalcon_update_property_this(zval *object, const char *property_name, uint32_t property_length, zval *value TSRMLS_DC);

/** Updating array properties */
int phalcon_update_property_array(zval *object, const char *property, uint32_t property_length, const zval *index, zval *value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_array_multi(zval *object, const char *property, uint32_t property_length, zval *value TSRMLS_DC, const char *types, int types_length, int types_count, ...);
int phalcon_update_property_array_string(zval *object, const char *property, uint32_t property_length, const char *index, uint32_t index_length, zval *value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_array_append(zval *object, const char *property, uint32_t property_length, zval *value TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_array_merge(zval *object, const char *property, uint32_t property_length, zval *values TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_property_array_merge_append(zval *object, const char *property, uint32_t property_length, zval *values TSRMLS_DC) PHALCON_ATTR_NONNULL;

/** Increment/Decrement properties */
int phalcon_property_incr(zval *object, const char *property_name, uint32_t property_length TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_property_decr(zval *object, const char *property_name, uint32_t property_length TSRMLS_DC) PHALCON_ATTR_NONNULL;

/** Unset Array properties */
int phalcon_unset_property_array(zval *object, const char *property, uint32_t property_length, const zval *index TSRMLS_DC) PHALCON_ATTR_NONNULL;

/** Static properties */
int phalcon_read_static_property(zval **result, const char *class_name, uint32_t class_length, const char *property_name, uint32_t property_length TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_read_class_property(zval **result, int type, const char *property, uint32_t len TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_update_static_property_array_multi_ce(zend_class_entry *ce, const char *property, uint32_t property_length, zval *value TSRMLS_DC, const char *types, int types_length, int types_count, ...);

PHALCON_ATTR_NONNULL static inline zval* phalcon_fetch_static_property_ce(zend_class_entry *ce, const char *property, uint32_t len TSRMLS_DC)
{
#if PHP_VERSION_ID < 50400
	return zend_read_static_property(ce, (char*)property, len, (zend_bool)ZEND_FETCH_CLASS_SILENT TSRMLS_CC);
#else
	return zend_read_static_property(ce, property, len, (zend_bool)ZEND_FETCH_CLASS_SILENT TSRMLS_CC);
#endif
}

PHALCON_ATTR_NONNULL static inline int phalcon_read_static_property_ce(zval **result, zend_class_entry *ce, const char *property, uint32_t len TSRMLS_DC)
{
	*result = phalcon_fetch_static_property_ce(ce, property, len TSRMLS_CC);
	if (*result) {
		Z_ADDREF_P(*result);
		return SUCCESS;
	}

	return FAILURE;
}

PHALCON_ATTR_NONNULL static inline int phalcon_update_static_property_ce(zend_class_entry *ce, const char *name, uint32_t len, zval *value TSRMLS_DC)
{
#if PHP_VERSION_ID < 50400
	return zend_update_static_property(ce, (char*)name, len, value TSRMLS_CC);
#else
	return zend_update_static_property(ce, name, len, value TSRMLS_CC);
#endif
}

/**
 * Update a static property
 */
PHALCON_ATTR_NONNULL static inline int phalcon_update_static_property(const char *class_name, uint32_t class_length, const char *name, uint32_t name_length, zval *value TSRMLS_DC)
{
	zend_class_entry **ce;
	if (zend_lookup_class(class_name, class_length, &ce TSRMLS_CC) == SUCCESS) {
		return phalcon_update_static_property_ce(*ce, name, name_length, value TSRMLS_CC);
	}

	return FAILURE;
}


/** Create instances */
int phalcon_create_instance_params_ce(zval *return_value, zend_class_entry *ce, zval *params TSRMLS_DC) PHALCON_ATTR_NONNULL2(1, 2);
int phalcon_create_instance(zval *return_value, const zval *class_name TSRMLS_DC) PHALCON_ATTR_NONNULL;
int phalcon_create_instance_params(zval *return_value, const zval *class_name, zval *params TSRMLS_DC) PHALCON_ATTR_NONNULL2(1, 2);

/** Create closures */
int phalcon_create_closure_ex(zval *return_value, zval *this_ptr, zend_class_entry *ce, const char *method_name, uint32_t method_length TSRMLS_DC);

#if PHP_VERSION_ID < 50400
void object_properties_init(zend_object *object, zend_class_entry *class_type);
#endif

/** Checks if property access on object */
int phalcon_check_property_access_quick(zval *object, const char *property_name, uint32_t property_length, ulong hash, int access TSRMLS_DC) PHALCON_ATTR_NONNULL;

PHALCON_ATTR_NONNULL static inline int phalcon_check_property_access(zval *object, const char *property_name, uint32_t property_length, int access TSRMLS_DC)
{
#ifdef __GNUC__
	if (__builtin_constant_p(property_name) && __builtin_constant_p(property_length)) {
		return phalcon_check_property_access_quick(object, property_name, property_length, zend_inline_hash_func(property_name, property_length), access TSRMLS_CC);
	}
#endif

	return phalcon_check_property_access_quick(object, property_name, property_length, zend_hash_func(property_name, property_length), access TSRMLS_CC);
}

PHALCON_ATTR_NONNULL static inline int phalcon_check_property_access_zval(zval *object, const zval *property, int access TSRMLS_DC)
{
	if (Z_TYPE_P(property) == IS_STRING) {
		ulong hash = zend_hash_func(Z_STRVAL_P(property), Z_STRLEN_P(property) + 1);
		return phalcon_check_property_access_quick(object, Z_STRVAL_P(property), Z_STRLEN_P(property) + 1, hash, access TSRMLS_CC);
	}

	return 0;
}

#define PHALCON_PROPERTY_IS_PUBLIC(object, property) \
	 phalcon_check_property_access(object, property, strlen(property), ZEND_ACC_PUBLIC TSRMLS_CC)

#define PHALCON_PROPERTY_IS_PROTECTED(object, property) \
	 phalcon_check_property_access(object, property, strlen(property), ZEND_ACC_PROTECTED TSRMLS_CC)

#define PHALCON_PROPERTY_IS_PRIVATE(object, property) \
	 phalcon_check_property_access(object, property, strlen(property), ZEND_ACC_PRIVATE TSRMLS_CC)

#define PHALCON_PROPERTY_IS_PUBLIC_ZVAL(object, property) \
	 phalcon_check_property_access_zval(object, property, ZEND_ACC_PUBLIC TSRMLS_CC)

#define PHALCON_PROPERTY_IS_PROTECTED_ZVAL(object, property) \
	 phalcon_check_property_access_zval(object, property, ZEND_ACC_PROTECTED TSRMLS_CC)

#define PHALCON_PROPERTY_IS_PRIVATE_ZVAL(object, property) \
	 phalcon_check_property_access_zval(object, property, ZEND_ACC_PRIVATE TSRMLS_CC)

#endif /* PHALCON_KERNEL_OBJECT_H */
