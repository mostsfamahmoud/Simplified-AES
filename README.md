
# Simplified AES Implementation

## Overview

This repository contains a C implementation of Simplified AES (SAES) encryption and decryption algorithms. The code provides functionality to encrypt and decrypt 16-bit data using a 16-bit key.

## File Structure

- `SAES.c` - Contains the SAES implementation.
- `SAES.h` - Header file for SAES with function declarations and necessary definitions.
- `SAES_test.c` - Test harness for the SAES implementation.

## Features
- Educational Focus: The code emphasizes clarity and simplicity, serving as an educational resource for understanding the fundamental concepts of AES encryption.

- Command-Line Interface: Includes a user-friendly command-line interface for effortless encryption and decryption of data using custom keys, enhancing usability and accessibility.

- Modular Architecture: Utilizes a modular structure with separate functions for key expansion, substitution, and mixing columns. This design choice promotes readability and allows for easy expansion or modification.
## Installation

Clone this repository:

```bash
    git clone https://github.com/mostsfamahmoud/Simplified-AES.git
```


## How To Use

### Compilation
To compile the code, use a C compiler such as GCC:

```bash
  gcc SAES.c SAES_test.c -o SAES_test.exe
```


### Running Tests
The provided test cases can be executed using the batch file `run_mytestcases.bat`:

```bash
  ./run_mytestcases.bat
```
This batch file reads test cases from `mytestcases.txt`, executes the SAES test program with the given parameters, and displays the results.

### Test Cases
The test cases cover various scenarios of encryption and decryption with valid and invalid inputs.

- Each test case format: Operation Key Data
- Operations: `ENC` for encryption, `DEC` for decryption.
- Key and Data should be 4-character hexadecimal strings.
- Invalid inputs will display error messages.

## Simple Usage
Example test cases and their expected output:

```bash
  ENC A73B 6F6B -> C2AA
  DEC AB89 -> ERROR: Invalid number of parameters
  ...
```
## Demo

Insert gif or link to demo


## Documentation

[Simplified AES](https://drive.google.com/drive/u/0/folders/1aMXZ8JHq6x5-J9e_ccthcW4Aejpd0uB8)
## Acknowledgements

 - [Simplified AES - Northern Kentucky University](https://www.nku.edu/~christensen/simplified%20AES.pdf)
 - [Simplified AES - sandilands.info](https://sandilands.info/sgordon/teaching/reports/simplified-aes-example.pdf)
 - [Simplified AES - Description](https://drive.google.com/drive/u/0/folders/1aMXZ8JHq6x5-J9e_ccthcW4Aejpd0uB8)


## Feedback

If you have any feedback, please reach out to us at mostafamahmoud.cse@gmail.com


## 🔗 Links
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mostafa-mahmoud23/)


