#include <stdio.h>

//gcc main.c ft* -Wall -Werror -Wextra -o main
int main(void)
{

	int estados = 2;
	char *matriz [estados][estados];
	char *palabraEntrada;
	palabraEntrada= "aaaabbb";
	char *palabraSalida;

	palabraSalida = NULL;
	//char *palabraSalida;
	char *infoMatriz;
	//int F = 0;
	// meter valores con for
	matriz[0][0] = "b/1/0";
	matriz[0][1] = "a/0/1";
	matriz[1][0] = "b/1/1";
	matriz[1][1] = "a/0/0";


		for(int i = 0; i < estados ; i++)
			{
				for (int j = 0; j < estados; j++)
				{
					infoMatriz = matriz[i][j];

						printf("- %s - \n", infoMatriz);
						if(*infoMatriz == *palabraEntrada)
						{
							infoMatriz++;
							infoMatriz++;
							while(*infoMatriz != '/')
							{
								//*palabraSalida = *infoMatriz;
								//printf("- %c -", palabraEntrada);

							}
							while(*infoMatriz != '\0')
							{
								i = *infoMatriz - '0';
								j = 0;
								infoMatriz++;
							}
							palabraEntrada++;
						}
				}
			}
	//printf("%s", palabraSalida);
    return (1);
}
