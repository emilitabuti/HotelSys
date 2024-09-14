//Trabalho do hotel - 26/06/23
//Ana Clara Oliveira Silva, Caroline Guimarães Campos, Emili Vieira Tabuti, Isabela Groke Gomes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define TAMANHO_MAX 100 //número max de caracteres 
#define TAM_ANDAR 20 //quantidade de linhas (andares)
#define TAM_APART 14 //quantidade de colunas (apartamentos)
#define TAM_HOTEL (TAM_ANDAR * TAM_APART) //tamanho total do hotel 

//declarações das funções utilizadas
struct strcadastro //cadastro das informações dos hóspedes 
{
    char cpf[12];
    char nome[TAMANHO_MAX];
    char endereco[TAMANHO_MAX];
    char telefone[12];
    char email[TAMANHO_MAX];
};

void CriarMapa (char Hotel [TAM_ANDAR] [TAM_APART]); 
void MostrarMapa (char Hotel [TAM_ANDAR] [TAM_APART]);
int Reservar (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], struct strcadastro hospede);
int Checkin (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], struct strcadastro hospede);
int VerificarExistencia (int an, int ap);
void Cadastrar(struct strcadastro *cadastro);
int CheckinCPF (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], char cpf[12]);
int CheckoutCPF (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], char cpf[12]);
int CancelarReservaCPF (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], char cpf[12]);
void InformacaoHospede (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART]);
void ExibirCadastro (char Hotel [TAM_ANDAR][TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], int an, int ap);
void FuncaoTaxa (char Hotel[TAM_ANDAR][TAM_APART]);
void LimpaEntrada (void); 

main()
{
	int menu; 
	char Hotel[TAM_ANDAR][TAM_APART]; 
	struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART];
	int andar, apart, reserva; 
	int an_mud, ap_mud;	// coordenadas para mudanças fornecidas pelo usuário
	char nome;
	char cpf[12];
	struct strcadastro hospede;
	char cadastro;
	CriarMapa(Hotel); //inicializa o mapa
	
		
	while(1) //Começa o loop
	{
		//Opções do menu
		printf("\n\nOla! Escolha uma opcao do menu: \n"); 
		printf("\nMENU DE OPCOES: \n");
		printf("1. Reserva de apartamento \n");
		printf("2. Check-In de hospede \n");
		printf("3. Check-Out de hospede \n");
		printf("4. Cancelar uma reserva \n");
		printf("5. Mapa de ocupacao e reservas do hotel \n");
		printf("6. Informacoes do quarto \n");
		printf("7. Informacoes do hospede\n");
		printf("8. Taxas de ocupacao e reservas do hotel \n");
		printf("9. Sair do programa \n");
		scanf("%d", &menu);
		LimpaEntrada (); //limpa o scanf 
		system ("cls"); //limpa a tela 
		
		switch (menu)
		{
			
			//Se a opção 1 for escolhida 
			case 1:	
			
				printf("\nOpcao escolhida: 1. Reserva de apartamento \n");
				printf ("\n\n");
				Cadastrar(&hospede); //chama a função cadastrar hóspede 
			
				MostrarMapa (Hotel); //mostra o mapa
				
				if (Reservar (Hotel, tab_hotel, hospede) == 1) //reserva aquele apartamento e andar
				{
					MostrarMapa (Hotel); //mostra o mapa com a reserva feita
				}
				break; 
		
			//Se a opção 2 for escolhida
			case 2:
				printf("\nOpcao escolhida: 2. Check-In de hospede \n");
				do
				{
					printf ("\nVoce ja fez reserva? \n (1) - sim \n (2) - nao \n");
					scanf ("%d", &reserva);
					LimpaEntrada ();
				
					if (reserva == 1) //se ja tem reserva
					{
						printf("Forneca o CPF: ");
						gets(cpf); 
						
						if (CheckinCPF (Hotel, tab_hotel, cpf) == 1) //ocupa o apartamento
						{
							MostrarMapa (Hotel); //mostra o mapa com a reserva feita
						}
					}
					
					else if (reserva == 2) //se nao tiver reserva
					{	
						Cadastrar(&hospede); 
						if (Checkin (Hotel, tab_hotel, hospede) == 1); //ocupa o apartamento
						{
							MostrarMapa (Hotel); //mostra o mapa com check-in feito
						}
					}
					else //qualquer outro caracter inserido 
						printf("\nOpcao invalida");
				}
				while (reserva != 1 && reserva != 2); //sai do loop quando for inserido algo sem ser 1 e 2 
				
				break; 
			
			//Se a opção 3 for escolhida
			case 3:
				
				printf("\nOpcao escolhida: 3. Check-Out de hospede \n");
				
				printf("Forneca o CPF: ");
				gets(cpf); 
					if (CheckoutCPF (Hotel, tab_hotel, cpf) == 1) //desocupa o apartamento
					{
						MostrarMapa (Hotel); //mostra o mapa com o quarto desocupado
					}
			
			break; 
			
			//Se a opção 4 for escolhida
			case 4:
				
				printf("\nOpcao escolhida: 4. Cancelar uma reserva \n");
				
				printf("Forneca o CPF: ");
				gets(cpf); 
					if (CancelarReservaCPF (Hotel, tab_hotel, cpf) == 1) //desocupa o apartamento
					{
						MostrarMapa (Hotel); //mostra o mapa com a reserva cancelada
					}
			
				break; 
		
			//Se a opção 5 for escolhida
			case 5:
				
				printf("\nOpcao escolhida: 5. Mapa de ocupacao e reservas do hotel \n");
				MostrarMapa (Hotel); //mostra o mapa atualizado
				
				break; 
		
			//Se a opção 6 for escolhida
			case 6:
				
				printf("\nOpcao escolhida: 6. Informacoes do quarto \n");
 				ExibirCadastro(Hotel, tab_hotel, an_mud, ap_mud); //mostra os dados do quarto escolhido
 				
				break; 
			
			//Se a opção 7 for escolhida	
			case 7:
				
				printf("\nOpcao escolhida: 7. Informacoes do hospede \n");
				InformacaoHospede (Hotel, tab_hotel); //mostra as informações do hóspede 
				
				break; 
			
			//Se a opção 8 for escolhida
			case 8:
				
				printf("\nOpcao escolhida: 8. Taxas de ocupacao e reservas do hotel \n");
				FuncaoTaxa (Hotel); // apresenta as taxas de ocupação e reserva do hotel
				
				break; //sai do case
			
			//Se a opção 8 for escolhida	
			case 9:
				
				printf("\nOpcao escolhida: 9. Sair do programa \n");
				printf("\n Programa Finalizado \n");
			
				return 0; // finaliza o programa
			}
		}
	} //sai do loop
	
