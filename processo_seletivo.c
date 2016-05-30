#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
/* Programa em C, que acessa um arquivo chamado turma.txt, copia os dados desse arquivo: matricula, av1, av2, av3.
   Depois compara as notas, e faz a média com as duas maiores notas. 
   Cria um novo arquivo binário chamado final.fab, com os dados do arquivo turma.txt, e printa na tela o conteúdo.
   Só que para ler esse arquivo final.fab, só através deste programa.
*/
struct aluno
{
	int matri;
	float av1, av2, av3, media;
};

typedef struct aluno regaluno;

int main ()
{
	regaluno * turma;
	regaluno * turma_final;
	regaluno aluno1;
    int total_linhas=0, i=0, cod, cont=0;
	char var_aux;
	float n1, n2, n3;
	FILE *arq_turma;
	arq_turma = fopen ("turma.txt", "r");
	
	if (arq_turma == NULL)
	{
		printf ("\nO arquivo TURMA.txt não pode ser aberto!!\n");
		printf ("\nOcorreu um Erro Grave! Use alguma tecla para finalizar.\n");
		getch ();
	}
	
	else
	{
		var_aux = fscanf (arq_turma, "%d\t%f\t%f\t%f", &cod, &n1, &n2, &n3);
		while (var_aux != EOF)
		{
			total_linhas = total_linhas + 1;
			var_aux = fscanf (arq_turma, "%d\t%f\t%f\t%f", &cod, &n1, &n2, &n3);
		}
	
		rewind(arq_turma);
	    turma = (regaluno*) malloc (total_linhas * sizeof(regaluno));
		var_aux = fscanf (arq_turma, "%d\t%f\t%f\t%f", &turma[i].matri, &turma[i].av1, &turma[i].av2, &turma[i].av3);
		while (var_aux != EOF)
    	{
        	if ((turma[i].av1 < turma[i].av2) && (turma[i].av1 < turma[i].av3))
        	{
            	turma[i].media = (turma[i].av2 + turma[i].av3)/2;
        	}
    
        	else if ((turma[i].av2 < turma[i].av3) && (turma[i].av2 < turma[i].av1))
        	{
            	turma[i].media = (turma[i].av1 + turma[i].av3)/2;
        	}
    
            else if ((turma[i].av3 < turma[i].av1) && (turma[i].av3 < turma[i].av2))
            {
                turma[i].media = (turma[i].av1 + turma[i].av2)/2;
            }
                        
            i++;
			var_aux = fscanf (arq_turma, "%d\t%f\t%f\t%f", &turma[i].matri, &turma[i].av1, &turma[i].av2, &turma[i].av3);
        }
    }
    fclose (arq_turma);
    
    FILE *arq_final;
    arq_final = fopen ("final.fab", "wb");
    
   	if (arq_turma == NULL)
	{
		printf ("\nO arquivo TURMA.fab não pode ser aberto!!\n");
		printf ("\nOcorreu um Erro Grave! Use alguma tecla para finalizar.\n");
		getch ();
	}
	
	else
	{
		fwrite(turma,sizeof(regaluno),total_linhas,arq_turma);		
	}
	fclose (arq_final);
    		
	//FILE *arq_final;
	
	arq_final = fopen ("final.fab","rb");
	
	if (arq_final == NULL)
	{
        printf ("\nO arquivo FINAL.fab não pode ser aberto!!\n");
        printf ("\nOcorreu um Erro Grave! Use alguma tecla para finalizar.\n");
        getch ();
    }
 
    else
    {
        fread (&aluno1,sizeof(regaluno),1, arq_final);
        while(!feof(arq_final))
        {
        	 cont = cont +1;
        	 fread (&aluno1,sizeof(regaluno),1, arq_final);
		}
		
        turma_final = (regaluno*) malloc (cont * sizeof(regaluno));
       
        rewind(arq_final);
        i=0;
        fread (&aluno1,sizeof(regaluno),1, arq_final);
        while(!feof(arq_final))
        {
     		 turma_final[i]=aluno1;
        	 i++;
        	 fread (&aluno1,sizeof(regaluno),1, arq_final);
		}
       
        for(i=0;i<cont; i++)
        {
        	printf("\n\nA Matricula: %d\tAv1: %.2f\tAv2: %.2f\tAv3: %.2f\tMedia: %.2f\n\n", turma_final[i].matri, turma_final[i].av1, turma_final[i].av2, turma_final[i].av3, turma_final[i].media);
		}
       
    }
    fclose (arq_final);
    getch ();
	return 0;
	
}
    	
	