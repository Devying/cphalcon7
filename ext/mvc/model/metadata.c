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

#include "mvc/model/metadata.h"
#include "mvc/model/metadatainterface.h"
#include "mvc/model/metadata/strategy/introspection.h"
#include "mvc/model/exception.h"
#include "mvc/modelinterface.h"
#include "diinterface.h"
#include "di/injectable.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/operators.h"

/**
 * Phalcon\Mvc\Model\MetaData
 *
 * <p>Because Phalcon\Mvc\Model requires meta-data like field names, data types, primary keys, etc.
 * this component collect them and store for further querying by Phalcon\Mvc\Model.
 * Phalcon\Mvc\Model\MetaData can also use adapters to store temporarily or permanently the meta-data.</p>
 *
 * <p>A standard Phalcon\Mvc\Model\MetaData can be used to query model attributes:</p>
 *
 * <code>
 *	$metaData = new Phalcon\Mvc\Model\MetaData\Memory();
 *	$attributes = $metaData->getAttributes(new Robots());
 *	print_r($attributes);
 * </code>
 *
 */
zend_class_entry *phalcon_mvc_model_metadata_ce;

PHP_METHOD(Phalcon_Mvc_Model_MetaData, _initialize);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, setStrategy);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getStrategy);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readMetaData);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readMetaDataIndex);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, writeMetaDataIndex);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readColumnMap);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readColumnMapIndex);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getPrimaryKeyAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getNonPrimaryKeyAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getNotNullAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, isNotNull);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataTypes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataType);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataSizes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataSize);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataBytes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataScales);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataScale);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataTypesNumeric);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, isNumeric);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getIdentityField);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getBindTypes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDefaultValues);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getAutomaticCreateAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getAutomaticUpdateAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, setAutomaticCreateAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, setAutomaticUpdateAttributes);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getColumnMap);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getReverseColumnMap);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, hasAttribute);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, isEmpty);
PHP_METHOD(Phalcon_Mvc_Model_MetaData, reset);