void CriarMapa(char Hotel [TAM_ANDAR] [TAM_APART]) //inicializa o mapa com pontos
{
	int i, j;		
		
	//preenche o mapa com '.'
	for (i = 0; i <= TAM_ANDAR - 1; i++) 
		for (j = 0; j <= TAM_APART - 1; j++) 
				Hotel[i][j] = '.'; //atribui um ponto à coordenada 	
}

void MostrarMapa (char Hotel [TAM_ANDAR] [TAM_APART]) //mostra o mapa
{
	int i, j;
	
	printf ("\nQuartos->");
	
	// mostra os nº dos apartamentos
	for (j = 1; j <= TAM_APART; j++)
		printf ("\t%d", j);
		
	// mostra os andares dos apartamentos.
	for (i = TAM_ANDAR-1; i >= 0; i--)
	{
		printf ("\nAndar %d ", i+1);
		
		for (j = 0; j <= TAM_APART-1; j++)
			printf ("\t%c", Hotel[i][j]);
	}
}

int Reservar (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], struct strcadastro hospede) //faz a reserva
{
int an, ap;	

	printf("\n\nForneca o numero do andar do quarto : \n");
	scanf("%d", &an);
	printf("Forneca o numero do quarto: \n");
	scanf("%d", &ap);	
	
	if (VerificarExistencia (an, ap) == 1) //chama a função que verifica se existe aquele apartamento e quarto inserido 
	{	
		if (Hotel[an - 1][ap - 1] == '.') // faz a troca
		{
			Hotel[an - 1][ap - 1] = 'R'; //reserva o quarto e coloca 'R' no mapa 
			tab_hotel[an-1][ap-1] = hospede;
			printf("\nReserva feita com sucesso.\n");
			return 1;
		}
		else if (Hotel[an - 1][ap - 1] == 'R') //verifica se o quarto já havia sido reservado
		{
			printf("\nQuarto ja reservado anteriormente");
		}
		else //quarto já ocupado
		{
			printf("\nQuarto ja ocupado");
		}
	}
	return 0;
}

