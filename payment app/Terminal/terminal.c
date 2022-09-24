#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("\nYour Transaction Date (DD/MM/YYYY) :  ");
	fgets(termData->transactionDate, sizeof(termData->transactionDate), stdin);  //  wrong format will return WRONG_DATE error not done
	if (strlen(termData->transactionDate) != 10)
	{
		return WRONG_DATE; 
	}
	else { return TERMINAL_OK; }
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	uint32_t CMM = 0, CYY = 0  , TMM=0, TYYYY=0;
	sscanf_s(cardData->cardExpirationDate, "%d %*c %d ", &CMM, &CYY);

	sscanf_s(termData->transactionDate, "%*d %*c %d %*c %d",  &TMM, &TYYYY);
	if ((CMM < TMM && CYY < (TYYYY - 2000)) || (!(CMM < TMM) && CYY < (TYYYY - 2000)))
	{ 
		return EXPIRED_CARD; 
	}
	else return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("\nTransaction Amount: ");
	scanf_s("%f", &termData->transAmount );
	if (termData->transAmount <= 0) { return INVALID_AMOUNT; }
	else return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Set Max to :  ");

	scanf_s("%f", &termData->maxTransAmount);

	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{	
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else return TERMINAL_OK;
}

