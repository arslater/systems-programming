#include "data.h"
#include "process.h"

// TODO: Call the functions from within these if statemetns
int instructionType(char *line)
{
	int ITYPE = 0; 	// 0 MEANS ITS AN ARITHMETIC/whatever 

	printf("No problem here '%s'\n",line);
	if( (strstr(line,"show")) != NULL)
	{
//		printf("SHOW!!\n");
		ITYPE = 1;
		show(line);
		// TODO: MAKE EACH INSTRUCTION TYPE CORRESPOND TO A BINARY MASK!!!
	}
	else if ((strstr(line,"print")) != NULL)
	{
//		printf("PRINT!!\n");
		ITYPE  = 2;
	}
	else if ((strstr(line,"halt")) != NULL)
	{
//		printf("HALT\n");
		ITYPE =3;
	}
	else if((strstr(line,"pop")) != NULL)
	{
//		printf("POP!\n");
		ITYPE = 4;
	}

	return ITYPE;
}

void show(char *string)
{
	// Just want to print everything after 'show '
	char *showString = (char *)malloc(sizeof(char)*strlen(string)-5);
	int i =0;

	while(string[i] != ' ')
		i++;

	showString = &(string[i+1]); // making a new array after the space after show
	printf("%s\n",showString);
}

