
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

#include "kernel/concat.h"

#include <ext/standard/php_string.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/string.h"

void phalcon_concat_sv(zval **result, const char *op1, uint32_t op1_len, zval *op2, int self_var TSRMLS_DC){

	zval result_copy, op2_copy;
	int use_copy = 0, use_copy2 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svs(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, int self_var TSRMLS_DC){

	zval result_copy, op2_copy;
	int use_copy = 0, use_copy2 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svsv(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, zval *op4, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svsvs(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, zval *op4, const char *op5, uint32_t op5_len, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4), op5, op5_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svsvsv(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, zval *op4, const char *op5, uint32_t op5_len, zval *op6, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy, op6_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0, use_copy6 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op6) != IS_STRING) {
		zend_make_printable_zval(op6, &op6_copy, &use_copy6);
		if (use_copy6) {
			op6 = &op6_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4), op5, op5_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len, Z_STRVAL_P(op6), Z_STRLEN_P(op6));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy6) {
		phalcon_dtor(op6);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svsvsvs(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, zval *op4, const char *op5, uint32_t op5_len, zval *op6, const char *op7, uint32_t op7_len, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy, op6_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0, use_copy6 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op6) != IS_STRING) {
		zend_make_printable_zval(op6, &op6_copy, &use_copy6);
		if (use_copy6) {
			op6 = &op6_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6) + op7_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4), op5, op5_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len, Z_STRVAL_P(op6), Z_STRLEN_P(op6));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6), op7, op7_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy6) {
		phalcon_dtor(op6);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svsvsvsvs(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, zval *op4, const char *op5, uint32_t op5_len, zval *op6, const char *op7, uint32_t op7_len, zval *op8, const char *op9, uint32_t op9_len, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy, op6_copy, op8_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0, use_copy6 = 0, use_copy8 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op6) != IS_STRING) {
		zend_make_printable_zval(op6, &op6_copy, &use_copy6);
		if (use_copy6) {
			op6 = &op6_copy;
		}
	}

	if (Z_TYPE_P(op8) != IS_STRING) {
		zend_make_printable_zval(op8, &op8_copy, &use_copy8);
		if (use_copy8) {
			op8 = &op8_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6) + op7_len + Z_STRLEN_P(op8) + op9_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4), op5, op5_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len, Z_STRVAL_P(op6), Z_STRLEN_P(op6));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6), op7, op7_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6) + op7_len, Z_STRVAL_P(op8), Z_STRLEN_P(op8));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6) + op7_len + Z_STRLEN_P(op8), op9, op9_len);

	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy6) {
		phalcon_dtor(op6);
	}

	if (use_copy8) {
		phalcon_dtor(op8);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svsvv(zval **result, const char *op1, uint32_t op1_len, zval *op2, const char *op3, uint32_t op3_len, zval *op4, zval *op5, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy, op5_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0, use_copy5 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4) + Z_STRLEN_P(op5);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4), Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svv(zval **result, const char *op1, uint32_t op1_len, zval *op2, zval *op3, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op3_copy;
	int use_copy = 0, use_copy2 = 0, use_copy3 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + Z_STRLEN_P(op3);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_svvs(zval **result, const char *op1, uint32_t op1_len, zval *op2, zval *op3, const char *op4, uint32_t op4_len, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op3_copy;
	int use_copy = 0, use_copy2 = 0, use_copy3 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + op4_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_P(*result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + op1_len + Z_STRLEN_P(op2) + Z_STRLEN_P(op3), op4, op4_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vs(zval **result, zval *op1, const char *op2, uint32_t op2_len, int self_var TSRMLS_DC){

	zval result_copy, op1_copy;
	int use_copy = 0, use_copy1 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsv(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsvs(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, const char *op4, uint32_t op4_len, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3), op4, op4_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsvsv(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, const char *op4, uint32_t op4_len, zval *op5, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy, op5_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0, use_copy5 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3), op4, op4_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len, Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsvsvs(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, const char *op4, uint32_t op4_len, zval *op5, const char *op6, uint32_t op6_len, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy, op5_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0, use_copy5 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5) + op6_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3), op4, op4_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len, Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5), op6, op6_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsvsvsv(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, const char *op4, uint32_t op4_len, zval *op5, const char *op6, uint32_t op6_len, zval *op7, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy, op5_copy, op7_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0, use_copy5 = 0, use_copy7 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	if (Z_TYPE_P(op7) != IS_STRING) {
		zend_make_printable_zval(op7, &op7_copy, &use_copy7);
		if (use_copy7) {
			op7 = &op7_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5) + op6_len + Z_STRLEN_P(op7);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3), op4, op4_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len, Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5), op6, op6_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5) + op6_len, Z_STRVAL_P(op7), Z_STRLEN_P(op7));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy7) {
		phalcon_dtor(op7);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsvv(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, zval *op4, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy, op4_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0, use_copy4 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + Z_STRLEN_P(op4);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3), Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vsvvv(zval **result, zval *op1, const char *op2, uint32_t op2_len, zval *op3, zval *op4, zval *op5, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op3_copy, op4_copy, op5_copy;
	int use_copy = 0, use_copy1 = 0, use_copy3 = 0, use_copy4 = 0, use_copy5 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	length = Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + Z_STRLEN_P(op4) + Z_STRLEN_P(op5);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), op2, op2_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len, Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3), Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + op2_len + Z_STRLEN_P(op3) + Z_STRLEN_P(op4), Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vv(zval **result, zval *op1, zval *op2, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvs(zval **result, zval *op1, zval *op2, const char *op3, uint32_t op3_len, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + op3_len;
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), op3, op3_len);
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvsv(zval **result, zval *op1, zval *op2, const char *op3, uint32_t op3_len, zval *op4, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy, op4_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0, use_copy4 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvv(zval **result, zval *op1, zval *op2, zval *op3, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy, op3_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0, use_copy3 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvvsv(zval **result, zval *op1, zval *op2, zval *op3, const char *op4, uint32_t op4_len, zval *op5, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy, op3_copy, op5_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0, use_copy3 = 0, use_copy5 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + op4_len + Z_STRLEN_P(op5);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3), op4, op4_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + op4_len, Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvvv(zval **result, zval *op1, zval *op2, zval *op3, zval *op4, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy, op3_copy, op4_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0, use_copy3 = 0, use_copy4 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3), Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvvvsvv(zval **result, zval *op1, zval *op2, zval *op3, zval *op4, const char *op5, uint32_t op5_len, zval *op6, zval *op7, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy, op3_copy, op4_copy, op6_copy, op7_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0, use_copy3 = 0, use_copy4 = 0, use_copy6 = 0, use_copy7 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op6) != IS_STRING) {
		zend_make_printable_zval(op6, &op6_copy, &use_copy6);
		if (use_copy6) {
			op6 = &op6_copy;
		}
	}

	if (Z_TYPE_P(op7) != IS_STRING) {
		zend_make_printable_zval(op7, &op7_copy, &use_copy7);
		if (use_copy7) {
			op7 = &op7_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6) + Z_STRLEN_P(op7);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3), Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4), op5, op5_len);
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4) + op5_len, Z_STRVAL_P(op6), Z_STRLEN_P(op6));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4) + op5_len + Z_STRLEN_P(op6), Z_STRVAL_P(op7), Z_STRLEN_P(op7));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy6) {
		phalcon_dtor(op6);
	}

	if (use_copy7) {
		phalcon_dtor(op7);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

void phalcon_concat_vvvvv(zval **result, zval *op1, zval *op2, zval *op3, zval *op4, zval *op5, int self_var TSRMLS_DC){

	zval result_copy, op1_copy, op2_copy, op3_copy, op4_copy, op5_copy;
	int use_copy = 0, use_copy1 = 0, use_copy2 = 0, use_copy3 = 0, use_copy4 = 0, use_copy5 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
		if (use_copy1) {
			op1 = &op1_copy;
		}
	}

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op3) != IS_STRING) {
		zend_make_printable_zval(op3, &op3_copy, &use_copy3);
		if (use_copy3) {
			op3 = &op3_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	if (Z_TYPE_P(op5) != IS_STRING) {
		zend_make_printable_zval(op5, &op5_copy, &use_copy5);
		if (use_copy5) {
			op5 = &op5_copy;
		}
	}

	length = Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4) + Z_STRLEN_P(op5);
	if (self_var) {

		if (Z_TYPE_P(*result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				PHALCON_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_P(*result);
		length += offset;
		Z_STRVAL_P(*result) = (char *) str_erealloc(Z_STRVAL_P(*result), length + 1);

	} else {
		Z_STRVAL_P(*result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_P(*result) + offset, Z_STRVAL_P(op1), Z_STRLEN_P(op1));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2), Z_STRVAL_P(op3), Z_STRLEN_P(op3));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3), Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	memcpy(Z_STRVAL_P(*result) + offset + Z_STRLEN_P(op1) + Z_STRLEN_P(op2) + Z_STRLEN_P(op3) + Z_STRLEN_P(op4), Z_STRVAL_P(op5), Z_STRLEN_P(op5));
	Z_STRVAL_P(*result)[length] = 0;
	Z_TYPE_P(*result) = IS_STRING;
	Z_STRLEN_P(*result) = length;

	if (use_copy1) {
		phalcon_dtor(op1);
	}

	if (use_copy2) {
		phalcon_dtor(op2);
	}

	if (use_copy3) {
		phalcon_dtor(op3);
	}

	if (use_copy4) {
		phalcon_dtor(op4);
	}

	if (use_copy5) {
		phalcon_dtor(op5);
	}

	if (use_copy) {
		phalcon_dtor(&result_copy);
	}

}