static const zend_function_entry phalcon_mvc_model_metadata_method_entry[] = {
	PHP_ME(Phalcon_Mvc_Model_MetaData, _initialize, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Phalcon_Mvc_Model_MetaData, setStrategy, arginfo_phalcon_mvc_model_metadatainterface_setstrategy, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getStrategy, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, readMetaData, arginfo_phalcon_mvc_model_metadatainterface_readmetadata, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, readMetaDataIndex, arginfo_phalcon_mvc_model_metadatainterface_readmetadataindex, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, writeMetaDataIndex, arginfo_phalcon_mvc_model_metadatainterface_writemetadataindex, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, readColumnMap, arginfo_phalcon_mvc_model_metadatainterface_readcolumnmap, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, readColumnMapIndex, arginfo_phalcon_mvc_model_metadatainterface_readcolumnmapindex, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getAttributes, arginfo_phalcon_mvc_model_metadatainterface_getattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getPrimaryKeyAttributes, arginfo_phalcon_mvc_model_metadatainterface_getprimarykeyattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getNonPrimaryKeyAttributes, arginfo_phalcon_mvc_model_metadatainterface_getnonprimarykeyattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getNotNullAttributes, arginfo_phalcon_mvc_model_metadatainterface_getnotnullattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, isNotNull, arginfo_phalcon_mvc_model_metadatainterface_isnotnull, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataTypes, arginfo_phalcon_mvc_model_metadatainterface_getdatatypes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataType, arginfo_phalcon_mvc_model_metadatainterface_getdatatype, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataSizes, arginfo_phalcon_mvc_model_metadatainterface_getdatasizes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataSize, arginfo_phalcon_mvc_model_metadatainterface_getdatasize, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataBytes, arginfo_phalcon_mvc_model_metadatainterface_getdatabytes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataScales, arginfo_phalcon_mvc_model_metadatainterface_getdatascales, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataScale, arginfo_phalcon_mvc_model_metadatainterface_getdatascale, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDataTypesNumeric, arginfo_phalcon_mvc_model_metadatainterface_getdatatypesnumeric, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, isNumeric, arginfo_phalcon_mvc_model_metadatainterface_isnumeric, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getIdentityField, arginfo_phalcon_mvc_model_metadatainterface_getidentityfield, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getBindTypes, arginfo_phalcon_mvc_model_metadatainterface_getbindtypes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getDefaultValues, arginfo_phalcon_mvc_model_metadatainterface_getdefaultvalues, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getAutomaticCreateAttributes, arginfo_phalcon_mvc_model_metadatainterface_getautomaticcreateattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getAutomaticUpdateAttributes, arginfo_phalcon_mvc_model_metadatainterface_getautomaticupdateattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, setAutomaticCreateAttributes, arginfo_phalcon_mvc_model_metadatainterface_setautomaticcreateattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, setAutomaticUpdateAttributes, arginfo_phalcon_mvc_model_metadatainterface_setautomaticupdateattributes, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getColumnMap, arginfo_phalcon_mvc_model_metadatainterface_getcolumnmap, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, getReverseColumnMap, arginfo_phalcon_mvc_model_metadatainterface_getreversecolumnmap, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, hasAttribute, arginfo_phalcon_mvc_model_metadatainterface_hasattribute, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, isEmpty, arginfo_phalcon_mvc_model_metadatainterface_isempty, ZEND_ACC_PUBLIC)
	PHP_ME(Phalcon_Mvc_Model_MetaData, reset, arginfo_phalcon_mvc_model_metadatainterface_reset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/**
 * Phalcon\Mvc\Model\MetaData initializer
 */
PHALCON_INIT_CLASS(Phalcon_Mvc_Model_MetaData){

	PHALCON_REGISTER_CLASS_EX(Phalcon\\Mvc\\Model, MetaData, mvc_model_metadata, phalcon_di_injectable_ce, phalcon_mvc_model_metadata_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalcon_mvc_model_metadata_ce, SL("_strategy"), ZEND_ACC_PROTECTED);
	zend_declare_property_null(phalcon_mvc_model_metadata_ce, SL("_metaData"), ZEND_ACC_PROTECTED);
	zend_declare_property_null(phalcon_mvc_model_metadata_ce, SL("_columnMap"), ZEND_ACC_PROTECTED);

	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_ATTRIBUTES"),               PHALCON_MVC_MODEL_METADATA_MODELS_ATTRIBUTES              );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_PRIMARY_KEY"),              PHALCON_MVC_MODEL_METADATA_MODELS_PRIMARY_KEY             );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_NON_PRIMARY_KEY"),          PHALCON_MVC_MODEL_METADATA_MODELS_NON_PRIMARY_KEY         );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_NOT_NULL"),                 PHALCON_MVC_MODEL_METADATA_MODELS_NOT_NULL                );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_TYPES"),               PHALCON_MVC_MODEL_METADATA_MODELS_DATA_TYPES              );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_TYPES_NUMERIC"),       PHALCON_MVC_MODEL_METADATA_MODELS_DATA_TYPES_NUMERIC      );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATE_AT"),                  PHALCON_MVC_MODEL_METADATA_MODELS_DATE_AT                 );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATE_IN"),                  PHALCON_MVC_MODEL_METADATA_MODELS_DATE_IN                 );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_IDENTITY_COLUMN"),          PHALCON_MVC_MODEL_METADATA_MODELS_IDENTITY_COLUMN         );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_TYPES_BIND"),          PHALCON_MVC_MODEL_METADATA_MODELS_DATA_TYPES_BIND         );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_AUTOMATIC_DEFAULT_INSERT"), PHALCON_MVC_MODEL_METADATA_MODELS_AUTOMATIC_DEFAULT_INSERT);
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_AUTOMATIC_DEFAULT_UPDATE"), PHALCON_MVC_MODEL_METADATA_MODELS_AUTOMATIC_DEFAULT_UPDATE);
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_DEFAULT_VALUE"), PHALCON_MVC_MODEL_METADATA_MODELS_DATA_DEFAULT_VALUE);
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_SZIE"), PHALCON_MVC_MODEL_METADATA_MODELS_DATA_SZIE);
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_SCALE"), PHALCON_MVC_MODEL_METADATA_MODELS_DATA_SCALE);
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_DATA_BYTE"), PHALCON_MVC_MODEL_METADATA_MODELS_DATA_BYTE);

	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_COLUMN_MAP"),         PHALCON_MVC_MODEL_METADATA_MODELS_COLUMN_MAP        );
	zend_declare_class_constant_long(phalcon_mvc_model_metadata_ce, SL("MODELS_REVERSE_COLUMN_MAP"), PHALCON_MVC_MODEL_METADATA_MODELS_REVERSE_COLUMN_MAP);

	zend_class_implements(phalcon_mvc_model_metadata_ce, 1, phalcon_mvc_model_metadatainterface_ce);

	return SUCCESS;
}

