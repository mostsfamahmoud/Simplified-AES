/**********************************************************************
 * my_types.h
 *
 * My Standard Types used in this project
 *
 * Created on: Nov 18, 2023
 *
 * Author: Mostafa Mahmoud
 **********************************************************************/

#ifndef _MY_TYPES_H_
#define _MY_TYPES_H_

 /***********************************************************************************************
  *************************************** Symbol definitions **************************************
  ************************************************************************************************/

#define TRUE         1U
#define FALSE        0U

#define NULL_PTR     ((void*)0)   // Pointer of type Void that points to Address 0

  /***********************************************************************************************
   *************************************** Type definitions **************************************
   ************************************************************************************************/

typedef unsigned char            boolean;          // Range: 0..255 – 0x00..0xFF

typedef unsigned char            uint8;            // Range: 0..255 – 0x00..0xFF
typedef unsigned short           uint16;           // Range: 0..65535 – 0x0000..0xFFFF
typedef unsigned long            uint32;           // Range: 0..4294967295 – 0x00000000..0xFFFFFFFF
typedef unsigned long long       uint64;           // Range: 0..18446744073709551615 – 0x0000000000000000..0xFFFFFFFFFFFFFFFF

typedef signed char              sint8;            // Range: -128..+127 – 0x80..0x7F
typedef signed short             sint16;           // Range: -32768..+32767 – 0x8000..0x7FFF
typedef signed long              sint32;           // Range: -2147483648..+2147483647 – 0x80000000..0x7FFFFFFF
typedef signed long long         sint64;           // Range: -9223372036854775808..9223372036854775807 – 0x8000000000000000..0x7FFFFFFFFFFFFFFF

typedef float                    float32;          // Range: -3.4028235e+38 .. +3.4028235e+38
typedef double                   float64;          // Range: -1.7976931348623157e+308 .. +1.7976931348623157e+308

/* Note: This type shall be used for buffers that contain data returned to the caller */
typedef void* VoidPtr;

/* Note: This type shall be used for buffers that are passed to the callee. */
typedef const void* ConstVoidPtr;

#endif /* _MY_TYPES_H_ */
