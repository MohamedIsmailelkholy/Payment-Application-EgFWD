#include<stdio.h>
#include<time.h>
#include<string.h>
#include "../Card/card.h"
#include <stdlib.h>
#include"Terminal.h"
#pragma Buffer overrun while writing to
struct tm date;
ST_terminalData_t terminal1;
extern ST_cardData_t card1;
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
	printf("Enter transaction date: \n");

		//strcpy_s((*termData).transactionDate,11, "" + date.tm_mday + '/' + date.tm_mon + '/' + date.tm_year );
		gets(termData->transactionDate);
		printf("\n");

	if (strlen(termData->transactionDate) == 5 && (termData->transactionDate[2] == '/') ) {
		return TERMINAL_OK;
	}

		return WRONG_DATE;
	
	}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	
	char* expirationDateYears = &card1.cardExpirationDate[3];
	// first 2 digits indicates to month
	char* expirationDateMonths = &card1.cardExpirationDate[0];

	// terminal date example: DD/MM/YYYY
	// last 2 digits indicates to years that will be compared
	char* terminalDateYears = &terminal1.transactionDate[3];
	char* terminalDateMonths = &terminal1.transactionDate[0];
	//creating integers with a format of "YYMM" to compare between them
	int expirationDateInt = 100 * atoi(expirationDateYears) + atoi(expirationDateMonths);
	int terminalDateInt = 100 * atoi(terminalDateYears) + atoi(terminalDateMonths);
	// comparing
	if (terminalDateInt < expirationDateInt) {
		return TERMINAL_OK;
	}
	else {
		return EXPIRED_CARD;
	}
	
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("enter transaction amount: \n ");
	scanf_s("%f", &termData->transAmount);
	printf("\n");
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount <= termData->maxTransAmount) {
		return TERMINAL_OK;

	}
	else {
		return EXCEED_MAX_AMOUNT;
	}

}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	if (maxAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}
//EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional
/*
void getTransactionDateTest(void) {
	char test_cases[4][34] = { "18/12/1998", "10", "12/5", "" };
	char expected[4][20] = {"TERMINAL_OK", " WRONG_DATE" ," WRONG_DATE" ," WRONG_DATE" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:getTransactionDate \n");
	ST_terminalData_t terminal1;
	char errors[7][30] = { "TERMINAL_OK"," WRONG_DATE"," EXPIRED_CARD", "INVALID_CARD"," INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };


	for (int i = 0; i < 4; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s \n", test_cases[i]);
		printf("expected result : %s\n", expected[i]);
		strcpy_s(terminal1.transactionDate, sizeof(test_cases[i]), test_cases[i]);
		printf("Actual Result :");
		printf("%s\n", errors[getTransactionDate(&terminal1)]);
		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void isCardExpriedTest(void) {
	char test_cases[4][34] = { "12/1998", "10/22", "12/25", "11/19" };
	char expected[4][20] = { "EXPIRED_CARD", "EXPIRED_CARD" ,"TERMINAL_OK " ,"EXPIRED_CARD" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:isCardExpriedTest \n");
	ST_terminalData_t terminal1;
	char errors[7][30] = { "TERMINAL_OK"," WRONG_DATE"," EXPIRED_CARD", "INVALID_CARD"," INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };
	ST_cardData_t card1;
	//llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	for (int i = 0; i < 4; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s \n", test_cases[i]);
		printf("expected result : %s\n", expected[i]);
		strcpy_s(card1.cardExpirationDate, sizeof(test_cases[i]), test_cases[i]);
		printf("Actual Result :%s\n", errors[isCardExpired(&card1, &terminal1)]);
		
		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
	}
}
 ////////////////////////////////////////////////////////////////////////////
 
  /*
 
 /////////////////////////////////////////////////////////////////////////////
 void getTransactionAmountTest(void) {
	 int test_cases[4] = { 0, -100, 100, 1000 };
	 char expected[4][20] = { "INVALID_AMOUNT", "INVALID_AMOUNT" ,"TERMINAL_OK " ,"TERMINAL_OK" };
	 printf("Tester Name :Mohamed Ismail\n");
	 printf("Function Name:getTransactionAmountTest \n");
	 ST_terminalData_t terminal1;
	 char errors[7][30] = { "TERMINAL_OK"," WRONG_DATE"," EXPIRED_CARD", "INVALID_CARD"," INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };
	 //ST_cardData_t card1;
	 //llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	 for (int i = 0; i < 4; i++) {
		 printf("Test case : %d \n", i + 1);
		 printf("Input data :%d \n", test_cases[i]);
		 printf("expected result : %s\n", expected[i]);
		 terminal1.transAmount=test_cases[i];
		 printf("Actual Result :%s\n", errors[getTransactionAmount (& terminal1)]);

		 //printf("%d\n", egetCardHolderName(&card1));
		 printf("      .\n");
		 printf("      .\n");
		 printf("      .\n");
	 }
 }
//////////////////////////////////////////////////////////////////////////


 void isBelowMaxAmountTest(void) {
	 int test_cases[4] = { 1200, 100000000, 100, 1000 };
	 char expected[4][20] = { "TERMINAL_OK", "EXCEED_MAX_AMOUNT" ,"TERMINAL_OK " ,"TERMINAL_OK" };
	 printf("Tester Name :Mohamed Ismail\n");
	 printf("Function Name:isBelowMaxAmount \n");
	 ST_terminalData_t terminal1;
	// terminal1.maxTransAmount = 2000.2;
	 char errors[7][30] = { "TERMINAL_OK"," WRONG_DATE"," EXPIRED_CARD", "INVALID_CARD"," INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };
	 //ST_cardData_t card1;
	 //llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	 for (int i = 0; i < 4; i++) {
		 printf("Test case : %d \n", i + 1);
		 printf("Input data :%d \n", test_cases[i]);
		 printf("expected result : %s\n", expected[i]);
		 terminal1.transAmount = test_cases[i];
		 printf("Actual Result :%s\n", errors[isBelowMaxAmount(&terminal1)]);

		 //printf("%d\n", egetCardHolderName(&card1));
		 printf("      .\n");
		 printf("      .\n");
		 printf("      .\n");
	 }
 }
 ///////////////////////////////////////////////////////////////////////////////////
 /*
 void setMaxAmountTest(void) {
	 int test_cases[4] = { 0, -1, 1000, 100 };
	 char expected[4][20] = { "INVALID_MAX_AMOUNT ", "INVALID_MAX_AMOUNT " ,"TERMINAL_OK " ,"TERMINAL_OK" };
	 printf("Tester Name :Mohamed Ismail\n");
	 printf("Function Name:setMaxAmount \n");
	 ST_terminalData_t terminal1;
	 
	 char errors[7][30] = { "TERMINAL_OK"," WRONG_DATE"," EXPIRED_CARD", "INVALID_CARD"," INVALID_AMOUNT", "EXCEED_MAX_AMOUNT", "INVALID_MAX_AMOUNT" };
	 //ST_cardData_t card1;
	 //llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	 for (int i = 0; i < 4; i++) {
		 printf("Test case : %d \n", i + 1);
		 printf("Input data :%d \n", test_cases[i]);
		 printf("expected result : %s\n", expected[i]);
		 printf("Actual Result :%s\n", errors[setMaxAmount(&terminal1, test_cases[i])]);

		 //printf("%d\n", egetCardHolderName(&card1));
		 printf("      .\n");
		 printf("      .\n");
		 printf("      .\n");
	 }



 }*/