/**
 * Initialize the metadata for certain table
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $key
 * @param string $table
 * @param string $schema
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, _initialize){

	zval *model, *key, *table, *schema, *read_meta = NULL, *dependency_injector, class_name;
	zval meta_data, prefix_key, data, model_metadata, strategy, exception_message, column_map, model_column_map;

	phalcon_fetch_params(0, 4, 1, &model, &key, &table, &schema, &read_meta);

	if (PHALCON_IS_EMPTY(key)) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The key is not valid");
		return;
	}

	if (!read_meta) {
		read_meta = &PHALCON_GLOBAL(z_false);
	}

	dependency_injector = phalcon_read_property(getThis(), SL("_dependencyInjector"), PH_NOISY);

	phalcon_get_class(&class_name, model, 0);

	if (zend_is_true(read_meta)) {
		phalcon_return_property(&meta_data, getThis(), SL("_metaData"));
		if (Z_TYPE(meta_data) != IS_ARRAY) { 
			array_init(&meta_data);
		}

		if (!phalcon_array_isset(&meta_data, key)) {
			PHALCON_CONCAT_SV(&prefix_key, "meta-", key);

			/** 
			 * The meta-data is read from the adapter always
			 */
			PHALCON_CALL_METHODW(&data, getThis(), "read", &prefix_key);

			if (Z_TYPE(data) != IS_NULL) {
				phalcon_array_update_zval(&meta_data, key, &data, PH_COPY);
				phalcon_update_property_this(getThis(), SL("_metaData"), &meta_data);
			} else {
				/** 
				 * Check if there is a method 'metaData' in the model to retrieve meta-data from it
				 */
				if (phalcon_method_exists_ex(model, SL("metadata")) == SUCCESS) {
					PHALCON_CALL_METHODW(&model_metadata, model, "metadata");
					if (Z_TYPE(model_metadata) != IS_ARRAY) {
						PHALCON_CONCAT_SV(&exception_message, "Invalid meta-data for model ", &class_name);
						PHALCON_THROW_EXCEPTION_ZVALW(phalcon_mvc_model_exception_ce, &exception_message);
						return;
					}
				} else {
					/** 
					 * Get the meta-data extraction strategy
					 */
					PHALCON_CALL_METHODW(&strategy, getThis(), "getstrategy");

					/** 
					 * Get the meta-data
					 */
					PHALCON_CALL_METHODW(&model_metadata, &strategy, "getmetadata", model, dependency_injector);
				}

				/** 
				 * Store the meta-data locally
				 */
				phalcon_update_property_array(getThis(), SL("_metaData"), key, &model_metadata);

				/** 
				 * Store the meta-data in the adapter
				 */
				PHALCON_CALL_METHODW(NULL, getThis(), "write", &prefix_key, &model_metadata);
			}
		}
	}

	/** 
	 * Check for a column map, store in _columnMap in order and reversed order
	 */
	if (!PHALCON_GLOBAL(orm).column_renaming) {
		RETURN_NULL();
	}

	phalcon_return_property(&column_map, getThis(), SL("_columnMap"));
	if (phalcon_array_isset(&column_map, key)) {
		RETURN_NULL();
	}

	if (Z_TYPE(column_map) != IS_ARRAY) { 
		array_init(&column_map);
	}

	/** 
	 * Create the map key name
	 */
	PHALCON_CONCAT_SV(&prefix_key, "map-", key);

	/** 
	 * Check if the meta-data is already in the adapter
	 */
	PHALCON_CALL_METHODW(&data, getThis(), "read", &prefix_key);
	if (Z_TYPE(data) != IS_NULL) {
		phalcon_array_update_zval(&column_map, key, &data, PH_COPY);
		phalcon_update_property_this(getThis(), SL("_columnMap"), &column_map);
		RETURN_NULL();
	}

	/** 
	 * Get the meta-data extraction strategy
	 */
	if (Z_TYPE(strategy) != IS_OBJECT) {
		PHALCON_CALL_METHODW(&strategy, getThis(), "getstrategy");
	}

	/** 
	 * Get the meta-data
	 */
	PHALCON_CALL_METHODW(&model_column_map, &strategy, "getcolumnmaps", model, dependency_injector);

	/** 
	 * Update the column map locally
	 */
	phalcon_update_property_array(getThis(), SL("_columnMap"), key, &model_column_map);

	/** 
	 * Write the data to the adapter
	 */
	PHALCON_CALL_METHODW(NULL, getThis(), "write", &prefix_key, &model_column_map);
}

