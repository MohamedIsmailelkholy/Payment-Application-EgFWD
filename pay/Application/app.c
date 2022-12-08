#include<stdio.h>
#include"../Server/server.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include<string.h>
#include"app.h"
char transstates[5][30] = { "APPROVED"," DECLINED_INSUFFECIENT_FUND"," DECLINED_STOLEN_CARD", "FRAUD_CARD"," INTERNAL_SERVER_ERROR" };
char serverstates[6][30] = { "SERVER_OK","SAVING_FAILED","TRANSACTION_NOT_FOUND","ACCOUNT_NOT_FOUND","LOW_BALANCE","BLOCKED_ACCOUNT"};
//#include "../Card/card.c"
//#include "../Terminal/terminal.c"

extern  ST_cardData_t  card1;
extern  ST_terminalData_t terminal1;
extern  ST_accountsDB_t  accountsDB;
extern ST_accountsDB_t refernceaccount1;
ST_transaction_t transaction1;
void appStart(void) {
	int a = getCardHolderName(&card1);
	if (a != 0) {
		printf("WRONG_NAME\n");
		return;
	}
	//printf("CARD_OK\n");
	int l = getCardExpiryDate(&card1);
	if (l != 0) {
		printf("WRONG_EXP_DATE\n");
		return;
	}
	//printf("CARD_OK\n");
	int r = getCardPAN(&card1);
	if (r != 0) {
		printf("WRONG_PAN\n");
		return;
	}
	printf("CARD_OK\n");
	int q=getTransactionDate(&terminal1);
	if (q != 0) {
		printf("WRONG_DATE\n");
		return;
	}


	//printf("TERMINAL_OK\n");
int	z=isCardExpired(&card1, &terminal1);
	if (z != 0) {
		printf("EXPIRED_CARD\n");
		return;
	}
	
	int b=getTransactionAmount(&terminal1);
	if (b != 0) {
		printf("INVALID_AMOUNT\n");
		return;}
	//printf("TERMINAL_OK\n");
    int c=setMaxAmount(&terminal1, 1000);
	if (c != 0) {
		printf("INVALID_MAX_AMOUNT\n");
		return;
	}printf("maxtrnsaction amount is 1000 EGP\n");
	//printf("TERMINAL_OK\n");
	int d = isBelowMaxAmount(&terminal1);
	if (d != 0) {
		printf("EXCEED_MAX_AMOUNT\n");
		transaction1.cardHolderData = card1;
		transaction1.terminalData = terminal1;
		//recieveTransactionData(&transaction1);
		//saveTransaction(&transaction1);
		//listSavedTransactions();
		return;
	}

	printf("TERMINAL_OK\n");

	//refernceaccount1
	int o  =isValidAccount(&card1, &refernceaccount1);
	
	if (o != 0) {
		printf("ACCOUNT_NOT_FOUND\n");
		return;
	}
	int f = 0;
		isAmountAvailable(&terminal1, &refernceaccount1);
	//printf("%s\n", serverstates[f]);
	if (f != 0) {
		printf("LOW_BALANCE\n");
		return;
	}
	transaction1.cardHolderData = card1;
	transaction1.terminalData = terminal1;
	int u=isBlockedAccount(&refernceaccount1);
	if (u != 0) {
		printf("BLOCKED_ACCOUNT\n");
		recieveTransactionData(&transaction1);
		saveTransaction(&transaction1);
		
		listSavedTransactions();
		return;
	}
	
	

	int p=recieveTransactionData(&transaction1);
	if (p != 0) {
		printf("%s\n",transstates[p]);
		recieveTransactionData(&transaction1);
		saveTransaction(&transaction1);
		listSavedTransactions();
		return;
	}

	saveTransaction(&transaction1);
	//printf("SERVER_OK\n");
	printf("Transaction Approved\n");
	listSavedTransactions();
	return;
}
int main() {
	appStart();
}