#include <stdio.h>
#include <stdlib.h>
#include<math.h>

void imprime(double **m, int dim)
{	int i, j;
	
	for(i=0;i<dim;i++)
	{	for(j=0;j<dim+1;j++)
			printf("%.5lf\t",m[i][j]);
	  
		puts("");
	}
	printf("\n------------------\n");
	
}

void troca(double *a, double *b, int dim)
{	double *aux;
	int i;
	
	aux = (double*)malloc((dim+1)*sizeof(double));
	
	for(i=0;i<=dim;i++)
	{	aux[i] = a[i];
		a[i] = b[i];
		b[i] = aux[i];
	}
}

double **triang_sup(double **M, int dim)
{
 	int i, j, k, h, p;
 	double aux, t;
 	
 	for(k=0;k<dim;k++) // função que faz triangular superior
 	{	for(h=k;h<dim;h++)
 			if(M[k][k]<M[h][k])
				p = h;
 		
 		troca(M[k],M[p],dim);
 		puts("Matriz trocada");
 		imprime(M,dim);
 		
 		for(i=k+1;i<dim;i++)
 		{	
 			aux = (M[i][k]/M[k][k]);
 
 			for(j=k;j<=dim;j++)
 				M[i][j] = M[i][j] - aux*M[k][j];
 		}
 		
 		printf("\nPasso %d\n", k+1);
 		imprime(M,dim);	
 	}
		
	return M;
}

double **ler(char *arquivo, int *tam)
{	double **R, a, l;
	int i, j, dim;
	FILE *p;
	
	fflush(stdin);
	
	if(!(p = fopen(arquivo, "r")))
		return NULL;
	
	i = fscanf(p,"%d",&dim);

	R = malloc(dim*sizeof(double));

	for(i=0;i<dim;i++)
		R[i] = (double *)malloc((dim+1)*sizeof(double));
	
	for(i=0;i<dim;i++)
	{	for(j=0;j<dim+1;j++)
		{	l = fscanf(p,"%lf",&a);
			R[i][j] = a;
		}
	}	
	*tam = dim;
	
	fclose(p);
	
	return R;
}

void substituicao_r(double **M, double *raizes, int dim)
{	int i, j;
	double b[dim], soma[dim], aux;
	
	for(i=dim-1;i>=0;i--)
	{	soma[i] = 0;
	
		for(j=i;j<=dim;j++)
			soma[i] = soma[i] + M[i][j-1]*raizes[j-1];
		
		aux = M[i][dim];
		b[i] = aux - soma[i];
		raizes[i] = b[i]/M[i][i];
	}
}

int main(int argc, char **argv)
{
	double **M, **T, **Modulo, *raizes;
	int i, j, a, dim;
	FILE *leitura;
	char **nome;
	
	for(i=0;i<dim;i++)
		M[i] = malloc((dim)*sizeof(int));
	
	M = ler(argv[1],&dim);
	imprime(M,dim);
	
	raizes = (double*)malloc(dim*sizeof(double));
	*raizes = 0;
	
	M = triang_sup(M,dim);
	printf("\nMatriz escalonada:\n");
	imprime(M,dim);

	substituicao_r(M, raizes, dim);	
	
	for(i=0;i<dim;i++)
		printf("\nX%d = %5.5lf\n", i, raizes[i]);
	
	return 0;
}