/**
 * Set the meta-data extraction strategy
 *
 * @param Phalcon\Mvc\Model\MetaData\Strategy\Introspection $strategy
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, setStrategy){

	zval *strategy;

	phalcon_fetch_params(0, 1, 0, &strategy);

	if (Z_TYPE_P(strategy) != IS_OBJECT) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data extraction strategy is not valid");
		return;
	}
	phalcon_update_property_this(getThis(), SL("_strategy"), strategy);

}

/**
 * Return the strategy to obtain the meta-data
 *
 * @return Phalcon\Mvc\Model\MetaData\Strategy\Introspection
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getStrategy){

	zval *strategy, s;

	strategy = phalcon_read_property(getThis(), SL("_strategy"), PH_NOISY);
	if (Z_TYPE_P(strategy) == IS_NULL) {
		object_init_ex(&s, phalcon_mvc_model_metadata_strategy_introspection_ce);
		phalcon_update_property_this(getThis(), SL("_strategy"), &s);
		RETURN_CTORW(&s);
	}

	RETURN_CTORW(strategy);
}

/**
 * Reads the complete meta-data for certain model
 *
 *<code>
 *	print_r($metaData->readMetaData(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readMetaData){

	zval *model, table, schema, class_name, key, *meta_data, data;

	phalcon_fetch_params(0, 1, 0, &model);
	PHALCON_VERIFY_INTERFACE_EX(model, phalcon_mvc_modelinterface_ce, phalcon_mvc_model_exception_ce, 0);

	PHALCON_CALL_METHODW(&table, model, "getsource");
	PHALCON_CALL_METHODW(&schema, model, "getschema");

	phalcon_get_class(&class_name, model, 1);

	/** 
	 * Unique key for meta-data is created using class-name-schema-table
	 */
	PHALCON_CONCAT_VSVV(&key, &class_name, "-", &schema, &table);

	meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);
	if (!phalcon_array_isset(meta_data, &key)) {
		PHALCON_CALL_METHODW(NULL, getThis(), "_initialize", model, &key, &table, &schema, &PHALCON_GLOBAL(z_true));
		meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);
	}

	phalcon_array_fetch(&data, meta_data, &key, PH_NOISY);

	RETURN_CTORW(&data);
}

