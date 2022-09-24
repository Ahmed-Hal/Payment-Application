#include "app.h"

void appStart(void)
{

	ST_transaction_t client = { {0} };

	EN_terminalError_t max = INVALID_MAX_AMOUNT;
	while (max == INVALID_MAX_AMOUNT)
	{
		max = setMaxAmount(&client.terminalData);					// set max trasaction amount
	}

	EN_cardError_t name = WRONG_NAME;

	while (name == WRONG_NAME)
	{

		name = getCardHolderName(&client.cardHolderData);			// get card holder name 

		if (name == Card_OK) 
		{
			break;
		}
	}


	EN_cardError_t pan = WRONG_PAN;
	while (pan == WRONG_PAN)
	{	
		pan = getCardPAN(&client.cardHolderData);					// get card personal account number 

		if (pan == Card_OK) 
		{ 
		break; 
		}
	}

	EN_cardError_t exDate = WRONG_EXP_DATE;									//GET EXPIRY DATE
	while (exDate == WRONG_EXP_DATE) 
	{
	exDate = getCardExpiryDate(&client.cardHolderData);
	}


	EN_terminalError_t Tdate = WRONG_DATE;									//GET TRANSACTION DATE 
	while (Tdate == WRONG_DATE)
	{
	Tdate = getTransactionDate(&client.terminalData);
	}
	
	EN_terminalError_t isCardEx = isCardExpired(&client.cardHolderData, &client.terminalData);
	if (isCardEx == EXPIRED_CARD) 
	{
		printf("\nDECLINED Expired Card"); 
		exit(0);
	}																		 //CHICK CARD EXPIRATION DATE
	else if (isCardEx == TERMINAL_OK) 
	{
	}


	EN_terminalError_t transAmount = INVALID_AMOUNT;
	while (transAmount == INVALID_AMOUNT)
	{
		transAmount = getTransactionAmount(&client.terminalData);	// Transaction Amount
	}


	if (isBelowMaxAmount(&client.terminalData) == EXCEED_MAX_AMOUNT)
	{
		printf("Declined Amount Exeeding limit");						// chick if amount is below max
		exit(0);
	}
	
	EN_transState_t transState = recieveTransactionData(&client);	
	if (transState == ACCOUNT_NOT_FOUND)
	{
		printf("Declined Account Not Found\n");
	}
	else if (transState == DECLINED_INSUFFECIENT_FUND)
	{
		printf("Decliend Insuffecient Funds");
	}
	else if (transState == DECLINED_STOLEN_CARD)
	{
		printf("Declined Stolen Card");
	}
	else if (transState == INTERNAL_SERVER_ERROR)
	{
		printf("Internal Server Erorr!! \nTransaction NOT Saved..");
	}
	else if (transState == APPROVED)
	{
		printf("\n\n<<APPROVED>> \nTRANSACTION SAVED\n\n");

	}


}