int Checkin (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], struct strcadastro hospede) //faz o check-in sem reserva
{
int an, ap;

	printf("\n\nForneca o numero do andar do quarto : \n");
	scanf("%d", &an);
	printf("Forneca o numero do quarto: \n");
	scanf("%d", &ap);
		
	if (VerificarExistencia (an, ap) == 1) //chama a função que verifica se existe aquele apartamento e quarto inserido 
	{
		if (Hotel[an - 1][ap - 1] == '.') // faz a troca
		{
			Hotel[an - 1][ap - 1] = 'O'; //ocupa o quarto e coloca 'O' no mapa
			tab_hotel[an-1][ap-1] = hospede;
			printf("\nCheck-In feito com sucesso.\n");
			return 1;
		}
		else if (Hotel[an - 1][ap - 1] == 'R') //Se já estiver reservado
		{
			printf("\nQuarto ja reservado anteriormente.\n");
		}
		else //Se já estiver ocupado 
		{
			printf("\nQuarto ja ocupado.\n");
		}
	}
	return 0;
}

int VerificarExistencia ( int an, int ap) // verifica se o quarto existe
{
	if((an > TAM_ANDAR || an < 1) && (ap > TAM_APART || ap < 1)) //se o andar for maior que 20 ou menor que 1 
	{
		printf("\nAndar invalido e Quarto invalido\n");
		return 0;
	}
	else if ((an <= TAM_ANDAR && an >= 1) && (ap > TAM_APART || ap < 1)) //se o apartamento for maior que 14 ou menor que 1 
	{
		printf("\nQuarto invalido\n");
		return 0;
	}
	else if((an > TAM_ANDAR || an < 1) && (ap <= TAM_APART && ap >= 1)) //se o andar for maior que 20 ou menor que 1 
	{
		printf("\nAndar invalido\n");
		return 0;
	}
	return 1;		
}

void Cadastrar(struct strcadastro *cadastro) // cadastra os hospedes
{
	printf(" Nome: ");
	gets(cadastro->nome); //armazena a string inserida em nome
    printf ("O nome fornecido foi: %s \n ", cadastro->nome);
    
    printf("CPF: ");
    gets(cadastro->cpf); //armazena a string inserida em cpf
    printf ("O CPF fornecido foi: %s \n ", cadastro->cpf);

    printf("Endereco: ");
    gets(cadastro->endereco); //armazena a string inserida em endereço
    printf ("O endereco fornecido foi: %s \n ", cadastro->endereco);

    printf("Telefone: ");
    gets(cadastro->telefone); //armazena a string inserida em telefone 
    printf ("O telefone fornecido foi: %s \n ", cadastro->telefone);

    printf("E-mail: ");
    gets(cadastro->email); //armazena a string inserida em email
    printf ("O e-mail fornecido foi: %s \n ", cadastro->email);
}

void ExibirCadastro(char Hotel [TAM_ANDAR][TAM_APART],  struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], int an, int ap) // mostra o cadastro do hospede
{
	printf ("\n\n Forneca o numero do andar: \n");
	scanf ("%d", &an);
	LimpaEntrada();
	printf ("Forneca o numero do quarto: \n");
	scanf("%d", &ap);
	LimpaEntrada();
	
		if (Hotel[an - 1][ap - 1] == 'R') //se estiver reservado
		{
			printf ("\n\nO quarto se encontra reservado.");
			printf("\n--- Dados do Cadastro ---\n"); //mostra os dados armazenados 
   		 	printf("Nome: %s\n", tab_hotel[an-1][ap-1].nome);
    		printf("CPF: %s\n", tab_hotel[an-1][ap-1].cpf);
	    	printf("Endereco: %s\n", tab_hotel[an-1][ap-1].endereco);
			printf("Telefone: %s\n", tab_hotel[an-1][ap-1].telefone);
    		printf("E-mail: %s\n", tab_hotel[an-1][ap-1].email);
		}
		else if (Hotel [an-1][ap-1] == 'O') //se estiver ocupado 
		{
			printf ("\n\nO quarto se encontra ocupado.");
			printf("\n--- Dados do Cadastro ---\n"); //mostra os dados armazenados 
   		 	printf("Nome: %s\n", tab_hotel[an-1][ap-1].nome);
    		printf("CPF: %s\n", tab_hotel[an-1][ap-1].cpf);
	    	printf("Endereco: %s\n", tab_hotel[an-1][ap-1].endereco);
			printf("Telefone: %s\n", tab_hotel[an-1][ap-1].telefone);
    		printf("E-mail: %s\n", tab_hotel[an-1][ap-1].email);
		}
		else //se não estiver nem ocupado nem reservado significa que está vazio
			printf("O quarto esta vazio");
}

