#include <stdio.h>
#define MAX 256
#define MAXK 32

void print_array(int array[],int qtd_max)//imprimir array para ter ideia dos numeros nele
{
	for (int i = 0; i < qtd_max; ++i)
	{
		printf("%d ",array[i]);
	}
	printf("\n");//ultimo item, pula linha
}

void read_array(int array[],int size)
{
	for (int i = 0; i < size; i++)//lê os itens para o vetor
	{
		scanf("%d", &array[i]);
	}
}


void initialize( int S[], int key[], int TamK, int rodada)
{		
	//ROTAÇÃO DA CHAVE
	int rotacao  = (TamK*4) - (rodada/2);
	//inicializar um vetor de 0 a 254 só pares (repetindo no meio)
	int T[256] = {0};
	for (int i = 0; i < MAX; ++i)
	{
		T[i] = key[(i+rotacao) % TamK];
	}
	

	int j = 0;

	for (int i = 0; i < MAX; ++i)
	{
		j = (j + S[i] + T[i]) % 256;
		//printf("antes %d, %d\n", S[i], S[j]);// ------------DEBUG----------------
		int aux = S[i];
		S[i] = S[j];
		S[j] = aux;
		//printf("depois %d, %d\n", S[i], S[j]);// ------------DEBUG---------------
	}
}

//--------------------//MAIN//---------------------------------------------------------------
int main(int argc, char const *argv[])
{
	// primeira preocupação: Criar um programa que lê um vetor de inteiros de n numeros
	// inicializa vetor s1 com 256 só pares, repetindo no meio, e s2 mesmo , só que com impares 
	int S1[256] = {0};
	int S2[256] = {0};

	int Atrib = 0;
		int pivot = 128;
	for (int i = 0; i < 128; ++i)
	{
		S1[i] = Atrib;
		S1[pivot] = Atrib;

		S2[i] = Atrib+1;
		S2[pivot] = Atrib+1;

		Atrib = Atrib+2;
		pivot++;
	}


	int key[MAXK] = {0};

	char op;
	int init = 0;
	int n_rodadas = 0;
	int TamK = 0;

	int S_descart[256] = {0};
	

	while(scanf("%c", &op) != EOF)
	{
		if (op == 'I')
		{
			scanf("%d", &n_rodadas);
			scanf("%d", &TamK);
			read_array(key, TamK);
			init = 1;
		}
		else if (op == 'C' && init == 1)
		{
			int cifrar[32] = {0};
			read_array(cifrar, 32);
			//Rodadas da rede
			for (int i = 0; i < n_rodadas; ++i)
			{
				//Rodadas par ou impar?
				if (i%2 == 0)
				{
					for (int i = 0; i < 256; ++i)
					{
						S_descart[i] = S1[i]; // seta/reseta o vetor descartavel de s PAR
					}
				}
				else
				{
					for (int i = 0; i < 256; ++i)
					{
						S_descart[i] = S2[i]; // seta/reseta o vetor descartavel de s IMPAR
					}
				}
				//
				initialize(S_descart, key, TamK, i);
				//DEBUG----------------------------
				//print_array(S_descart, MAX);
				//
				for (int i = 0; i < 16; ++i)
				{
					cifrar[i] = cifrar[i] ^ (S_descart[cifrar[i+16]]); 
					
					int aux = cifrar[i];
					cifrar[i] = cifrar[i+16];
					cifrar[i+16] = aux;
				}
			}
			//ultima troca:
			for (int i = 0; i < 16; ++i)
			{
				//troca blocos 16
				int aux = cifrar[i];
				cifrar[i] = cifrar[i+16];
				cifrar[i+16] = aux;
			}
			//
			printf("C ");
			print_array(cifrar, MAXK);
		}
		else if (op == 'D' && init == 1)
		{
			int decifrar[32] = {0};
			read_array(decifrar, 32);
			for (int i = n_rodadas-1; i >=0; --i)
			{
				if (i%2 == 0)
				{
					for (int i = 0; i < 256; ++i)
					{
						S_descart[i] = S1[i]; // seta/reseta o vetor descartavel de s PAR
					}
				}
				else
				{
					for (int i = 0; i < 256; ++i)
					{
						S_descart[i] = S2[i]; // seta/reseta o vetor descartavel de s IMPAR
					}
				}

				initialize(S_descart, key, TamK, i);


				for (int i = 15; i >= 0; --i)
				{
					decifrar[i] = decifrar[i] ^ (S_descart[decifrar[i+16]]); //entra no bloco 
					
					//troca
					int aux = decifrar[i];
					decifrar[i] = decifrar[i+16];
					decifrar[i+16] = aux;
				}
			}
			for (int i = 15; i >= 0; --i)
			{
				//troca
				int aux = decifrar[i];
				decifrar[i] = decifrar[i+16];
				decifrar[i+16] = aux;
			}
			printf("C ");
			print_array(decifrar, MAXK);
		}
	}

	return 0;//FIM -------------------------

}