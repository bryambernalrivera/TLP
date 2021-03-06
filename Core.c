#include <stdio.h>
#include <stdlib.h>

typedef struct matrx matrx;

struct matrx{ char *entrada; char *salida ;};

//Funcion para buscar datos
int buscar_char(char *b, char c)
{
	while (*b != '\0')
	{
		if(*b == c)
			return 1;
		b++;
	}
	return 0;
}
//Funcion para guardar datos.
int guardar_datos(char *datos, char * entrada, char * salida)
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
		while( datos[i] != '\0')
		{
			salida[j] = datos[i];
			i++;
			j++;
		}
		salida[j] = '\0';
return 0;
}
//Funcion para leer datos de .txt
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

	FILE *fp;
	struct n_final{ char final [10];};
	int aux;
	char *palabra_entrada;
	char *abecedario;
	char *n_estados;
	char *estados_finales;
	char *n_e_finales;
	char *datos;
	char *nombre;
	char *palabra_salida;
	int n_est;
//Abrimos el fichero

	aux = 2;
	palabra_entrada = malloc(aux * sizeof(char));
	abecedario = malloc(aux * sizeof(char));
	n_estados = malloc(aux * sizeof(char));
	n_e_finales = malloc(aux * sizeof(char));
	datos = malloc(aux * sizeof(char));
	palabra_salida = malloc(aux * sizeof(char));
	estados_finales = malloc(aux * sizeof(char));
	nombre = malloc(aux * sizeof(char));

	fp = fopen ( "configuracionC.txt", "r" );
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}

	leer_dato(fp,nombre);
	leer_dato(fp,n_estados);
	n_est = atoi(n_estados);
	leer_dato(fp,palabra_entrada);
	leer_dato(fp,abecedario);
	leer_dato(fp,estados_finales);

//Declaramos una Matriz y guardamos los datos en la estructura

	struct matrx matriz[n_est][n_est];
//Guardamos datos en la matriz
	for(int i = 0; i < n_est ; i++)
		{
			for(int j = 0; j < n_est ;j++)
			{
				leer_dato(fp,datos);

				matriz[i][j].entrada = malloc(sizeof(datos)* sizeof(char));
				matriz[i][j].salida = malloc(sizeof(datos) * sizeof(char));
				guardar_datos(datos,matriz[i][j].entrada,matriz[i][j].salida);
			}
		}

int k;
int i;
int j;

k = 0;
i = 0;
j = 0;


while (palabra_entrada[k] != '\0')
{
	//printf("i: %i j: %i ",i,j);
	//printf("palabra entrada: %c ", palabra_entrada[k]);
	//printf("palabras posibles %s\n",matriz[i][j].entrada);
	//printf("Buscar %i\n",buscar_char(matriz[i][j].entrada, palabra_entrada[k]));
	if(buscar_char(matriz[i][j].entrada, palabra_entrada[k]))
	{
		printf("%s", matriz[i][j].salida);
		i = j;
		j = 0;
		k++;
	}
	else
	{
		if (!(buscar_char(abecedario,palabra_entrada[k])))
		{
			printf("ERROR\n");
			return 0;
		}

		j++;
	}

}

// NO ESTA IMPLEMENTADO PERO SERIA OTRA MANERA DE FORMA DIRECTA
/*
char f;

while((f = fgetc(fp)) != EOF)
{
	printf("%c",f);
	//printf("palabra entrada: %c ", palabra_entrada[k]);
	//printf("palabras posibles %s\n",matriz[i][j].entrada);
	//printf("Buscar %i\n",buscar_char(matriz[i][j].entrada, palabra_entrada[k]));
	if(buscar_char(matriz[i][j].entrada,f))
	{
		printf("%s", matriz[i][j].salida);
		i = j;
		j = 0;
		//k++;
	}
	else
	{
		if (!(buscar_char(abecedario,f)))
		{
			printf("ERROR\n");
			return 0;
		}

		j++;
	}

}
*/

printf("\n");

if (buscar_char(estados_finales,i + '0'))
	printf("Se ha reconocido la palabra");
else
	printf("No se ha reconocido la palabra");

printf("\n");

    fclose ( fp );
	return (1);
}