void InformacaoHospede (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART]) //armazena as informações dos hóspedes de acordo com o cpf 
{
int an, ap, indice=0, option, andar;
int andares[TAM_HOTEL];
int apartamentos[TAM_HOTEL];
char cpf[12];

	printf("Forneca o cpf: ");
	gets(cpf);
	
	//encontra as reservas comparando o CPF digitado e o cadastrado
	for (an = 1; an <= TAM_ANDAR - 1; an++) 
		for (ap = 1; ap <= TAM_APART - 1; ap++) 
			if (Hotel[an-1][ap-1] == 'R') 
				if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
				{
					andares[indice]=an;
					apartamentos[indice]=ap;
					indice++;
				}
	// se indice > 0, ao menos uma reserva existe
	if (indice > 0) 
	{
		if(indice == 1) // só uma existe
		{
			for (an = 1; an <= TAM_ANDAR - 1; an++)
				for (ap = 1; ap <= TAM_APART - 1; ap++)
					if (Hotel[an-1][ap-1] == 'R')
						if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
						{
								printf ("\n\nO quarto:\nAndar:%d e Apartamento:%d esta reservado.", an, ap);
								printf("\n--- Dados do Cadastro ---\n");
   		 						printf("Nome: %s\n", tab_hotel[an-1][ap-1].nome);
    							printf("CPF: %s\n", tab_hotel[an-1][ap-1].cpf);
	    						printf("Endereco: %s\n", tab_hotel[an-1][ap-1].endereco);
								printf("Telefone: %s\n", tab_hotel[an-1][ap-1].telefone);
    							printf("E-mail: %s\n", tab_hotel[an-1][ap-1].email);
						}
		}
		else //se tiver mais que 1 reserva
		{
		    printf("\n\nEncontramos essas reservas:\n");
	            
			for (andar = 0; andar <= indice-1; andar++)  // apresentas as reservas encontradas
			{
				printf("\n%d. Andar: %d, Apartamento: %d\n ", andar+1, andares[andar],apartamentos[andar]);
				printf("\n--- Dados do Cadastro ---\n");
   			 	printf("Nome: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].nome);
    			printf("CPF: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].cpf);
				printf("Endereco: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].endereco);
				printf("Telefone: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].telefone);
    			printf("E-mail: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].email);	
			}
		}
	}
	else
		printf ("CPF nao encontrado em reserva.\n");		
			
indice = 0;
	//encontra as ocupações comparando o CPF digitado e o cadastrado
	for (an = 1; an <= TAM_ANDAR - 1; an++) 
		for (ap = 1; ap <= TAM_APART - 1; ap++) 
			if (Hotel[an-1][ap-1] == 'O') 
				if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
				{
					andares[indice]=an;
					apartamentos[indice]=ap;
					indice++;
				}
	// se indice > 0, ao menos uma ocupação existe
	if (indice > 0) 
	{
		if(indice == 1) // só uma existe
		{
			for (an = 1; an <= TAM_ANDAR - 1; an++)
				for (ap = 1; ap <= TAM_APART - 1; ap++)
					if (Hotel[an-1][ap-1] == 'O')
						if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
						{
							printf ("\n\nO quarto:\nAndar:%d e Apartamento:%d esta ocupado.", an, ap);
							printf("\n--- Dados do Cadastro ---\n");
   		 					printf("Nome: %s\n", tab_hotel[an-1][ap-1].nome);
    						printf("CPF: %s\n", tab_hotel[an-1][ap-1].cpf);
	    					printf("Endereco: %s\n", tab_hotel[an-1][ap-1].endereco);
							printf("Telefone: %s\n", tab_hotel[an-1][ap-1].telefone);
	    					printf("E-mail: %s\n", tab_hotel[an-1][ap-1].email);
						}
		}
		else //se tiver mais que 1 ocupação
		{
		    printf("\n\nEncontramos essas ocupacoes:\n");
	            
			for (andar = 0; andar <= indice-1; andar++)  // apresentas as ocupações encontradas
			{
				printf("\n%d. Andar: %d, Apartamento: %d\n ", andar+1, andares[andar],apartamentos[andar]);
				printf("\n--- Dados do Cadastro ---\n");
   			 	printf("Nome: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].nome);
    			printf("CPF: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].cpf);
				printf("Endereco: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].endereco);
				printf("Telefone: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].telefone);
    			printf("E-mail: %s\n", tab_hotel[andares[andar]-1][apartamentos [andar]-1].email);	
			}
		}
	}
	else
		printf ("CPF nao encontrado em ocupacao.\n");							
}

void FuncaoTaxa (char Hotel[TAM_ANDAR][TAM_APART]) // calcula a taxa de ocupação e reserva
{
int an, ap;
float  nO, nR, taxa, tr; //nO = número de ocupações; nR = número de reservas; tr= taxa de reserva
nO= 0; nR=0;
	
	//Taxa de ocupacao
	for(an = 1; an <= TAM_ANDAR; an++)
		for(ap = 1; ap <= TAM_APART; ap++)                    
			{                                      
				if (Hotel[an-1][ap-1] == 'O')
				nO++;								
			}
			
	taxa=(nO*100)/ TAM_HOTEL; 
	
	printf("A taxa de ocupacao do hotel vale: %.2f %%\n", taxa);
	
	//Taxa de reserva
	for(an = 1; an <= TAM_ANDAR; an++)
		for(ap = 1; ap <= TAM_APART; ap++)
			{                                     
				if (Hotel[an-1][ap-1] == 'R')
				nR++;								
			}
			
	tr=(nR*100)/  TAM_HOTEL;
	
	printf("A taxa de reserva do hotel vale: %.2f %%\n", tr);	
}

int CheckinCPF (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], char cpf[12]) // faz o check-in com reserva
{
int an, ap, indice=0, option, andar;
int andares[TAM_HOTEL];
int apartamentos[TAM_HOTEL];
	
	//encontra as reservas comparando o CPF digitado e o cadastrado
	for (an = 1; an <= TAM_ANDAR - 1; an++)
		for (ap = 1; ap <= TAM_APART - 1; ap++)
			if (Hotel[an-1][ap-1] == 'R')
				if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
				{
					andares[indice]=an;
					apartamentos[indice]=ap;
					indice++;
				}
	// se indice > 0, ao menos uma reserva existe
	if (indice > 0) {
		
		if(indice == 1) // só uma existe
		{
			for (an = 1; an <= TAM_ANDAR - 1; an++)
				for (ap = 1; ap <= TAM_APART - 1; ap++)
					if (Hotel[an-1][ap-1] == 'R')
						if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
						{
							Hotel[an - 1][ap - 1] = 'O';
							printf("\n\nReserva encontrada: andar - %d, quarto - %d\n\n", an, ap);
							printf("\nCheck-In feito com sucesso\n");
						return 1;
						}
		}
		else //se tiver mais que 1 reserva
		{
		printf("\n\nEncontramos essas reservas, qual voce deseja ocupar(escolha uma opcao)?\n");
	            
		for (andar = 0; andar <= indice-1; andar++)  // apresentas as reservas encontradas
		{
			printf("%d. Andar: %d, Apartamento: %d\n ", andar+1, andares[andar],apartamentos[andar]);
		}
		
		scanf ("%d",&option);
		
		if (option > 0 && option <= andar)
		{
			Hotel [andares[option-1]-1][apartamentos [option-1]-1] = 'O';
			printf("\nCheck-In feito com sucesso\n"); // ocupa o quarto
			return 1;
		}
		
		else //se o valor inserido for menor que zero ou maior que TAM_HOTEL 
		{
			printf("Opcao invalida\n");
			return 0;
		}
		}
	}
	printf ("CPF nao encontrado");
	return 0;
}

int CheckoutCPF (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], char cpf[12]) // faz o check-out
{
int an, ap, indice=0, option, andar;
int andares[TAM_HOTEL];
int apartamentos[TAM_HOTEL];
	
	for (an = 1; an <= TAM_ANDAR - 1; an++)
		for (ap = 1; ap <= TAM_APART - 1; ap++)
			if (Hotel[an-1][ap-1] == 'O')
				if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
				{
					andares[indice]=an;
					apartamentos[indice]=ap;
					indice++;
				}
	
	if (indice > 0) 
	{
		if(indice == 1) 
		{
			for (an = 1; an <= TAM_ANDAR; an++)
				for (ap = 1; ap <= TAM_APART; ap++)
					if ( Hotel[an - 1][ap - 1] == 'O')
						if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
						{
							Hotel[an - 1][ap - 1] = '.'; 
							printf("\nCheck-Out feito com sucesso\n");// desocupa o quarto
							return 1;
						}
		}
		
		printf("\n\nEncontramos essas reservas, qual voce deseja desocupar(escolha uma opcao)?\n");
	            
		for (andar = 0; andar <= indice-1; andar++) 
		{
			printf("%d. Andar: %d, Apartamento: %d\n ", andar+1, andares[andar],apartamentos[andar]);
		}
		
		scanf ("%d",&option);
		if (option > 0 && option <= andar)
		{
			Hotel [andares[option-1]-1][apartamentos [option-1]-1] = '.';
			printf("\nCheck-Out feito com sucesso\n"); // desocupa o quarto
			return 1;
		}
		else //se o valor inserido for menor que 0 ou maior que TAM_HOTEL
		{
			printf("Opcao invalida\n");
			return 0;
		}
	}
	
	printf ("CPF nao encontrado");
	return 0;
}

int CancelarReservaCPF (char Hotel [TAM_ANDAR] [TAM_APART], struct strcadastro tab_hotel [TAM_ANDAR][TAM_APART], char cpf[12]) // cancela a reserva
{
int an, ap, indice=0, option, andar;
int andares[TAM_HOTEL];
int apartamentos[TAM_HOTEL];
	
	for (an = 1; an <= TAM_ANDAR - 1; an++)
		for (ap = 1; ap <= TAM_APART - 1; ap++)
			if (Hotel[an-1][ap-1] == 'R')
				if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
				{
					andares[indice]=an;
					apartamentos[indice]=ap;
					indice++;
				}
	
	if (indice > 0) 
	{
		if(indice == 1) 
		{
			for (an = 1; an <= TAM_ANDAR; an++)
				for (ap = 1; ap <= TAM_APART; ap++)
					if ( Hotel[an - 1][ap - 1] == 'R')
						if (strcmp(cpf, tab_hotel[an-1][ap-1].cpf) == 0)
						{
							Hotel[an - 1][ap - 1] = '.';
							printf("\nreserva cancelada com sucesso\n"); // cancela a reserva
							return 1;
						}
		}
		printf("\n\nEncontramos essas reservas, qual voce deseja cancelar (escolha uma opcao)?\n");
	            
		for (andar = 0; andar <= indice-1; andar++) 
		{
			printf("%d. Andar: %d, Apartamento: %d\n ", andar+1, andares[andar],apartamentos[andar]);
		}
		
		scanf ("%d",&option);
		if (option > 0 && option <= andar)
		{
			Hotel [andares[option-1]-1][apartamentos [option-1]-1] = '.';
			printf("\nreserva cancelada com sucesso\n"); // cancela a reserva
			return 1;
		}
		else //se o valor inserido for menor que 0 ou maior que TAM_HOTEL
		{
			printf("Opcao invalida\n");
			return 0;
		}
	}
	
	printf ("CPF nao encontrado");
	return 0;
}

void LimpaEntrada (void) // limpa o scanf
{
	char carac;
	while ((carac = fgetc(stdin)) != EOF && carac != '\n')
		;
}