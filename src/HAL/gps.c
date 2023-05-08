#include "gps.h"
#include "../MCAL/UART_init.h"
#include <stdlib.h>
#include <string.h>

char RMC_LOG_NAME[] = "$GPRMC,";
char RMC_STRING [80];

void gps_init()
{
    UART0_init_fifo(9600);

// recvives an RMS sentence form gps om URAT1
void get_RMC_string()
{
    char recievedChar;
    unsigned char i = 0; unsigned char Counter = 0;
	
    do
	{
		while(UART0_READ_BYTE() != RMC_LOG_NAME[i]);
		i++;
	}while(i <= 6);

	strcpy(RMC_STRING, "");

	do
	{
		recievedChar = UART0_READ_BYTE();
		RMC_STRING[Counter++] = recievedChar;
	}while(recievedChar != '*');
}
geographic_point get_geographic_point()
{
		char lat[30] = "";
    char lon[30] = "";
	  char lat_dir[] = "";
		char lon_dir[] = "";
    char valid[] = "";
		geographic_point p;
		char *token ;

		memset(RMC_STRING,0,80);
		get_RMC_string();

		token = strtok(RMC_STRING, ",");
		token= strtok (NULL,",");
				strcpy(valid,token);
		if (strcmp(valid, "A")==0)
		{
			p.Valid = 1;

		token= strtok (NULL,",");
				strcpy(lat,token);

		token= strtok (NULL,",");
				strcpy(lat_dir,token);
			
		token= strtok (NULL,",");
				strcpy(lon,token);

		token= strtok (NULL,",");
				strcpy(lon_dir,token);

		if (strcmp(lat_dir, "N")==0)
			p.latitude = atof (lat);
		else
			p.latitude = -atof (lat);

		if (strcmp (lon_dir, "E")==0)
			p.longtude = atof (lon);
		else
			p.longtude =-atof (lon);
		}
		
		else
			p.Valid = 0;
		
    return p;
}
