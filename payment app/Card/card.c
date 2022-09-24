#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("\nYour Name as Written On Your Card: ");
	fgets(cardData->cardHolderName, 24, stdin);
	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
	{
		return WRONG_NAME;
	}
	else return Card_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("\nYour Card Expiry Date (MM/YY) :  ");
	uint32_t MM = 0, YY = 0;
	fgets(cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate), stdin);
	sscanf_s(cardData->cardExpirationDate, "%u %*c %u", &MM, &YY);
	if (strlen(cardData->cardExpirationDate) != 5 ) 
	{ 
		return WRONG_EXP_DATE; 
	}
	else if (MM > 12 || YY < 22) 
	{ 
		return WRONG_EXP_DATE;
	}
	else  return Card_OK; 
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	long long unsigned int len;
	printf("\nYour Primary Account Number:  ");
	fgets(cardData->primaryAccountNumber, 19, stdin);
	len = strlen(cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber[len - 1] == '\n') {
		len--;
		cardData->primaryAccountNumber[len] = '\0';
	}
	if (len < 16 || len > 19)
	{
		return WRONG_PAN;
	}
	else return Card_OK;
}