/**
 * Appends the content of the right operator to the left operator
 */
void phalcon_concat_self(zval **left, zval *right TSRMLS_DC){

	zval left_copy, right_copy;
	uint length;
	int use_copy_left = 0, use_copy_right = 0;

	if (Z_TYPE_P(right) != IS_STRING) {
		phalcon_make_printable_zval(right, &right_copy, &use_copy_right);
		if (use_copy_right) {
			right = &right_copy;
		}
	}

	if (Z_TYPE_P(*left) == IS_NULL) {

		Z_STRVAL_P(*left) = emalloc(Z_STRLEN_P(right) + 1);
		memcpy(Z_STRVAL_P(*left), Z_STRVAL_P(right), Z_STRLEN_P(right));
		Z_STRVAL_P(*left)[Z_STRLEN_P(right)] = 0;
		Z_STRLEN_P(*left) = Z_STRLEN_P(right);
		Z_TYPE_P(*left) = IS_STRING;

		if (use_copy_right) {
			phalcon_dtor(&right_copy);
		}

		return;
	}

	if (Z_TYPE_P(*left) != IS_STRING) {
		phalcon_make_printable_zval(*left, &left_copy, &use_copy_left);
		if (use_copy_left) {
			PHALCON_CPY_WRT_CTOR(*left, (&left_copy));
		}
	}

	SEPARATE_ZVAL_IF_NOT_REF(left);

	length = Z_STRLEN_P(*left) + Z_STRLEN_P(right);
	Z_STRVAL_P(*left) = str_erealloc(Z_STRVAL_P(*left), length + 1);

	memcpy(Z_STRVAL_P(*left) + Z_STRLEN_P(*left), Z_STRVAL_P(right), Z_STRLEN_P(right));
	Z_STRVAL_P(*left)[length] = 0;
	Z_STRLEN_P(*left) = length;
	Z_TYPE_P(*left) = IS_STRING;

	if (use_copy_left) {
		phalcon_dtor(&left_copy);
	}

	if (use_copy_right) {
		phalcon_dtor(&right_copy);
	}
}

