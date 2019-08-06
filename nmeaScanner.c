#include "nmeaScanner.h"
char getCurrentChar(void)
{
	currentChar = le_USARTcarac();
	return currentChar;
}
void appendSpelling(char a)
{
	currentSpelling[cSpelling++] = a;
	currentSpelling[cSpelling] = '\0';
}
void flushSpelling(void)
{
	cSpelling = 0;
	currentSpelling[cSpelling]='\0';
}
char* scanNmea(char* mensageCode)//$GPRMC, $GPGGA, $GPGSA, $GPGLL
{
	flushSpelling();
	while(1)
	{
		getCurrentChar();
		if(currentChar=='$')
		{
			int x;
			appendSpelling(currentChar);
			for(x=0;x<5;x++)
			appendSpelling(le_USARTcarac());
			
			if(!strcmp(currentSpelling,mensageCode))
			{
				do
				{
					getCurrentChar();
					appendSpelling(currentChar);
				}while(currentChar!='\n');
				strcpy(mensage,currentSpelling);
				flushSpelling();
				
				return mensage;

			}
			else
			{
				flushSpelling();
				
			}
		}
		
	}
	return NULL;
}
