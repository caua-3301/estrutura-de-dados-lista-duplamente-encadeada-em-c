//LISTA QUE SIMULA UMA AGENDA TELEFONICA, ANOTANDO O NOME E NUMERO DE CADA CONTATO
//Atualizações em breve

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Criando o campo que armazenará o nome e o telefone*/
typedef struct{
	char nome [100];
	char telefone [20];
}pessoa;


/*Criando o nod, contendo o registro pessoa e dois ponteiros apontando para o nodo anterior e o próximo*/
typedef struct nodo{
	struct nodo *anterior;
	pessoa contato;
	struct nodo *proximo;
}Nodo;


/*Definindo o inicio da minha lista*/
typedef struct{
	Nodo *inicio;
}Lista;


/*Função que criar a lista, definido um ponteiro para seu inicio*/
Lista *criando_lista(){
	Lista *lista = (Lista *)malloc(sizeof(Lista));
	lista -> inicio = NULL;
	return lista;
}


/*Adicionando novo contado na minha lista, de forma que a mesma fique organizada em ordem alfabetica*/
void adicionar_contato(Lista *lista, char nome[100], char telefone[20]){
	Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
	novo -> anterior = NULL;
	novo -> proximo = NULL;
	strcpy (novo -> contato.nome, nome);
	strcpy (novo -> contato.telefone, telefone);
	Nodo *aux = lista -> inicio;
	if (lista -> inicio == NULL){
		lista -> inicio = novo;
	} 
	else{
		int teste = strcmp (nome, aux -> contato.nome);
		while (aux -> proximo != NULL && teste > 0){
			aux = aux -> proximo;
			teste = strcmp (nome, aux -> contato.nome);
		}
		if (teste > 0){
			aux -> proximo = novo;
			novo -> anterior = aux;
		}
		else if (lista -> inicio == aux){
			novo -> proximo = aux;
			aux -> anterior = novo;
			lista -> inicio = novo;
		}
		else{
			aux -> anterior -> proximo = novo;
			novo -> anterior = aux -> anterior;
			novo -> proximo = aux;
			aux -> anterior = novo;
		}
	}
}


/*Função que retorna um ponteiro apontado para o nodo desejado*/
Nodo * localizar_contato (Lista *lista, char nome[100]){
	Nodo *aux = lista -> inicio;
	int teste = strcmp (nome, aux -> contato.nome);
	while (teste > 0 && aux -> proximo != NULL){
		aux = aux -> proximo;
		teste = strcmp (nome, aux -> contato.nome);
	}
	if(teste == 0){
		return aux;
	}
	return NULL;
}


/*Procedimenro que imprime o telefone de um contato*/
void imprimir_contato (Lista *lista, char nome[100]){
	Nodo *aux = localizar_contato(lista, nome);
	if (aux != NULL){
		printf ("%s", aux -> contato.nome);
	}
	else{
		printf ("Contato nao encontrado, tente novamente\n");
	}
}


/*Contar quantos contatos existem na agenda*/
int contar_contatos (Lista *lista){
	int cont = 0;
	Nodo *aux = lista -> inicio;
	while (aux != NULL){
		cont++;
		aux = aux -> proximo;
	}
	return cont;	
}


/*Atualizando um contato*/
void atualizar_contato (Lista *lista, char nome[100], char novo_telefone[20]){
	Nodo *aux = localizar_contato(lista, nome);
	if (aux != NULL){
		strcpy (aux -> contato.telefone, novo_telefone);
		printf ("Operacao realizada com sucesso!\n");
	}
	else{
		printf ("Numero nao encontrado, tente novamente");
	}
}


/*Procedimeno que remove um contato*/
void excluir_telefone (Lista *lista, char nome[100]){
	Nodo *aux = localizar_contato(lista, nome);
	if (aux != NULL){
		if (aux -> anterior != NULL){
			aux -> anterior -> proximo = aux -> proximo;
		}
		if (aux -> proximo != NULL){
			aux -> proximo -> anterior = aux -> anterior;
		}
		if (lista -> inicio == aux){
			lista -> inicio = aux -> proximo;	
		}
		printf ("Operacao realizada com sucesso\n");
	}
	else{
		printf ("Ocorreu um problema na operacao, tente novamente\n");
	}
}


/*Imprimir todos os contatos, printando o nome e telefone dos contatos*/
void imprimir_tudo (Lista *lista){
	Nodo *aux = lista -> inicio;
	while (aux != NULL){
		char teste [100];
		strcpy (teste, aux -> contato.nome);
		printf ("Nome: %s\n", teste);
		printf ("Telefone: %s\n\n", aux -> contato.telefone);
		aux = aux -> proximo;
	}
}


/*Imprimindo ao contrário*/
void imprimir_decrescente (Lista *lista){
	Nodo *aux = lista -> inicio;
	while (aux -> proximo != NULL){
		aux = aux -> proximo;
	}
	while (aux -> anterior != NULL){
		printf ("Nome: %s\n", aux -> contato.nome);
		printf ("Telefone: %s\n", aux -> contato.telefone);
		aux = aux -> anterior;
	}
}

//  MAIN  //
void main(){
	
	char fazer, nome[100], telefone[20], novo_numero[20];
	int continuar = 1;
	float valor;
	
	//Criando ponteiro para a minha lista
	Lista *lista = criando_lista();
	
	printf ("\t\t\t\t  -----------------------------------------\n");
	printf ("\t\t\t\t             LISTA DE CONTATOS\n");
	printf ("\t\t\t\t  -----------------------------------------\n");
	
	while (continuar == 1){
	
	//Menu que pergunta a operação que o usuário deseja realizar
		printf ("O que deseja fazer: \n\n");
	
		printf ("Adicionar contato: (A)\n");
		printf ("Deletar contato: (D)\n");
		printf ("Editar contato: (E)\n");
		printf ("Ver numero de contatos: (N)\n");
		printf ("Imprimir todos os contatos: (I)\n");
		printf ("Imprimir em ordem reversa: (R)\n");
		scanf ("%c", &fazer);
		fflush (stdin);
	
		switch (fazer){
			case 'a':
			case 'A': 
					printf ("Informe o nome que sera adicionado: \n");
					scanf ("%s", &nome);
					fflush (stdin);
					printf ("Agora informe o numero: \n");
					scanf ("%s", &telefone);
					fflush (stdin);
					adicionar_contato (lista, nome, telefone);
						break;
		
			case 'd':
			case 'D': 
		        	printf ("Informe o nome do contato que sera deletado: \n");
					scanf ("%s", &nome);
					fflush(stdin);
					excluir_telefone (lista, nome);
						break;
		
			case 'e':			
			case 'E':
					printf ("Informe o nome do contato que sera editado: \n");
					scanf ("%s", &nome);
					printf ("Informe o novo numero: \n");
					scanf ("%s", &novo_numero);
					atualizar_contato (lista, nome, novo_numero);
						break;
		
			case 'n':
			case 'N':
					printf ("Voce possui %d contatos\n", contar_contatos(lista));
						break;
		
			case 'r':			
			case 'R':
					imprimir_decrescente (lista);
						break;
		
			case 'i':		
			case 'I':
					imprimir_tudo (lista);
						break;
						
			default: printf ("Operacao invalida\n");
	}
	//Sabendo se o usuário deseja realizar mais alguma alteração
		printf ("Deseja realizar mais alguma operacao: (1) sim (2) nao\n");
		scanf ("%d", &continuar);
		fflush (stdin);
	}
	
	getch ();
}


