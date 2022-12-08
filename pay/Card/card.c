#include<stdio.h>
#include<string.h>
#include"card.h"
#define  _CRT_SECURE_NO_WARNINGS

ST_cardData_t card1;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
	printf("enter card holder name : \n");
	
	//char name[100];
	gets(cardData->cardHolderName);
		//strcpy_s(cardData->cardHolderName, 30, "beboismailelkholyaaa");
	printf(" \n");
	
	if (strlen(cardData->cardHolderName) <= 24 && strlen(cardData->cardHolderName) >= 20) {
		return CARD_OK;
		
	}
	else {
		return WRONG_NAME;
	}
	
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	  printf("enter card expiry date: MM/YY \n");
	  gets(cardData->cardExpirationDate);
	  //strcpy_s(cardData->cardExpirationDate, 30, "12/25");
	  printf(" \n");

	if (strlen(cardData->cardExpirationDate) == 5 && cardData->cardExpirationDate[2] == '/' && cardData->cardExpirationDate[0] >= 48 && cardData->cardExpirationDate[0] <= 57 && cardData->cardExpirationDate[1] >= 48 && cardData->cardExpirationDate[1] <= 57 && cardData->cardExpirationDate[3] >= 48 && cardData->cardExpirationDate[3] <= 57 && cardData->cardExpirationDate[4] >= 48 && cardData->cardExpirationDate[4] <= 57) {
		return CARD_OK;
	}
	else {
		return WRONG_EXP_DATE;
	}
}



EN_cardError_t getCardPAN(ST_cardData_t * cardData) {
	printf("enter card PAN number: \n");
	gets(cardData->primaryAccountNumber);
	//strcpy_s(cardData->primaryAccountNumber, 16, "1989374615436851");
	printf(" \n");
	//uint8_t primaryAccountNumber1[20];
	//strcpy_s(primaryAccountNumber1, 20,cardData->primaryAccountNumber);
	int i;
	
	//i= strlen(cardData->primaryAccountNumber);
	
	if(strlen(cardData->primaryAccountNumber)>=16&& strlen( cardData->primaryAccountNumber)<=19){
		
		return CARD_OK;
    }



	return WRONG_PAN;
}

/*
void getCardHolderNameTest(void) {
	char test_cases[4][30] = { "beboismailelkholyaaa", "beboismailelkholyaaabb", "beboismailelkholymohamedq", ""};
	char expected  [4][20] = { "CARD_OK","CARD_OK","WRONG_NAME","WRONG_NAME" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name: getCardHolderName\n");
	//ST_cardData_t card1;
	char errors[4][30] = { "CARD_OK","WRONG_NAME","WRONG_EXP_DATE","WRONG_PAN" };

	
	for (int i = 0; i < 4; i++) {
		printf("Test case : %d \n", i+1);
		printf("Input data :%s \n", test_cases[i]);
		printf("expected result : %s\n", expected[i]);
		strcpy_s(card1.cardHolderName,sizeof(test_cases[i]), test_cases[i]);
		printf("Actual Result :" );
		printf("%s\n", errors[getCardHolderName(&card1)]);
		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
        

		

       
	}
}
void getCardExpiryDateTest(void) {
	char test_cases[4][30] = { "24/02/2022", "15//10", "12/25", "" };
	char expected[4][20] = { "WRONG_EXP_DATE","WRONG_EXP_DATE","CARD_OK","WRONG_EXP_DATE" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name: cardExpirationDate\n");
	ST_cardData_t card1;
	char errors[4][30] = { "CARD_OK","WRONG_NAME","WRONG_EXP_DATE","WRONG_PAN" };


	for (int i = 0; i < 4; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s \n", test_cases[i]);
		printf("expected result : %s\n", expected[i]);
		strcpy_s(card1.cardExpirationDate, sizeof(test_cases[i]), test_cases[i]);
		printf("Actual Result :");
		printf("%s\n", errors[getCardExpiryDate(&card1)]);
		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");





	}
}

void getCardPANTest(void) {
	char test_cases[4][34] = { "1234567891234567", "1234561", "128912111111111111111", "" };
	char expected[4][20] = { "CARD_OK","WRONG_PAN","CARD_OK","WRONG_PAN" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name: getCardPAN\n");
	ST_cardData_t card2;
	char errors[4][30] = { "CARD_OK","WRONG_NAME","WRONG_EXP_DATE","WRONG_PAN" };


	for (int i = 0; i < 4; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s \n", test_cases[i]);
		printf("expected result : %s\n", expected[i]);
		strcpy_s(card2.primaryAccountNumber, sizeof(test_cases[i]), test_cases[i]);
		printf("Actual Result :");
		printf("%s\n", errors[getCardPAN(&card2)]);
		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");





	}
}*/