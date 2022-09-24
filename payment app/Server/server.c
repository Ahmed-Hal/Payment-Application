#include "server.h"
#include <string.h>
#include "..\Terminal\terminal.h"

extern ST_accountsDB_t dataBase[250] = 
{ 
	{ 2000,RUNNING,"5807007076043875" },{ 3000,RUNNING,"5807007076043876" },
	{ 40000,BLOCKED,"5807007076043877" },{ 5000,RUNNING,"5807007076043878" },
	{ 6000,RUNNING,"5807007076043879" },{ 90000,BLOCKED,"5807007076043880" }
};

extern ST_transaction_t transactions[250] = { {0} };
int InDex = 0;
int T_index = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData, dataBase) == ACCOUNT_NOT_FOUND)
	{
		return FRAUD_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData)== LOW_BALANCE) 
	{
		return DECLINED_INSUFFECIENT_FUND; 
	}
	else if (isBlockedAccount(dataBase) == DECLINED_STOLEN_CARD)
	{
		return DECLINED_STOLEN_CARD;
	}
	else
	{
		dataBase[InDex].balance -= transData->terminalData.transAmount;
		transData->transState = APPROVED;	
	EN_serverError_t save = saveTransaction(transData);
	if (save == SAVING_FAILED) { return INTERNAL_SERVER_ERROR; }
	else return APPROVED;
	}

}

EN_serverError_t isValidAccount(ST_cardData_t * cardData, ST_accountsDB_t * accountRefrence)
{
	int flag , index = 0 ;

	for ( index = 0; index < 6; index++)
	{
		if (strcmp( cardData->primaryAccountNumber , accountRefrence[index].primaryAccountNumber) != 0)
		{
			flag = 0;
		}	
		else { flag = 1; break; }
	}
	if (flag == 0) { return ACCOUNT_NOT_FOUND; }
	else if (flag == 1) 
	{ 
		InDex = index;
		return SERVER_OK;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > dataBase[InDex].balance)
	{
		return LOW_BALANCE;
	}
	else return SERVER_OK;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence[InDex].state == BLOCKED)
	{
		return DECLINED_STOLEN_CARD;
	}
	else return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transactions[T_index].cardHolderData = transData->cardHolderData;
	transactions[T_index].terminalData = transData->terminalData;
	transactions[T_index].transState = transData->transState;
	if (T_index == 0)
	{
		transactions[0].transactionSequenceNumber = 7000;
	}
	else { transactions[T_index].transactionSequenceNumber = transactions[T_index - 1].transactionSequenceNumber + 1; }

	EN_serverError_t isSaved = getTransaction(transactions[T_index].transactionSequenceNumber, transactions);
	if (isSaved == SERVER_OK) { T_index += 1; return SERVER_OK; }
	else return SAVING_FAILED;

}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	int i, flag;
	for (i = 0; i < 1; i++)
	{
		if (transactionSequenceNumber == transData[i].transactionSequenceNumber)
		{
			flag = 1;
			break;
		}
		else flag = 0;
	} 
	if (flag == 0) 
	{
		return TRANSACTION_NOT_FOUND; 
	}
	else
	{
		printf("\n\n>> Card Holder Name:  %s\n", transData[InDex].cardHolderData.cardHolderName);
		printf(">> Card PAN: %s\n", transData[InDex].cardHolderData.primaryAccountNumber);
		printf(">> Transaction Amount: %.2f\n", transData[InDex].terminalData.transAmount);
		printf(">> Updated Balance: %.2f\n", dataBase[InDex].balance);
		printf(">> Transaction Date: %s\n", transData[InDex].terminalData.transactionDate);

		return SERVER_OK;
	}
	
}
