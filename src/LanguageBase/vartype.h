//
// C++ Interface: vartype
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _vartype_h_
#define _vartype_h_

//! types of variables
typedef enum {
  type_void,             /**< no type */
  type_float,            /**< floating point number */
  type_bool,             /**< boolean */               /// New (added: 19/11/2010)
  type_double,           /**< double point number */   /// New (added: 24/05/2010)
  type_long,             /**< long int point number */ /// New (added: 27/05/2010)
  type_ulong,            /**< unsigned long int point number */ 
  type_int,              /**< integer number*/
  type_short,            /**< short integer number*/
  type_ushort,           /**< unsigned short integer number*/
  type_uchar,            /**< unsigned char number */
  type_string,           /**< string */
  type_c_procedure,      /**< C wrapped procedure */
  type_class_member,  /**< wrapped C++ class procedure member */
  type_c_function,       /**< C wrapped function that returns a variable */
  type_ami_function,     /**< AMI Language function */
  type_ami_class,        /**< AMI Language class */
  type_ami_object,       /**< AMI Language object (instance of a class, or namespace) */
  type_matrix,           /**< matrix */
  type_array,            /**< Array */
  type_any,              /**< Any type */
} vartype; //! types of variables
 

#endif 
// _vartype_h_
