#include<stdio.h>
#include"server.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include<string.h>
ST_accountsDB_t refernceaccount1;
extern char transstates[5][30];
ST_accountsDB_t accountsDB[255]=
    {{500, RUNNING,"89893746154367711"},
	{0.0,   RUNNING,"1989374615436851"},
	{500.0, RUNNING,"1189374615436851"},
	{200.0, RUNNING,"3389374615436851"},
	{2000.0,RUNNING,"4489374615436851"},
	{3000.0,RUNNING,"2289374615436851"},
	{01212, RUNNING,"7989374615436851"},
	{1020,  BLOCKED,"5907007076043875"},
	{1000  ,BLOCKED,"5807021076043875"},
	{18900 ,BLOCKED,"5807707076043875"},
	{17800, BLOCKED,"5817007076043875"}};


ST_transaction_t TransactionDB[255]={ {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
EN_transStat_t  recieveTransactionData(ST_transaction_t* transData) {
	int flag = 0;
	int i;
	for ( i = 0; i < 11; i++) {
		if (strcmp(transData->cardHolderData.primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {

			flag = 1;
			break;
		}

	}

	if (flag == 1) {
		if (refernceaccount1.state == 1) {
			transData->transState = DECLINED_STOLEN_CARD;
			return DECLINED_STOLEN_CARD;
		}
		else if (refernceaccount1.balance < transData->terminalData.transAmount) {
			transData->transState = DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
		}

		else {
			refernceaccount1.balance = refernceaccount1.balance - transData->terminalData.transAmount;
			transData->transState = APPROVED;
			return APPROVED;

		}
	}
	else {
		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}
	transData->transState = INTERNAL_SERVER_ERROR;
	return INTERNAL_SERVER_ERROR;


}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	int i;
	for (i = 0; i < 11; i++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
		//	refernceaccount1 = &accountsDB[i];
			refernceaccount1.balance = accountsDB[i].balance;
			strcpy_s(refernceaccount1.primaryAccountNumber, 25, accountsDB[i].primaryAccountNumber);
			refernceaccount1.state = accountsDB[i].state;
			

			return SERVER_OK;
		}
	}
	
	return ACCOUNT_NOT_FOUND;
	
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence) {
	if (accountRefrence->state == BLOCKED) {
		return BLOCKED_ACCOUNT;
}
	else {
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t *accountRefrence) {
	if (termData->transAmount > accountRefrence->balance) {
		return LOW_BALANCE;
  }
	else {
		return SERVER_OK;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	static int sequenc_number = 0;
	TransactionDB[sequenc_number].cardHolderData = transData->cardHolderData;
	TransactionDB[sequenc_number].terminalData = transData->terminalData;
	TransactionDB[sequenc_number].transState = transData->transState;
	TransactionDB[sequenc_number].transactionSequenceNumber = 1;
	sequenc_number = sequenc_number + 1;
	
	return SERVER_OK;
}
void listSavedTransactions(void) {
	int x = 0;
	//while (TransactionDB[x].transactionSequenceNumber >0) {
		printf("Transaction Sequence Number :%d\n", TransactionDB[x].transactionSequenceNumber);
		printf("Transaction Date :%s\n", TransactionDB[x].terminalData.transactionDate);
		printf("Transaction Amount :%f\n", TransactionDB[x].terminalData.transAmount);
		printf("Transaction State :%s\n", transstates[TransactionDB[x].transState]);
		printf("Terminal Max Amount :%f\n", TransactionDB[x].terminalData.maxTransAmount);
		printf("Cardholder Name :%s\n", TransactionDB[x].cardHolderData.cardHolderName);
		printf("PAN:%s\n", TransactionDB[x].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date:%s\n", TransactionDB[x].cardHolderData.cardExpirationDate);
		printf("the balance is:  %f\n", refernceaccount1.balance);
		printf("################################################\n");
		printf("                 .                .                      .                      .                   .\n");
		
		x++;
	
	return;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void isValidAccountTest(void) {
	ST_cardData_t test_cases[2];
	strcpy_s(test_cases[0].primaryAccountNumber, 25, "5807707076043875");
	strcpy_s(test_cases[1].primaryAccountNumber, 25, "1189375255436851");

	char expected[2][30] = { "SERVER_OK", "ACCOUNT_NOT_FOUND" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:isValidAccountTest \n");
	//ST_transaction_t transaction1;
	char errors[6][30] = { "SERVER_OK"," SAVING_FAILED"," TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND"," LOW_BALANCE","BLOCKED_ACCOUNT" };
	//ST_cardData_t card1;
	//llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	for (int i = 0; i < 2; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s \n", test_cases[i].primaryAccountNumber);
		printf("expected result : %s\n", expected[i]);

		printf("Actual Result :%s\n", errors[isValidAccount(&test_cases[i], &accountsDB)]);

		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
	}
}

void recieveTransactionDataTest(void) {
	
	ST_transaction_t test_cases[4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	strcpy_s(test_cases[0].cardHolderData.primaryAccountNumber, 25, "189374615436851");
	strcpy_s(test_cases[1].cardHolderData.primaryAccountNumber, 25, "1189374615436851");
	strcpy_s(test_cases[2].cardHolderData.primaryAccountNumber, 25, "5807021076043875");
	strcpy_s(test_cases[3].cardHolderData.primaryAccountNumber, 25, "4489374615436851");

	char expected[4][30] = { "FRAUD_CARD", "DECLINED_INSUFFECIENT_FUND" ,"DECLINED_STOLEN_CARD " ,"APPROVED" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:recieveTransactionDataTest \n");
	ST_transaction_t transaction1;
	char errors[5][30] = { "APPROVED"," DECLINED_INSUFFECIENT_FUND"," DECLINED_STOLEN_CARD", "FRAUD_CARD"," INTERNAL_SERVER_ERROR" };
	//ST_cardData_t card1;
	//llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	for (int i = 0; i < 4; i++) {
		printf("Test case : %d \n", i + 1);
		//printf("Input data :%d \n", test_cases[i]);
		printf("expected result : %s\n", expected[i]);
		transaction1 = test_cases[i];
		printf("Actual Result :%s\n", errors[recieveTransactionData(&transaction1)]);

		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");




	}
}

void isBlockedAccountTest(void) {

	ST_accountsDB_t test_cases[2];
	strcpy_s(test_cases[0]. primaryAccountNumber, 25, "1189374615436851");
	strcpy_s(test_cases[1].primaryAccountNumber, 25, "5817007076043875");
	test_cases[0].state = RUNNING;
	test_cases[1].state = BLOCKED;
	char expected[2][30] = { "SERVER_OK", "BLOCKED_ACCOUNT" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:isBlockedAccountTest \n");
	//ST_transaction_t transaction1;
	char errors[6][30] = { "SERVER_OK"," SAVING_FAILED"," TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND"," LOW_BALANCE","BLOCKED_ACCOUNT" };
	//ST_cardData_t card1;
	//llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	for (int i = 0; i < 2; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s \n", test_cases[i].primaryAccountNumber);
		printf("expected result : %s\n", expected[i]);

		printf("Actual Result :%s\n", errors[isBlockedAccount(&test_cases[i])]);

		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
	}



}
///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void isAmountAvailableTest(void) {


	ST_accountsDB_t test_cases[2];
	strcpy_s(test_cases[0].primaryAccountNumber, 25, "1989374615436851");
	strcpy_s(test_cases[1].primaryAccountNumber, 25, "2289374615436851");
	ST_terminalData_t data[2];
	test_cases[0].balance = 10000;
	test_cases[1].balance = 10000;
	data[0].transAmount = 2000000.0;
	data[1].transAmount = 20.0;
	char expected[2][30] = { "LOW_BALANCE", "SERVER_OK" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:isAmountAvailableTest \n");
	
	char errors[6][30] = { "SERVER_OK"," SAVING_FAILED"," TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND"," LOW_BALANCE","BLOCKED_ACCOUNT" };
	//ST_cardData_t card1;
	//llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	for (int i = 0; i < 2; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%f\n", data[i].transAmount);
		printf("expected result : %s\n", expected[i]);

		printf("Actual Result :%s\n", errors[isAmountAvailable( &data[i], &test_cases[i])]);

		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
	}




}
void saveTransactionTest(void) {
	ST_transaction_t test_cases[2];
	strcpy_s(test_cases[0].cardHolderData.primaryAccountNumber, 25, "1989374615436851");
	strcpy_s(test_cases[1].cardHolderData. primaryAccountNumber, 25, "2289374615436851");
	test_cases[0].terminalData.transAmount = 10000;
	test_cases[1].terminalData.transAmount = 100;
	test_cases[0].transactionSequenceNumber = 1;
	test_cases[1].transactionSequenceNumber = 2;
	char expected[2][30] = { "SERVER_OK", "SERVER_OK" };
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:saveTransactionTest \n");

	char errors[6][30] = { "SERVER_OK"," SAVING_FAILED"," TRANSACTION_NOT_FOUND", "ACCOUNT_NOT_FOUND"," LOW_BALANCE","BLOCKED_ACCOUNT" };
	//ST_cardData_t card1;
	//llstrcpy_s(card1.cardExpirationDate, 5,"12/22");
	for (int i = 0; i < 2; i++) {
		printf("Test case : %d \n", i + 1);
		printf("Input data :%s\n", test_cases->cardHolderData.primaryAccountNumber);
		printf("expected result : %s\n", expected[i]);

		printf("Actual Result :%s\n", errors[saveTransaction( &test_cases[i])]);

		//printf("%d\n", egetCardHolderName(&card1));
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
void listSavedTransactionsTest(void) {
	printf("Tester Name :Mohamed Ismail\n");
	printf("Function Name:listSavedTransactions \n");
	
	strcpy_s(TransactionDB[0].cardHolderData.primaryAccountNumber, 25, "1989374615436851");
	strcpy_s(TransactionDB[1].cardHolderData.primaryAccountNumber, 25, "2289374615436851");

	TransactionDB[0].terminalData.transAmount = 10000;
	TransactionDB[1].terminalData.transAmount = 100;
	TransactionDB[0].transactionSequenceNumber = 1;
	TransactionDB[1].transactionSequenceNumber = 2;
	
	/*int x = 0;
	while (TransactionDB[x].transactionSequenceNumber > 0) {
		printf("Transaction Sequence Number :%d\n", TransactionDB[x].transactionSequenceNumber);
		printf("Transaction Date :%s\n", test_cases[x].terminalData.transactionDate);
		printf("Transaction Amount :%f\n", test_cases[x].terminalData.transAmount);
		printf("Transaction State :%d\n", test_cases[x].transState);
		printf("Terminal Max Amount :%f\n", test_cases[x].terminalData.maxTransAmount);
		printf("Cardholder Name :%s\n", test_cases[x].cardHolderData.cardHolderName);
		printf("PAN:%s\n", test_cases[x].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date:%s\n", test_cases[x].cardHolderData.cardExpirationDate);
		printf("################################################\n");
		printf("      .\n");
		printf("      .\n");
		printf("      .\n");
		x++;
	}*/
	printf("bob");
	listSavedTransactions();
	
	
}
























