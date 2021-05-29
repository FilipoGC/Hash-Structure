#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

//valor inicial de M
#define INIT_M 19

struct hash{
	int M; //tamanho maximo da estrutura
	int N; //contagem de valores na estrutura
	int *values;
} typedef hash_t;

/*
Funcao para inserir com probing quadratico.
*/
int insertQaudratica(hash_t *hash, int value){//funcao para inserir com tratamento de colisao com probinf quadratico

	int index; 
	int i = 0;

	index = value % hash->M; 

	if (hash->values[index] == INT_MIN){

		hash->values[index] = value;
		hash->N++;


	}else{

		do{
			index = (value*value + i++) % hash->M;/*fazendo value * value ele faz com que o proximo indice seja o valor(value) inserido ao qudrado*/

		}while(hash->values[index] != INT_MIN);

		hash->values[index] = value;
		hash->N++;/*outro N++ pois tinha só no if e nao tinha um no else, caso tivesse algo na posicao ele ainda pudesse seguir a contagem de valores na estrutura*/
	}
	if ((float)hash->N/hash->M > 0.5){
		hash->values = (int*) realloc (hash->values, hash->M * 2 * sizeof(int));
		hash->M = hash->M * 2;
	return 1;
	}

}

/*
Funcao para inserir com linear probing.
*/
int insert(hash_t *hash, int value){

	int index; 
	int i = 0;

	index = value % hash->M; 

	if (hash->values[index] == INT_MIN){

		hash->values[index] = value;
		hash->N++;


	}else{

		do{
			index = (value + i++) % hash->M;

		}while(hash->values[index] != INT_MIN);

		hash->values[index] = value;
		hash->N++;
	}
	if ((float)hash->N/hash->M > 0.5){/*forcando a divisao ser float*/
		hash->values = (int*) realloc (hash->values, hash->M * 2 * sizeof(int));/*mecanismo de realocacao de memoria para quando o numero de valores preenchessem mais de 50% da estrutura*/
		hash->M = hash->M * 2;/*atualizacao do tamanho maximo da estrutura*/
	return 1;
	}

}


/*
Funcao para inicializar estrutura
*/

hash_t* init(){

	int i;
	hash_t* hash = (hash_t*) malloc (sizeof(hash_t));
	
	if (hash != NULL){
	
		hash->M = INIT_M;
		hash->N = 0;
		hash->values = (int*) malloc(hash->M * sizeof(int));
		
		for(i = 0; i < hash->M; i++) hash->values[i] = INT_MIN;

		if (hash->values == NULL) return NULL;
		return hash;
	
	}else{
		return NULL;
	} 

}

/*
Funcao para desalocar. 
*/
int dealloc(hash_t* hash){
	free(hash->values);
	free(hash);
	return 1;
}

/*
Funcao para buscar. 
*/

int search(hash_t* hash, int value){
	int index;
	int i = 0;
	do{
		index = (value + i++) % hash->M;/*fazendo com que o resultado do valor buscado com resto da divisão retorne a posicao do mesmo*/
		
	}while(hash->values[index] != value && i <= hash->M);/*caso o conteudo da posicao do vetor for igual ao valor buscado ira parar, e se o i passar do tamanho maximo(caso o valor informado nao esteja na estrutura)*/
	if (hash->values[index] == value) return index;
	else return -1;
	
}

/*
Funcao para remover. 
*/
int delete(hash_t* hash, int value){
	int index = search(hash, value);/*utilizando a funcao de busca para achar a posicao do valor informado e remove-lo*/
	if (index == -1) return -1;/*caso o valor pedido para remover nao esteja na estrutura a funcao search irá retorne -1*/
	else {
		hash->values[index] = INT_MIN;/*fazendo com que o conteudo da posicao seja zerado para INT_MIN*/
		hash->N--;/*diminuindo a contagem de elemtos na estrutura*/
	}
	return 1;
}

void print(hash_t* hash){

	int i;
	for(i = 0; i < hash->M; i++){
		if(hash->values[i] != INT_MIN) printf("%d\n", hash->values[i]);
	}

}

int main(){

	int i;
	hash_t* minhaHash = init();

	for(i = 0; i < 10; i++) insert(minhaHash, i);
	print(minhaHash); 

	return 0;

}