/**
 * Reads meta-data for certain model using a MODEL_* constant
 *
 *<code>
 *	print_r($metaData->writeColumnMapIndex(new Robots(), MetaData::MODELS_REVERSE_COLUMN_MAP, array('leName' => 'name')));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param int $index
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readMetaDataIndex){

	zval *model, *index, table, schema, class_name;
	zval key, *meta_data = NULL, meta_data_index, attributes;

	phalcon_fetch_params(0, 2, 0, &model, &index);
	PHALCON_VERIFY_INTERFACE_EX(model, phalcon_mvc_modelinterface_ce, phalcon_mvc_model_exception_ce, 0);
	PHALCON_ENSURE_IS_LONG(index);

	PHALCON_CALL_METHODW(&table, model, "getsource");
	PHALCON_CALL_METHODW(&schema, model, "getschema");

	phalcon_get_class(&class_name, model, 1);

	/** 
	 * Unique key for meta-data is created using class-name-schema-table
	 */
	PHALCON_CONCAT_VSVV(&key, &class_name, "-", &schema, &table);

	meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);

	if (!phalcon_array_isset(meta_data, &key)) {
		PHALCON_CALL_METHODW(NULL, getThis(), "_initialize", model, &key, &table, &schema, &PHALCON_GLOBAL(z_true));
		meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);
	}

	phalcon_array_fetch(&meta_data_index, meta_data, &key, PH_NOISY);
	phalcon_array_fetch(&attributes, &meta_data_index, index, PH_NOISY);

	RETURN_CTORW(&attributes);
}

/**
 * Writes meta-data for certain model using a MODEL_* constant
 *
 *<code>
 *	print_r($metaData->writeColumnMapIndex(new Robots(), MetaData::MODELS_REVERSE_COLUMN_MAP, array('leName' => 'name')));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param int $index
 * @param mixed $data
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, writeMetaDataIndex){

	zval *model, *index, *data, *replace, table, schema, class_name, key, *meta_data, arr, value, *v;
	zend_string *str_key;
	ulong idx;

	phalcon_fetch_params(0, 4, 0, &model, &index, &data, &replace);
	PHALCON_VERIFY_INTERFACE_EX(model, phalcon_mvc_modelinterface_ce, phalcon_mvc_model_exception_ce, 0);

	if (Z_TYPE_P(index) != IS_LONG) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "Index must be a valid integer constant");
		return;
	}

	if (Z_TYPE_P(data) != IS_ARRAY && Z_TYPE_P(data) != IS_STRING && !PHALCON_IS_BOOL(data)) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "Invalid data for index");
		return;
	}

	PHALCON_CALL_METHODW(&table, model, "getsource");
	PHALCON_CALL_METHODW(&schema, model, "getschema");

	phalcon_get_class(&class_name, model, 1);

	/** 
	 * Unique key for meta-data is created using class-name-schema-table
	 */
	PHALCON_CONCAT_VSVV(&key, &class_name, "-", &schema, &table);

	meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);
	if (!phalcon_array_isset(meta_data, &key)) {
		PHALCON_CALL_METHODW(NULL, getThis(), "_initialize", model, &key, &table, &schema, &PHALCON_GLOBAL(z_true));
		meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);
	} else if (!zend_is_true(replace)) {
		phalcon_array_fetch(&arr, meta_data, &key, PH_NOISY);
		phalcon_array_fetch(&value, &arr, index, PH_NOISY);

		PHALCON_SEPARATE_PARAM(data);

		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL(value), idx, str_key, v) {
			zval tmp;
			if (str_key) {
				ZVAL_STR(&tmp, str_key);
			} else {
				ZVAL_LONG(&tmp, idx);
			}

			if (!phalcon_array_isset(data, &tmp)) {
				phalcon_array_update_zval(data, &tmp, v, PH_COPY);
			}
		} ZEND_HASH_FOREACH_END();
	}

	phalcon_array_update_multi_2(meta_data, &key, index, data, PH_COPY);
	phalcon_update_property_this(getThis(), SL("_metaData"), meta_data);
}

