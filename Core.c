#include <stdio.h>
#include <stdlib.h>

typedef struct matrx matrx;

struct matrx{ char entrada [10]; char salida [10]; char siguiente [10];};

//gcc core.c -Wall -Werror -Wextra -o main

//FUNCION LEE DATOS/ SI HAY DATOS Y TODO VA BIEN RETORNA AUX > 0,
 //EN CASO CONTRARIO RETORNA 0


int guardar_datos(char *datos, char * entrada, char * salida, char *siguiente)
{
	int i;
	int j;

	i = 0;
	j = 0;

		while( datos[i] != '/')
		{
			entrada[j] = datos[i];
			i++;
			j++;
		}
		entrada[j] = '\0';
		j = 0;
		i = i + 1;
		while( datos[i] != '/')
		{
			salida[j] = datos[i];
			i++;
			j++;
		}
		salida[j] = '\0';
		j = 0;
		i = i + 1;
		while( datos[i] != '\0')
		{
			siguiente[j] = datos[i];
			i++;
			j++;
		}
		siguiente[j] = '\0';
return 0;
}

int leer_dato(FILE *fp, char *salida)
{
char caracter;
int aux;
char *tmp_ptr;

aux = 0;
while((caracter = fgetc(fp)) != '\n' && caracter != EOF)
	{
		if(caracter == '{')
		{
			aux = 1;
			while ((caracter = fgetc(fp)) != '}')
			{
				salida[aux - 1] = caracter;
				aux++;

				if (!(tmp_ptr = realloc(salida, aux + 1)))
					return 0;
				salida = tmp_ptr;
			}
		}
	}
	salida[aux - 1] = '\0';

	return aux;
}

int main(void)
{

//Declaracion de variables.

	FILE *fp;
	//struct matrx{ char entrada; char salida [10]; char siguiente [5];};
	struct n_final{ char final [10];};
	int aux;
	char caracter;
	char *palabra_entrada;
	char *abecedario;
	char *tmp_ptr;
	char *n_estados;
	char *n_e_finales;
	char *datos;
	char *palabra_salida;
	int n;
//Abrimos el fichero

	aux = 1;
	palabra_entrada = malloc(aux * sizeof(char));
	abecedario = malloc(aux * sizeof(char));
	n_estados = malloc(aux * sizeof(char));
	n_e_finales = malloc(aux * sizeof(char));
	datos = malloc(aux * sizeof(char));
	palabra_salida = malloc(aux * sizeof(char));


	fp = fopen ( "configuracion.txt", "r" );
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}

	leer_dato(fp,palabra_entrada);
	printf ("PALABRA \n");
	printf("-%s-\n",palabra_entrada);

	leer_dato(fp,abecedario);
	printf ("ABECEDARIO \n");
	printf("-%s-\n",abecedario);

	leer_dato(fp,n_estados);
	printf ("N_ESTADOS \n");
	printf("-%s-\n",n_estados);

	n = atoi(n_estados);

//Declaramos una Matriz y guardamos los datos en la estructura

	struct matrx matriz[n][n];
// PONER AQUI TU MATRIZ QUITANDO ESTA
// matriz * [n][n];
	for(int i = 0; i < n ; i++)
		{
			for(int j = 0; j < n ;j++)
			{
				leer_dato(fp,datos);
				guardar_datos(datos,matriz[i][j].entrada,matriz[i][j].salida,matriz[i][j].siguiente);
				//AQUI SE PUEDE GUARDAR DIRECTAMENTE LOS VALORES
				// matriz[i][j] = datos;
			}
		}
//FOR PARA PINTAR
	for(int i = 0; i < n ; i++)
		{
			for(int j = 0; j < n ;j++)
			{
				printf("ENTRADA: %s SALIDA: %s SIGUIENTE: %s \n", matriz[i][j].entrada,matriz[i][j].salida,matriz[i][j].siguiente);
			}
		}

//ALGORITMO AUTOMATA
/*
int i;
int j;
int k;

k = 0;
while (palabra_entrada != '\n')
{
	if(palabra_entrada == matriz[i][j].entrada)
	{
		if (!(tmp_ptr = realloc(palabra_salida,strlen(matriz[i][j].salida))))
			return 0;
		palabra_salida = tmp_ptr;
		while (matriz[i][j].salida != '\0')
		{

		}
		i = matriz[i][j].siguiente - '0';
		j = 0;
	}

}


*/
    fclose ( fp );
	return (1);
}
