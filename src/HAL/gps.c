#include "gps.h"
#include <string.h>
#include <stdlib.h>

char RMC_LOG_NAME[] = "$GPRMC,";
char RMC_STRING [80];
char FORMATED_STRING [12][20];
char * token;

void gps_init()
{
    UART0_init_fifo(9600);
}

geographic_point get_geographic_point()
{
    char noOfTokenStrings = 0;
    geographic_point p;

    get_RMC_string();

    
	token = strtok(RMC_STRING, ",");
	do
	{
		strcpy(FORMATED_STRING[noOfTokenStrings],token);
		token= strtok (NULL,",");
		noOfTokenStrings++;
	} while (noOfTokenStrings <= 6);
	
	if (strcmp(FORMATED_STRING[1], "A")==0)    //Valid
	{ 
		if (strcmp(FORMATED_STRING[3], "N")==0)
			p.latitude = atof (FORMATED_STRING[2]);
		else
			p.latitude = -atof (FORMATED_STRING[2]);

		if (strcmp (FORMATED_STRING [5], "E")==0)
			p.longtude = atof (FORMATED_STRING[4]);
		else
			p.longtude =-atof (FORMATED_STRING[4]);
	}
    return p;
}

void get_RMC_string()
{   
    char Counter = 0;
	char recievedChar;
	char i = 0;
	do
	{
		while(get_char() != RMC_LOG_NAME[i]);
		i++;
	}while(i <= 6);

	strcpy(RMC_STRING, "");

	do
	{
		recievedChar = get_char();
		RMC_STRING[Counter++] = recievedChar;
	}while(recievedChar != '*');
}
