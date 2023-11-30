/**********************************************************************
 * SAES.c
 *
 * My Implementation of Simplified AES Mentioned in Lecture Slides
 *
 * Created on: Nov 18, 2023
 *
 * Author: Mostafa Mahmoud
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "SAES.h"

 /******************************* SAES Global Variables ***************************************/

uint8 encryptState[2][2] = { 0 }; // State Matrix for encryption

uint8 decryptState[2][2] = { 0 }; // State Matrix for decryption

uint16 roundkey[3] = { 0 };       // Key Matrix (3 Keys K0,K1,K2 each is 16-bit in size)

uint8 Sbox[16] =
{
	0x9,0x4,0xA,0xB,
	0xD,0x1,0x8,0x5,
	0x6,0x2,0x0,0x3,
	0xC,0xE,0xF,0x7
};


uint8 InvSbox[16] =
{
	0xA,0x5,0x9,0xB,
	0x1,0x7,0x8,0xF,
	0x6,0x0,0x2,0x3,
	0xC,0x4,0xD,0xE
};


uint8 RCON[3] =
{
	0,       // Reserved
	0x80,    // Round1 Constant
	0x30     // Round2 Constant
};

/***********************************************************************************************
*********************************** SAES Function Definitions **********************************
************************************************************************************************/

/********************** SAES Encryption Function Definitions ************************/

uint16 SAES_Encryption(uint16 plaintext, uint16 Key)
{
	// Key Generation
	SAES_ExpandKey(Key);

	/* // Test Key Expansion
	for (int i = 0; i < 3; i++)
	{
		printf("RoundKey[%d] = %X\n", i, roundkey[i]);
	}
	*/

	// Add Round 0 Key
	uint16 addRoundOutput = SAES_AddRoundKey(plaintext, roundkey[0]);
	//printf("\nOutput of Add Round Key: %X\n",addRoundOutput);

	/******************** Round 1 *******************/

	SAES_UpdateStateMatrix(encryptState, addRoundOutput);
	// Test Construct encryptState Matrix
	//printStateMatrix(encryptState);

	SAES_SubstituteNibbles();
	// Test Sub Nibble
	//printf("\nAfter Nibble Substitution: \n");
	//printStateMatrix(encryptState);

	SAES_ShiftRow();
	// Test Shift Rows
	//printf("\nAfter Shifting Rows: \n");
	//printStateMatrix(encryptState);

	SAES_MixColumns();
	// Test Mix Columns
	//printf("\nAfter Mix Columns: \n");
	//printStateMatrix(encryptState);

	uint16 mixColumnOut = SAES_ConvertStateMatrixToData(encryptState);

	// Add Round 1 Key
	addRoundOutput = SAES_AddRoundKey(mixColumnOut, roundkey[1]);
	//printf("\nOutput of Add Round Key: %X\n", addRoundOutput);

	/******************** Round 2 *******************/

	SAES_UpdateStateMatrix(encryptState, addRoundOutput);
	// Test Construct encryptState Matrix
	//printStateMatrix(encryptState);

	SAES_SubstituteNibbles();
	// Test Sub Nibble
	//printf("\nAfter Nibble Substitution: \n");
	//printStateMatrix(encryptState);

	SAES_ShiftRow();
	// Test Shift Rows
	//printf("\nAfter Shifting Rows: \n");
	//printStateMatrix(encryptState);

	uint16 shiftRowOut = SAES_ConvertStateMatrixToData(encryptState);

	// Add Round 2 Key
	uint16 ciphertext = SAES_AddRoundKey(shiftRowOut, roundkey[2]);

	return ciphertext;
}

void SAES_MixColumns()
{
	uint8 oldState[2][2] = { 0 };

	// Creating an older version of the encryptState to store the previous values of encryptState Matrix before the update  
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			oldState[i][j] = encryptState[i][j];
		}
	}

	// Mix Columns Step based on GF(2^4)
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			encryptState[i][j] = oldState[i][j] ^ GF_MultiplyBy(oldState[(i + 1) % 2][j], 4);
		}
	}
}

