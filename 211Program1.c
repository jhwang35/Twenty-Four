/*
	Program 1: TwentyFour

	The goal of this game is to make the number 24 from the four numbers shown.
	You can add, subtract, multiply and divide. 
	Use all four numbers shown, but use each number only once.
	You do not have to use all four operations.

	As an example, consider these four numbers: 3 9 4 1.
	One possible solution would be:
		3 * 9 = 27.
		27 - 4 = 23.
		23 + 1 = 24.

	UIC CS 211, Spring 2023
	Author: Justin Hwang, 1/26/2023
	System: Replit
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Global constants
const int TRUE = 1;    // TRUE is 1, FALSE is 0
const int FALSE = 0;

const int NUM_SOLUTIONS = 3188;

// If easy mode is on, the user is presented with a random puzzle from a
//	selection of 10 puzzles
// These puzzles are always the same, so we save them in a global constant 2D array
const int easyPuzzles[10][4] = {
	{3, 9, 4, 1},
	{8, 5, 8, 1},
	{6, 1, 5, 1},
	{2, 8, 7, 8},
	{5, 2, 9, 2},
	{2, 6, 8, 4},
	{5, 5, 4, 3},
	{6, 6, 2, 6},
	{8, 4, 2, 6},
	{6, 2, 8, 1}
};

//---------------------------------------------------------------------
//  displayUsage() - Display program usage message
//
void displayUsage() {
  printf("  USAGE:                                		\n");
  printf("	./main [-d debugMode] [-e easyMode]         \n");
  printf("                                        		\n");
  printf(" 	where the parameters are:           		\n");
  printf("	   [-d debugMode] = Whether or not to turn on debug display (1 for on / 0 for off)\n");
  printf("	   [-e easyMode] = Whether or not easy mode should be on (1 for on / 0 for off) \n");
  exit(0);
}//end displayUsage()

//---------------------------------------------------------------------
//  getArguments - Retrieve & store command line arguments
//
void getArguments(
    int argc,           // number of args, including prog. name
    char *argv[],       // array of strings
    int *debugValue,    // integer value to indicate if debug display is on
    int *easyModeValue) // integer value to indicate if easy mode is on
{
	while ((argc -= 2) > 0) { // while there is another pair of strings
		switch (argv[1][1]) { // handle options
			case 'd':
				*debugValue = atoi(argv[2]);
				break;
			case 'e':
				*easyModeValue = atoi(argv[2]);
				break;
	  		default:
				displayUsage();
		} // end switch
	
		argv += 2; // advance to next pair of command line options
	} // end while
}//end getArguments()

//---------------------------------------------------------------------
//  compute - Calculates an operation given a character and two numbers
//
double compute(double num1, char op, double num2) {
	switch(op) {
		case '+':
			return num1 + num2;
			break;
		case '-':
			return num1 - num2;
			break;
		case '*':
			return num1 * num2;
			break;
		case '/':
			return num1 / num2;
			break;
		default: // this should never happen!
			return -1.0;
			break;
	}
}//end compute()

//---------------------------------------------------------------------
//  findAllSolutions() - Finds all the possible solutions
//						 using the numbers 1-9 and operators +, -, *, /
//						 The solutions are saved into a 2D integer array.
//						 If debug mode is on, the solutions are also printed.
//
void findAllSolutions(int allPuzzles[][4], int debugModeValue) {
	// Uncomment the following lines to write it to a file instead
	// FILE *fOut;
	// fOut = fopen("solutions.txt", "w");
	
	int solutionCount = 1;
	char allOperators[4] = {'+', '-', '*', '/'};
	for(double num1=1; num1<10; num1++) {   
		for(double num2=1; num2<10; num2++) {
				for(double num3=1; num3<10; num3++) {
						for(double num4=1; num4<10; num4++) {
							for(int i=0; i<4; i++) {
								double result = compute(num1, allOperators[i], num2);
					for(int j=0; j<4; j++) {
						double result2 = compute(result, allOperators[j], num3);
							for(int k=0; k<4; k++) {
								double finalResult = compute(result2, allOperators[k], num4);
								if(fabs(finalResult-24.0) < 0.001) {
									// Uncomment the following lines to write it to a file instead
									// char line[100];
									// sprintf(line, "%d. %d%c%d%c%d%c%d\n", solutionCount++, 
									// 	(int)num1, allOperators[i], (int)num2, allOperators[j], (int)num3, allOperators[k], (int)num4);
									// fputs(line, fOut);
									if(debugModeValue == TRUE) {
										printf("%d. %d%c%d%c%d%c%d\n", solutionCount, 
											(int)num1, allOperators[i], (int)num2, allOperators[j], (int)num3, allOperators[k], (int)num4);
									}
									allPuzzles[solutionCount - 1][0] = num1;
									allPuzzles[solutionCount - 1][1] = num2;
									allPuzzles[solutionCount - 1][2] = num3;
									allPuzzles[solutionCount - 1][3] = num4;
									solutionCount++;
								}//end if(compute(...
							}
						}
					}
				}//end for(float num4...
			}//end for(float num3...
		}//end for(float num2...
	}//end for(float num1...
}//end findAllSolutions()

//---------------------------------------------------------------------
//  generatePuzzle() - Generates a random puzzle based on whether or not easy mode is on
//					   Saves the four numbers of the puzzle into num1, num2, num3, num4
//							(hence, they are pass-by-reference parameters)
void generatePuzzle(int easyModeValue, int allPuzzles[][4], int* num1, int* num2, int* num3, int* num4) {
	
	// If easy mode is on, the user is presented with a random puzzle from a
	//	selection of 10 puzzles
	if(easyModeValue == TRUE) {
		int randValue = rand() % 10; // gives us a random value from 0 to 9
		*num1 = easyPuzzles[randValue][0];
		*num2 = easyPuzzles[randValue][1];
		*num3 = easyPuzzles[randValue][2];
		*num4 = easyPuzzles[randValue][3];
	}
	else {
		int randValue = rand() % NUM_SOLUTIONS;
		*num1 = allPuzzles[randValue][0];
		*num2 = allPuzzles[randValue][1];
		*num3 = allPuzzles[randValue][2];
		*num4 = allPuzzles[randValue][3];
	}
}//end generatePuzzle()

//---------------------------------------------------------------------
int main(int argc, char* argv[]) {

	// Seed random number generator with value of 1 for testing purposes
	srand(1);
	// Uncomment the line below for different random values each time
	// srand(time(0));

	// Display welcome message
	printf("Welcome to the game of TwentyFour.\n");
	printf("Use each of the four numbers shown below exactly once, \n");
	printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
	printf("to yield the value twenty-four.\n\n");

	// Default values: debug display is off, and easy mode is on
	int debugMode = FALSE;
	int easyMode = TRUE;

	// Determine if user entered choices for debug display and easy mode
	getArguments(argc, argv, &debugMode, &easyMode);

	// Find all the solutions and save them into allPuzzles
	// The function will also print them if debug display is on
	int allPuzzles[NUM_SOLUTIONS][4];
	findAllSolutions(allPuzzles, debugMode);

	// Loop to play the game
	int done = FALSE;
	while(!done) {

		// Determine and output the puzzle
		int num1=0, num2=0, num3=0, num4=0;
		generatePuzzle(easyMode, allPuzzles, &num1, &num2, &num3, &num4);
		printf("The numbers to use are: ");
		printf("%d, %d, %d, %d.\n", num1, num2, num3, num4);
	
		// Read in user input of the operators to use
		char operators[100];
		printf("Enter the three operators to be used, in order (+,-,*, or /): ");
		scanf("%s", operators);
	
		// Check that the user entered 3 operators
		if(strlen(operators) != 3) {
			printf("Error! The number of operators is incorrect. Please try again.\n\n");
			continue;
		}
	
		// Check that the operators entered are +, -, *, and / only
		int invalidOperatorEntered = FALSE;
		for(int i=0; i<strlen(operators); i++) {
			if(operators[i] != '+' && operators[i] != '-'
				&& operators[i] != '*' && operators[i] != '/') {
				printf("Error! Invalid operator entered. Please try again.\n\n");
				invalidOperatorEntered = TRUE;
				break;
			}
		}
		if(invalidOperatorEntered) {
			continue;
		}
	
		// Perform the calculation to check that the result is 24
		int answerSoFar = 0;
		switch(operators[0]) {
			case '+':
				answerSoFar = num1 + num2;
				break;
			case '-':
				answerSoFar = num1 - num2;
				break;
			case '*':
				answerSoFar = num1 * num2;
				break;
			case '/':
				answerSoFar = num1 / num2;
				break;
			default: // this should never happen!
				answerSoFar = -1;
				break;
		}
		printf("%d %c %d = %d.\n", num1, operators[0], num2, answerSoFar);
	
		int answerSoFarPrev = answerSoFar;
		switch(operators[1]) {
			case '+':
				answerSoFar = answerSoFar + num3;
				break;
			case '-':
				answerSoFar = answerSoFar - num3;
				break;
			case '*':
				answerSoFar = answerSoFar * num3;
				break;
			case '/':
				answerSoFar = answerSoFar / num3;
				break;
			default: // this should never happen!
				answerSoFar = -1;
				break;
		}
		printf("%d %c %d = %d.\n", answerSoFarPrev, operators[1], num3, answerSoFar);
	
		answerSoFarPrev = answerSoFar;
		switch(operators[2]) {
			case '+':
				answerSoFar = answerSoFar + num4;
				break;
			case '-':
				answerSoFar = answerSoFar - num4;
				break;
			case '*':
				answerSoFar = answerSoFar * num4;
				break;
			case '/':
				answerSoFar = answerSoFar / num4;
				break;
			default: // this should never happen!
				answerSoFar = -1;
				break;
		}
		printf("%d %c %d = %d.\n", answerSoFarPrev, operators[2], num4, answerSoFar);
	
		if(answerSoFar != 24) {
			printf("Sorry. Your solution did not evaluate to 24.\n\n");
		}
		else{
			printf("Well done! You are a math genius.\n\n");
		}

		// Ask the user if they would like to play again
		printf("Would you like to play again? Enter N for no and any other character for yes. ");
		char playAgainInput = ' ';
		scanf(" %c", &playAgainInput);
		if(playAgainInput == 'N') {
			done = TRUE;
		}
		printf("\n");
	}

	printf("Thanks for playing!\n\n");
	return 0;
}