/**
 * Reads the ordered/reversed column map for certain model
 *
 *<code>
 *	print_r($metaData->readColumnMap(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readColumnMap){

	zval *model, table, schema, class_name, key, *column_map, data;

	phalcon_fetch_params(0, 1, 0, &model);
	PHALCON_VERIFY_INTERFACE_EX(model, phalcon_mvc_modelinterface_ce, phalcon_mvc_model_exception_ce, 0);

	if (!PHALCON_GLOBAL(orm).column_renaming) {
		return;
	}

	PHALCON_CALL_METHODW(&table, model, "getsource");
	PHALCON_CALL_METHODW(&schema, model, "getschema");

	phalcon_get_class(&class_name, model, 1 TSRMLS_CC);

	/** 
	 * Unique key for map is created using class-name-schema-table
	 */
	PHALCON_CONCAT_VSVV(&key, &class_name, "-", &schema, &table);

	column_map = phalcon_read_property(getThis(), SL("_columnMap"), PH_NOISY);
	if (!phalcon_array_isset(column_map, &key)) {
		PHALCON_CALL_METHODW(NULL, getThis(), "_initialize", model, &key, &table, &schema);

		column_map = phalcon_read_property(getThis(), SL("_columnMap"), PH_NOISY);
	}

	phalcon_array_fetch(&data, column_map, &key, PH_NOISY);

	RETURN_CTORW(&data);
}

/**
 * Reads column-map information for certain model using a MODEL_* constant
 *
 *<code>
 *	print_r($metaData->readColumnMapIndex(new Robots(), MetaData::MODELS_REVERSE_COLUMN_MAP));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param int $index
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, readColumnMapIndex){

	zval *model, *index, table, schema, class_name, key, *column_map, column_map_model, attributes;

	phalcon_fetch_params(0, 2, 0, &model, &index);
	PHALCON_VERIFY_INTERFACE_EX(model, phalcon_mvc_modelinterface_ce, phalcon_mvc_model_exception_ce, 0);
	PHALCON_ENSURE_IS_LONG(index);

	if (!PHALCON_GLOBAL(orm).column_renaming) {
		return;
	}

	PHALCON_CALL_METHODW(&table, model, "getsource");
	PHALCON_CALL_METHODW(&schema, model, "getschema");

	phalcon_get_class(&class_name, model, 1 TSRMLS_CC);

	/** 
	 * Unique key for map is created using class-name-schema-table
	 */
	PHALCON_CONCAT_VSVV(&key, &class_name, "-", &schema, &table);

	column_map = phalcon_read_property(getThis(), SL("_columnMap"), PH_NOISY);
	if (!phalcon_array_isset(column_map, &key)) {
		PHALCON_CALL_SELFW(NULL, "_initialize", model, &key, &table, &schema);

		column_map = phalcon_read_property(getThis(), SL("_columnMap"), PH_NOISY);
	}

	phalcon_array_fetch(&column_map_model, column_map, &key, PH_NOISY);
	phalcon_array_fetch(&attributes, &column_map_model, index, PH_NOISY);

	RETURN_CTORW(&attributes);
}