/**
 * Appends the content of the right operator to the left operator
 */
void phalcon_concat_self_str(zval **left, const char *right, int right_length TSRMLS_DC){

	zval left_copy;
	uint length;
	int use_copy = 0;

	if (Z_TYPE_P(*left) == IS_NULL) {

		Z_STRVAL_P(*left) = emalloc(right_length + 1);
		memcpy(Z_STRVAL_P(*left), right, right_length);
		Z_STRVAL_P(*left)[right_length] = 0;
		Z_STRLEN_P(*left) = right_length;
		Z_TYPE_P(*left) = IS_STRING;

		return;
	}

	if (Z_TYPE_P(*left) != IS_STRING) {
		phalcon_make_printable_zval(*left, &left_copy, &use_copy);
		if (use_copy) {
			PHALCON_CPY_WRT_CTOR(*left, (&left_copy));
		}
	}

	SEPARATE_ZVAL_IF_NOT_REF(left);

	length = Z_STRLEN_P(*left) + right_length;
	Z_STRVAL_P(*left) = str_erealloc(Z_STRVAL_P(*left), length + 1);

	memcpy(Z_STRVAL_P(*left) + Z_STRLEN_P(*left), right, right_length);
	Z_STRVAL_P(*left)[length] = 0;
	Z_STRLEN_P(*left) = length;
	Z_TYPE_P(*left) = IS_STRING;

	if (use_copy) {
		phalcon_dtor(&left_copy);
	}
}

