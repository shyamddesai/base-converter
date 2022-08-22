/*============================================================================
Name : base2Base.c
Author : Shyam Desai (using template provided by Prof. Ferrie)
Version : 1.0
Date: December 1st, 2021
Description : A "C" command line program with three arguments:
: 1. A string corresponding to a number in a base from [2,36]
: 2. An integer corresponding to the base of the first argument
: 3. An integer corresponding to the base of the converted output.
============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
* Function Prototypes Here
*/
int string2Int(char *inString, int inBase, int *decValue);
char *int2String(int decValue, int outBase);
int char2Int(char inChar);
void reverseString(char* str);

/**
* Definitions Here
*/
#define MAXBUF 34 // Longest output string is 34 characters (sign) and '\0'
#define MINBASE 2 // Base ranges
#define MAXBASE 36
#define true 1 // Useful to define true and false
#define false !true

/**
* Globals Here
*/
static char *LUT = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Lookup table for conversions

/**
* The main routine parses input, calls conversion routines and prints the results.
* argv[0] = base2Base; argv[1] = input number; argv[2] = source base; argv[3] = target base
*/
int main(int argc, char *argv[]) {
	int inBase, outBase, decValue;

	//Error check - # of arguments
	if(argc != 4) {
		printf("Usage: base2Base [input-string] [input-base] [output-base]\n");
		exit(0);
	}

	//Get arguments and store them into variables
	char input[strlen(argv[1])];
	strcpy(input, argv[1]);
	inBase = atoi(argv[2]); //Converts the source base input at argv[2] into an integer
	outBase = atoi(argv[3]); //Converts the target base input at argv[3] into an integer

	//Error checks - Bases within allowed range [2, 36]
	if(inBase<MINBASE || inBase>MAXBASE) {
		printf("The input base must be between [2,36].\n");
		if(outBase<2 || outBase>36) printf("The output base must be between [2,36].\n");
		exit(0);
	}
	if(outBase<MINBASE || outBase>MAXBASE) {
			printf("The output base must be between [2,36].\n");
			exit(0);
	}

	//Error check - Correct representation of input base number
	int error = string2Int(input, inBase, &decValue); //Call string2Int() to convert the input number into decimal
	if(error == -1) {
		printf("%s does not correspond to a valid integer in Base-%d.\n", input, inBase);
		exit(0);
	}

	printf("%s has a value of %d as a decimal integer.\n", input, decValue); //Print decimal value

	//Call int2String() to convert from decimal into target base string
	char *result = int2String(decValue, outBase);
	printf("%s has an equivalent representation of %s in Base-%d.\n", input, result, outBase);
	free(result);

	printf("Program terminated.\n");
	return 0; //Successful termination
}

/**
* int string2Int(char *inString, int inBase, int *decValue);
* inString - input string representing number in inBase
* inBase - base corresponding to number above
* decValue - pointer to location in which to write return value
*
* returns - 0 no error, 1 invalid representation for specified base

* Credit: Pseudocode from Fall2021-Assignment 5 Handout
*/
int string2Int(char *inString, int inBase, int *decValue) {
	int sum = 0; int power = 1; int sign = 1;
	int length = strlen(inString);

	for(int i = length -1; i >= 0; i--) {
		char current = inString[i]; //Get current character

		if(i == 0 && current == '-') {
			sign = -1;
		} else { //Convert to integer
			int index = char2Int(current);
			if(index == -1 || index >= inBase) return -1; //Error either if index not in LUT, or if index more than inBase

			//Recompute sum
			sum = sum + index*power;
			power = power*inBase;
		}
	}

	sum = sum*sign;
	*decValue = sum; //Write sum to location referenced by decValue

	return 0;
}

/**
* int char2Int(char inChar)
* inChar - character to search for in LUT
* returns - the index if found, otherwise -1
*/
int char2Int(char inChar) {
	if (inChar >= 'a' && inChar <= 'z') inChar = toupper(inChar); //Convert lowercase character to uppercase

	char *value = strchr(LUT, inChar); //Search for the character in lookup table
	if(value == NULL)	return -1;

	int index = (int) (value - LUT);
	return index; //Return the index of the character
}

/**
* char *int2String(int decValue, int outBase);
* decValue - decimal value to encode as a string in target base
* outBase - the target base to convert to
*
Credit: Pseudocode from Fall2021-Assignment 5 Handout
*/
char *int2String(int decValue, int outBase) {
	char *buffer = (char*)malloc(MAXBUF*sizeof(char)); //Allocate buffer space
	if(buffer == NULL) {
		printf("Program Terminated.");
		exit(0);
	}
	
	int arg = abs(decValue);
	int index = 0;
	
	while(arg >0) {
		int current = arg%outBase;
		arg = arg/outBase;
		buffer[index++] = LUT[current]; //Convert index to character
	}
	
	if(decValue < 0) buffer[index++] = '-'; //Add in sign
	buffer[index] = '\0'; //Add end-of-string terminator
	
	reverseString(buffer);
	
	return buffer;
}

/**
 *Reverse a character array
 *The method swaps the first and last element until reached half the size of the array
 */
void reverseString(char* str) {
	int length = strlen(str);
	for(int i=0; i<length/2; i++) {
		char temp = str[i];
		str[i] = str[length-i-1];
		str[length-i-1] = temp;
	}
}