void SAES_ShiftRow()
{
	// Swapping only the second row in the encryptState Matrix (Using XOR Operation) 
	encryptState[1][0] = encryptState[1][0] ^ encryptState[1][1];
	encryptState[1][1] = encryptState[1][0] ^ encryptState[1][1];
	encryptState[1][0] = encryptState[1][0] ^ encryptState[1][1];
}

void SAES_SubstituteNibbles()
{
	for (uint8 i = 0; i < 2; i++)
	{
		for (uint8 j = 0; j < 2; j++)
		{
			encryptState[i][j] = Sbox[encryptState[i][j]];  // Substitute Each Nibble with the corresponding value in SBOX
		}
	}
}

/******************* SAES Decryption Function Definitions *************************/

uint16 SAES_Decryption(uint16 ciphertext, uint16 Key)
{
	// Key Generation
	SAES_ExpandKey(Key);

	/* // Test Key Expansion
	for (int i = 0; i < 3; i++)
	{
		printf("RoundKey[%d] = %X\n", i, roundkey[i]);
	}
	*/

	// Add Round 0 Key
	uint16 addRoundOutput = SAES_AddRoundKey(ciphertext, roundkey[2]);
	//printf("\nOutput of Add Round Key: %X\n", addRoundOutput);

	/******************** Round 1 *******************/

	// Test Update decryptState Matrix
	SAES_UpdateStateMatrix(decryptState, addRoundOutput);
	//printStateMatrix(decryptState);

	SAES_InverseShiftRow();
	// Test Inverse Shift Rows
	//printf("\nAfter Inverse Shift Row: \n");
	//printStateMatrix(decryptState);

	SAES_InverseSubstituteNibbles();
	// Test Inverse Sub Nibble
	//printf("\nAfter Inverse Nibble Substitution: \n");
	//printStateMatrix(decryptState);

	uint16 invSubNibbleOut = SAES_ConvertStateMatrixToData(decryptState);

	// Add Round 1 Key
	addRoundOutput = SAES_AddRoundKey(invSubNibbleOut, roundkey[1]);
	//printf("\nOutput of Add Round Key: %X\n", addRoundOutput);

	SAES_UpdateStateMatrix(decryptState, addRoundOutput);
	// Test Update decryptState Matrix
	//printStateMatrix(decryptState);

	SAES_InverseMixColumns();
	// Test Inverse Mix Columns
	//printf("\nAfter Inverse Mix Columns: \n");
	//printStateMatrix(decryptState);

	/******************** Round 2 *******************/

	SAES_InverseShiftRow();
	// Test Inverse Shift Rows
	//printf("\nAfter Inverse Shift Row: \n");
	//printStateMatrix(decryptState);

	SAES_InverseSubstituteNibbles();
	// Test Inverse Sub Nibble
	//printf("\nAfter Inverse Nibble Substitution: \n");
	//printStateMatrix(decryptState);

	invSubNibbleOut = SAES_ConvertStateMatrixToData(decryptState);

	// Add Round 2 Key
	uint16 plaintext = SAES_AddRoundKey(invSubNibbleOut, roundkey[0]);

	return plaintext;
}

void SAES_InverseMixColumns()
{
	uint8 oldState[2][2] = { 0 };

	// Creating an older version of the decryptState to store the previous values of encryptState Matrix before the update  
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			oldState[i][j] = decryptState[i][j];
		}
	}

	// Inverse Mix Columns Step based on GF(2^4)
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			decryptState[i][j] = GF_MultiplyBy(oldState[i][j], 9) ^ GF_MultiplyBy(oldState[(i + 1) % 2][j], 2);
		}
	}
}

void SAES_InverseShiftRow()
{
	// Swapping only the second row in the decryptState Matrix (Using XOR Operation) 
	decryptState[1][0] = decryptState[1][0] ^ decryptState[1][1];
	decryptState[1][1] = decryptState[1][0] ^ decryptState[1][1];
	decryptState[1][0] = decryptState[1][0] ^ decryptState[1][1];
}

