#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

    
    typedef struct data {
        char* nombreAFDTraductor;
        char* cintaEntrada;
        int estados;
        char* *arrayEstados;
        int* estadoFinal;
    } Data;
    
    Data * precargar(void);
    
    int main (void){
        Data *dta = precargar();
        printf("NombreAFDTraductor: %s\n",dta->nombreAFDTraductor);
        printf("CintaEntradaInicial: %s\n\n",dta->cintaEntrada);
        
        char* cintaSalida = "";
        int cur = 0;
        int j;
        
        for (int i = 0; dta->cintaEntrada[i] != '\0';i++){
              
            printf ("-identificamos y traducimos (%c) \n", dta->cintaEntrada[i]);
            
            int estaAlfabeto = 0;
            for(j = 0; j < dta->estados*dta->estados; j++) {
                char asd = dta->arrayEstados[j][0];
                asd = dta->cintaEntrada[i];
                if( dta->cintaEntrada[i] == dta->arrayEstados[j][0] ) { 
                    estaAlfabeto = 1;
                    break;
                };
            }
            if(estaAlfabeto == 0) { 
                cur = 0;
                break;
            }
                      
            for (j = 0; j < dta->estados*(cur+1); j++) {
                if (dta->arrayEstados[j][0] == dta->cintaEntrada[i]){
                    char* aux = malloc(sizeof(char));
                    strcpy(aux,cintaSalida);
                    cintaSalida = strcat(aux, &dta->arrayEstados[j][1]);
                    printf ("\t-cintaSalida = %s\n\n", cintaSalida);
                        
                    break;
                }
                	
            }
            char asd = dta->arrayEstados[(cur+1)*j][1];
            if(dta->arrayEstados[(cur+1)*j][1]!='\0')cur = j;
        }  
        
        if (dta->estadoFinal[cur] == 1){
        	printf ("\n   \t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|");  
            printf ("\n   \t|Se ha reconocido la palabra| la traducción es: %s", cintaSalida);
        	printf ("\n   \t|~~~~~~~~~~~~~~~~~~~~~~~~~~~|");                    
            return 1;
        }else{
            printf ("\n   \t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
            printf ("\n   \t| Palabra no reconocida por el traductor |");
            printf ("\n   \t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
            	  
            return -1;
        }
    }

    Data * precargar(void){
        Data *dta;
        
        char ch1[1024], ch2[1024], ch3[1024];
        int state, tempFinalState, i=0, j=0;
        
        FILE *fp;
        fp = fopen("config.txt","r+");
        if(fp == NULL) {
            printf("\n Error while opening the file: config.txt");
            exit (EXIT_FAILURE);
        }
        
        fscanf(fp, "%s\n%s\n%d\n%s\n", ch1, ch2, &state);
        
        int finalState[state];
        char *arrayEstados[state*state];
        
        fscanf(fp, "%[^\n]\n", ch3);
        char * token = strtok(ch3, " ");
        while( token != NULL ) {
            finalState[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
        
        i = 0;
        fscanf(fp, "%[^\n]\n", ch3);
        token = strtok(ch3, " ");
        while( token != NULL ) {
            arrayEstados[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        
        dta = malloc( sizeof(*dta) + sizeof(finalState) + sizeof(arrayEstados) ); 
        dta->estadoFinal = malloc( sizeof(finalState) ); 
        dta->arrayEstados = malloc( sizeof(arrayEstados) );
        dta->nombreAFDTraductor = ch1; 
        dta->cintaEntrada = ch2; 
        dta->estados = state;
        dta->estadoFinal = finalState;
        dta->arrayEstados = arrayEstados;
       
        fclose(fp);
        return dta;
    }
    