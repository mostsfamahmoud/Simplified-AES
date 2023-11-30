/**********************************************************************
 * SAES.h
 *
 * Simplified AES Header file
 *
 * Created on: Nov 18, 2023
 *
 * Author: Mostafa Mahmoud
 **********************************************************************/


#ifndef _SAES_H_
#define _SAES_H_

#include "my_types.h"

/***********************************************************************************************
*************************************** Symbol definitions **************************************
************************************************************************************************/

#define GF_MUL_PRECOMPUTED_TERM    0x03 

/***********************************************************************************************
*********************************** SAES Function Prototypes **********************************
************************************************************************************************/

/******************* SAES Encryption Functions Prototypes **********************/
uint16 SAES_Encryption(uint16 plaintext, uint16 Key);
void SAES_MixColumns();
void SAES_ShiftRow();
void SAES_SubstituteNibbles();

/******************* SAES Decryption Functions Prototypes **********************/
uint16 SAES_Decryption(uint16 plaintext, uint16 Key);
void SAES_InverseMixColumns();
void SAES_InverseShiftRow();
void SAES_InverseSubstituteNibbles();

/******************* SAES Common Functions Prototypes ***************************/
uint16 SAES_AddRoundKey(uint16 data, uint16 roundKey);

// Key Expansion
void SAES_ExpandKey(uint16 originalKey);
uint8 KE_SubNibble(uint8 value);
uint8 RotNibble(uint8 value);

// State Matrix
uint16 SAES_ConvertStateMatrixToData(uint8 State[][2]);
void SAES_UpdateStateMatrix(uint8 State[][2], uint16 data);
void printStateMatrix(uint8 state[][2]);

// GF(2^4) Multiplication 
uint8 GF_MultiplyBy(uint8 data, uint8 mulValue);

#endif /* _SAES_H_ */