/**
* Appends the content of the right operator to the left operator
 */
void phalcon_concat_self_long(zval **left, const long right TSRMLS_DC) {

	zval left_copy;
	uint length;
	char *right_char;
	int use_copy = 0, right_length = 0;

	right_length = phalcon_spprintf(&right_char, 0, "%ld", right);

	if (Z_TYPE_P(*left) == IS_NULL) {
		Z_STRVAL_P(*left) = emalloc(right_length + 1);
		if (right_length > 0) {
			memcpy(Z_STRVAL_P(*left), right_char, right_length);
		} else {
			memcpy(Z_STRVAL_P(*left), "", 0);
		}
		Z_STRVAL_P(*left)[right_length] = 0;
		Z_STRLEN_P(*left) = right_length;
		Z_TYPE_P(*left) = IS_STRING;
		return;
	}

	if (Z_TYPE_P(*left) != IS_STRING) {
		phalcon_make_printable_zval(*left, &left_copy, &use_copy);
		if (use_copy) {
			PHALCON_CPY_WRT_CTOR(*left, (&left_copy));
		}
	}

	if (right_length > 0) {

		SEPARATE_ZVAL_IF_NOT_REF(left);

		length = Z_STRLEN_P(*left) + right_length;
		Z_STRVAL_P(*left) = str_erealloc(Z_STRVAL_P(*left), length + 1);
		memcpy(Z_STRVAL_P(*left) + Z_STRLEN_P(*left), right_char, right_length);
		Z_STRVAL_P(*left)[length] = 0;
		Z_STRLEN_P(*left) = length;
		Z_TYPE_P(*left) = IS_STRING;
	}

	if (use_copy) {
		phalcon_dtor(&left_copy);
	}
}

/**
 * Appends the content of the right operator to the left operator
 */
void phalcon_concat_self_char(zval **left, unsigned char right TSRMLS_DC) {

	zval left_copy;
	int use_copy = 0;

	if (Z_TYPE_P(*left) == IS_NULL) {
		Z_STRVAL_P(*left) = emalloc(2);
		Z_STRVAL_P(*left)[0] = right;
		Z_STRVAL_P(*left)[1] = 0;
		Z_STRLEN_P(*left) = 1;
		Z_TYPE_P(*left) = IS_STRING;
		return;
	}

	if (Z_TYPE_P(*left) != IS_STRING) {
		phalcon_make_printable_zval(*left, &left_copy, &use_copy);
		if (use_copy) {
			PHALCON_CPY_WRT_CTOR(*left, (&left_copy));
		}
	}

	SEPARATE_ZVAL_IF_NOT_REF(left);

	Z_STRLEN_P(*left)++;
	Z_STRVAL_P(*left) = str_erealloc(Z_STRVAL_P(*left), Z_STRLEN_P(*left) + 1);
	Z_STRVAL_P(*left)[Z_STRLEN_P(*left) - 1] = right;
	Z_STRVAL_P(*left)[Z_STRLEN_P(*left)] = 0;
	Z_TYPE_P(*left) = IS_STRING;

	if (use_copy) {
		phalcon_dtor(&left_copy);
	}
}