void SAES_InverseSubstituteNibbles()
{
	for (uint8 i = 0; i < 2; i++)
	{
		for (uint8 j = 0; j < 2; j++)
		{
			decryptState[i][j] = InvSbox[decryptState[i][j]];  // Substitute Each Nibble with the corresponding value in Inverse SBOX
		}
	}
}

/*********************** SAES Common Function Definitions ****************************/

uint16 SAES_AddRoundKey(uint16 data, uint16 roundKey)
{
	return data ^ roundKey;
}

/** Key Expansion Related Functions ********************/

// Used inside the key Expansion Method
uint8 RotNibble(uint8 value)
{
	return (value << 4) | ((value >> 4) & 0xF);
}

uint8 KE_SubNibble(uint8 value)
{
	uint8 N0 = value & 0xF;
	uint8 N1 = (value >> 4) & 0xF;

	N0 = Sbox[N0];
	N1 = Sbox[N1];

	return N0 | (N1 << 4);
}

void SAES_ExpandKey(uint16 originalKey)
{
	uint8 w[6] = { 0 };

	roundkey[0] = originalKey;
	w[0] = (roundkey[0] >> 8) & 0xFF;
	w[1] = roundkey[0] & 0xFF;

	// Steps to calculate First round key
	w[2] = w[0] ^ RCON[1] ^ KE_SubNibble(RotNibble(w[1]));
	w[3] = w[1] ^ w[2];
	roundkey[1] = (w[2] << 8) | w[3];

	// Steps to calculate Second round key
	w[4] = w[2] ^ RCON[2] ^ KE_SubNibble(RotNibble(w[3]));
	w[5] = w[3] ^ w[4];
	roundkey[2] = (w[4] << 8) | w[5];
}

/** State Matrix Related Functions ********************/

void SAES_UpdateStateMatrix(uint8 State[][2], uint16 data)
{
	// Mask for isolating each nibble
	uint16 mask = 0xF;

	State[0][0] = (data >> 12) & mask; // Extract the first Nibble
	State[1][0] = (data >> 8) & mask;  // Extract the second Nibble
	State[0][1] = (data >> 4) & mask;  // Extract the third Nibble
	State[1][1] = data & mask;         // Extract the fourth Nibble
}

uint16 SAES_ConvertStateMatrixToData(uint8 State[][2])
{
	return (State[0][0] << 12) |
		(State[1][0] << 8) |
		(State[0][1] << 4) |
		State[1][1];
}

void printStateMatrix(uint8 state[][2])
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			printf("S[%d][%d] = %X\n", j, i, state[j][i]);
		}
	}
}

/** GF(2^4) Multiplication Function ********************/

uint8 GF_MultiplyBy(uint8 data, uint8 mulValue)
{
	uint8 result = data;

	switch (mulValue)
	{
	case 2: /* Used in SAES Decryption */

		/* Reading Bit 3 in data to determine what will be done in the multiplication operation */
		if ((result >> 3) == 1)
		{
			result = ((result << 1) & 0x0F) ^ GF_MUL_PRECOMPUTED_TERM;
		}
		else
			result = (result << 1) & 0x0F;

		break;

	case 4: /* Used in SAES Encryption */

		for (uint8 i = 0; i < 2; i++)
		{
			/* Reading Bit 3 in data to determine what will be done in the multiplication operation */
			if ((result >> 3) == 1)
			{
				result = ((result << 1) & 0x0F) ^ GF_MUL_PRECOMPUTED_TERM;
			}
			else
			{
				result = (result << 1) & 0x0F;
			}
		}

		break;

	case 9: /* Used in SAES Decryption */

		for (uint8 i = 0; i < 3; i++)
		{
			/* Reading Bit 3 in data to determine what will be done in the multiplication operation */
			if ((result >> 3) == 1)
			{
				result = ((result << 1) & 0x0F) ^ GF_MUL_PRECOMPUTED_TERM;
			}
			else
			{
				result = (result << 1) & 0x0F;
			}
		}

		result = result ^ data;
		break;

	default:
		break;
	}

	return result;
}