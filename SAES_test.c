/**********************************************************************
 * SAES_test.c
 *
 * My test of Simplified AES Implementation
 *
 * Created on: Nov 18, 2023
 *
 * Author: Mostafa Mahmoud Ali Ahmed
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SAES.h"

/********************************* Main Helper Functions ***********************************/
boolean Character_isHexaDecimal(char ch) 
{
    return ((ch >= '0' && ch <= '9') ||
            (ch >= 'a' && ch <= 'f') ||
            (ch >= 'A' && ch <= 'F'));
}

/********************************* Main Function ***************************************/

int main(int argc, char** argv)
{
	// Check if the number of parameters passed from commandline is valid or not
    if (argc != 4)
    {
        printf("ERROR: Invalid number of parameters\nExpects: <ENC|DEC> <key> <data>\n");
        return 1; // Exiting early with an error code
    }

    char* operation = argv[1];

    // Check if the operation is valid
    if (strcmp(operation, "ENC") != 0 && strcmp(operation, "DEC") != 0)
    {
        printf("ERROR: Invalid Operation\n");
        return 1; // Exiting early with an error code
    }

    char* keyString = argv[2];

	// Check if the keyString length is not equal to 4
    if (strlen(keyString) != 4)
    {
        printf("ERROR: Invalid Key length\n");
        return 1; // Exiting early with an error code
    }

    // Check if the keyString contains only valid hexadecimal characters
    for (int i = 0; keyString[i] != '\0'; i++)
    {
        if (!Character_isHexaDecimal(keyString[i]))
        {
            printf("ERROR: Key contains non-hex characters\n");
            return 1; // Exiting early with an error code
        }
    }

    // Convert keyString to a uint16 value
    uint16 key = (uint16)strtoul(keyString, NULL, 16); // 16 for hexadecimal base

    if (strcmp(operation, "ENC") == 0)
    {
        char* plainTextString = argv[3];

		// Check if the plainTextString length is not equal to 4
   		if (strlen(plainTextString) != 4)
  		{
       		printf("ERROR: Invalid Data length\n");
       		return 1; // Exiting early with an error code
    	}

        // Check if the plainTextString contains only valid hexadecimal characters
        for (int i = 0; plainTextString[i] != '\0'; i++)
        {
            if (!Character_isHexaDecimal(plainTextString[i]))
            {
                printf("ERROR: Data contains non-hex characters\n");
                return 1; // Exiting early with an error code
            }
        }

        // Convert plainTextString to a uint16 value
        uint16 plaintext = (uint16)strtoul(plainTextString, NULL, 16); // 16 for hexadecimal base

        // Proceed with encryption...
		uint16 ciphertext = SAES_Encryption(plaintext,key);
		
		printf("%04X\n", ciphertext);
    }
    else if (strcmp(operation, "DEC") == 0)
    {
        char* cipherTextString = argv[3];

		// Check if the cipherTextString length is not equal to 4
   		if (strlen(cipherTextString) != 4)
  		{
       		printf("ERROR: Invalid Data length\n");
       		return 1; // Exiting early with an error code
    	}

        // Check if the cipherTextString contains only valid hexadecimal characters
        for (int i = 0; cipherTextString[i] != '\0'; i++)
        {
            if (!Character_isHexaDecimal(cipherTextString[i]))
            {
                printf("ERROR: Data contains non-hex characters\n");
                return 1; // Exiting early with an error code
            }
        }

        // Convert cipherTextString to a uint16 value
        uint16 ciphertext = (uint16)strtoul(cipherTextString, NULL, 16); // 16 for hexadecimal base

        // Proceed with decryption...
		uint16 plaintext = SAES_Decryption(ciphertext, key);

		printf("%04X\n", plaintext);
    }
    return 0;
}