/**
 * Returns table attributes names (fields)
 *
 *<code>
 *	print_r($metaData->getAttributes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getAttributes){

	zval *model, what;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&what, PHALCON_MVC_MODEL_METADATA_MODELS_ATTRIBUTES);

	PHALCON_RETURN_CALL_METHODW(getThis(), "readmetadataindex", model, &what);

	if (Z_TYPE_P(return_value) != IS_ARRAY) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupted");
		return;
	}
}

/**
 * Returns an array of fields which are part of the primary key
 *
 *<code>
 *	print_r($metaData->getPrimaryKeyAttributes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getPrimaryKeyAttributes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 1);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns an arrau of fields which are not part of the primary key
 *
 *<code>
 *	print_r($metaData->getNonPrimaryKeyAttributes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return 	array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getNonPrimaryKeyAttributes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 2);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns an array of not null attributes
 *
 *<code>
 *	print_r($metaData->getNotNullAttributes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getNotNullAttributes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 3);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Checks if the attribute is not null
 *
 *<code>
 *	var_dump($metaData->isNotNull(new Robots(), 'type');
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, isNotNull){

	zval *model, *attribute, data;

	phalcon_fetch_params(0, 2, 0, &model, &attribute);

	PHALCON_CALL_METHODW(&data, getThis(), "getnotnullattributes", model);

	if (phalcon_fast_in_array(attribute, &data)) {
		RETURN_TRUE;
	}

	RETURN_FALSE;
}

/**
 * Returns attributes and their data types
 *
 *<code>
 *	print_r($metaData->getDataTypes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataTypes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 4);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);

	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns attribute data type
 *
 *<code>
 *	print_r($metaData->getDataType(new Robots(), 'type'));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataType){

	zval *model, *attribute, data;

	phalcon_fetch_params(0, 2, 0, &model, &attribute);

	PHALCON_CALL_METHODW(&data, getThis(), "getdatatypes", model);

	if (phalcon_array_isset(&data, attribute)) {
		phalcon_array_fetch(return_value, &data, attribute, PH_NOISY);
	}
}

/**
 * Returns attributes and their data sizes
 *
 *<code>
 *	print_r($metaData->getDataSizes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataSizes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 13);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns attribute data size
 *
 *<code>
 *	print_r($metaData->getDataSize(new Robots(), 'type'));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataSize){

	zval *model, *attribute, data;

	phalcon_fetch_params(0, 2, 0, &model, &attribute);

	PHALCON_CALL_METHODW(&data, getThis(), "getdatasizes", model);

	if (phalcon_array_isset(&data, attribute)) {
		phalcon_array_fetch(return_value, &data, attribute, PH_NOISY);
	}
}

/**
 * Returns attribute data bytes
 *
 *<code>
 *	print_r($metaData->getDataBytes(new Robots(), 'type'));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataBytes){

	zval *model, *attribute, index, data;

	phalcon_fetch_params(0, 2, 0, &model, &attribute);

	ZVAL_LONG(&index, 15);

	PHALCON_CALL_METHODW(&data, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE(data) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}

	if (phalcon_array_isset(&data, attribute)) {
		phalcon_array_fetch(return_value, &data, attribute, PH_NOISY);
	}
}

/**
 * Returns attributes and their data scales
 *
 *<code>
 *	print_r($metaData->getDataScales(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataScales){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 14);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns attribute data scale
 *
 *<code>
 *	print_r($metaData->getDataScale(new Robots(), 'type'));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataScale){

	zval *model, *attribute, data;

	phalcon_fetch_params(0, 2, 0, &model, &attribute);

	PHALCON_CALL_METHODW(&data, getThis(), "getdatascales", model);

	if (phalcon_array_isset(&data, attribute)) {
		phalcon_array_fetch(return_value, &data, attribute, PH_NOISY);
	}
}

/**
 * Returns attributes which types are numerical
 *
 *<code>
 *	print_r($metaData->getDataTypesNumeric(new Robots()));
 *</code>
 *
 * @param  Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDataTypesNumeric){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 5);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Checks if the attribute is numerical
 *
 *<code>
 *	var_dump($metaData->isNumeric(new Robots(), 'id'));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, isNumeric){

	zval *model, *attribute, data;

	phalcon_fetch_params(0, 1, 0, &model, &attribute);

	PHALCON_CALL_METHODW(&data, getThis(), "getdatatypesnumeric", model);

	if (phalcon_array_isset(&data, attribute)) {
		RETURN_TRUE;
	}

	RETURN_FALSE;
}

/**
 * Returns the name of identity field (if one is present)
 *
 *<code>
 *	print_r($metaData->getIdentityField(new Robots()));
 *</code>
 *
 * @param  Phalcon\Mvc\ModelInterface $model
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getIdentityField){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 8);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
}

/**
 * Returns attributes and their bind data types
 *
 *<code>
 *	print_r($metaData->getBindTypes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getBindTypes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 9);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns attributes and their default values
 *
 *<code>
 *	print_r($metaData->getDefaultValues(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getDefaultValues){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 12);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns attributes that must be ignored from the INSERT SQL generation
 *
 *<code>
 *	print_r($metaData->getAutomaticCreateAttributes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getAutomaticCreateAttributes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 10);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Returns attributes that must be ignored from the UPDATE SQL generation
 *
 *<code>
 *	print_r($metaData->getAutomaticUpdateAttributes(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getAutomaticUpdateAttributes){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 11);

	PHALCON_CALL_METHODW(return_value, getThis(), "readmetadataindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_ARRAY) { 
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
		return;
	}
}

/**
 * Set the attributes that must be ignored from the INSERT SQL generation
 *
 *<code>
 *	$metaData->setAutomaticCreateAttributes(new Robots(), array('created_at' => true));
 *</code>
 *
 * @param  Phalcon\Mvc\ModelInterface $model
 * @param  array $attributes
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, setAutomaticCreateAttributes){

	zval *model, *attributes, *replace, index;

	phalcon_fetch_params(0, 3, 0, &model, &attributes, &replace);

	ZVAL_LONG(&index, 10);
	PHALCON_CALL_METHODW(NULL, getThis(), "writemetadataindex", model, &index, attributes, replace);
}

/**
 * Set the attributes that must be ignored from the UPDATE SQL generation
 *
 *<code>
 *	$metaData->setAutomaticUpdateAttributes(new Robots(), array('modified_at' => true));
 *</code>
 *
 * @param  Phalcon\Mvc\ModelInterface $model
 * @param  array $attributes
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, setAutomaticUpdateAttributes){

	zval *model, *attributes, *replace, index;

	phalcon_fetch_params(0, 3, 0, &model, &attributes, &replace);

	ZVAL_LONG(&index, 11);
	PHALCON_CALL_METHODW(NULL, getThis(), "writemetadataindex", model, &index, attributes, replace);
}

/**
 * Returns the column map if any
 *
 *<code>
 *	print_r($metaData->getColumnMap(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getColumnMap){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 0);

	PHALCON_CALL_METHODW(return_value, getThis(), "readcolumnmapindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_NULL) {
		if (Z_TYPE_P(return_value) != IS_ARRAY) { 
			PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
			return;
		}
	}
}

/**
 * Returns the reverse column map if any
 *
 *<code>
 *	print_r($metaData->getReverseColumnMap(new Robots()));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, getReverseColumnMap){

	zval *model, index;

	phalcon_fetch_params(0, 1, 0, &model);

	ZVAL_LONG(&index, 1);

	PHALCON_CALL_METHODW(return_value, getThis(), "readcolumnmapindex", model, &index);
	if (Z_TYPE_P(return_value) != IS_NULL) {
		if (Z_TYPE_P(return_value) != IS_ARRAY) { 
			PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "The meta-data is invalid or is corrupt");
			return;
		}
	}
}

/**
 * Check if a model has certain attribute
 *
 *<code>
 *	var_dump($metaData->hasAttribute(new Robots(), 'name'));
 *</code>
 *
 * @param Phalcon\Mvc\ModelInterface $model
 * @param string $attribute
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, hasAttribute){

	zval *model, *attribute, column_map, meta_data, data_types;

	phalcon_fetch_params(0, 2, 0, &model, &attribute);

	if (Z_TYPE_P(attribute) != IS_STRING) {
		PHALCON_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "Attribute must be a string");
		return;
	}

	PHALCON_CALL_METHODW(&column_map, getThis(), "getreversecolumnmap", model);
	if (Z_TYPE(column_map) == IS_ARRAY) { 
		if (phalcon_array_isset(&column_map, attribute)) {
			RETURN_TRUE;
		}
	} else {
		PHALCON_CALL_METHODW(&meta_data, getThis(), "readmetadata", model);

		phalcon_array_fetch_long(&data_types, &meta_data, 4, PH_NOISY);
		if (phalcon_array_isset(&data_types, attribute)) {
			RETURN_TRUE;
		}
	}

	RETURN_FALSE;
}

/**
 * Checks if the internal meta-data container is empty
 *
 *<code>
 *	var_dump($metaData->isEmpty());
 *</code>
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, isEmpty){

	zval *meta_data;

	meta_data = phalcon_read_property(getThis(), SL("_metaData"), PH_NOISY);
	if (phalcon_fast_count_ev(meta_data)) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}

/**
 * Resets internal meta-data in order to regenerate it
 *
 *<code>
 *	$metaData->reset();
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData, reset){

	phalcon_update_property_empty_array(getThis(), SL("_metaData"));
	phalcon_update_property_empty_array(getThis(), SL("_columnMap"));
}
