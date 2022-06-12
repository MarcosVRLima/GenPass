#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
/*Esta struct armazena os atributos básicos que cada conta tem*/
typedef struct{
	char plataforma[20];
	char email[30];
	char senha[32];
	unsigned short int ativo;
}conta;

int op = 0; /*Variável global que controla os laços para o programa não sair de execução*/
char nomearq[31]; /*Varável global que armazena o nome do arquivo quando o usuario estiver logado*/
char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '_', '.', '-', '$', '%', '/', '&', '(', ')', '[', ']', '?', '!', '@', '=', '+', '*'};
void msg(char *alert); /*Função que recebe como parâmetro uma string e exibe essa string como mensagem na tela com tempo para usuario ler*/
void cripto(char *texto, char modo); /*Função que recebe como parâmetro uma string e um caractere para realizar a 'criptografia' ou 'descriptografia' das informações contidas no arquivo*/
void nomeArquivo(char *nomearquivo); /*Função que recebe uma string como parâmetro e concatena primeiro o diretorio da pasta com a string e depois a extensão*/
void mask(char *senha, char *msgm);
void menu(); /*Função que controla o menu principal*/
void menuUser(); /*Função que controla o menu do usuario depois que fizer o login*/
void login(); /*Função que verifica se o acesso do usuario ao arquivo*/
void criarConta(); /*Função que cria um arquivo e insere nele uma senha*/
void cadSenha(); /*Função que cadastra uma conta com seus atributos em um arquivo*/
void listaSenha(); /*Função que exibe para o usuario as contas cadastradas*/
void attSenha(); /*Função que atualiza a senha de uma conta escolhida pelo usuario*/
void delSenha(); /*Função que remove uma conta cadastrada pelo usuario*/
void attSenhaArq(); /*Função que atualiza a senha do arquivo*/
void gerarSenha(char *senha); /*Função que recebe como parâmetro uma string e gera uma senha nesta string*/

int main(){
	srand(time(NULL)); /*Semeador de aleatoriedade*/
	setlocale(LC_ALL, "Portuguese"); /*Setar a linguagem portuguesa como padrão*/
	CreateDirectory("./data", NULL); /* Função que cria uma pasta, passando como argumento o diretorio e a constante NULL*/
	system("title Sistema de Gerenciamento de Senhas"); /*Define o titulo da janela no interpretador de comandos*/
	msg("Seja bem vindo ao sistema de gerenciamento de contas!"); /*Funão que exibe uma mensagem passada por parâmetro*/
	menu(); /*Chama a função menu*/
	return 0;
}
void msg(char *alert){
	Sleep(300); /*Congela por 0,5 segundos*/
	system("cls"); /*Limpa a tela*/
	puts(alert); /*Imprime a string recebida como parâmetro na tela*/
	Sleep(500); /*Congela por 1 segundos*/
}
void nomeArquivo(char *nomearquivo){
	char strtemp[31] = "./data/";
	strcat(strtemp,nomearquivo);
	strcpy(nomearquivo,strtemp);
	strcat(nomearquivo, ".bin");
	/*Função que concatena o diretorio com o nome do arquivo e a extensão*/
}
void mask(char *masq, char *msgm){
	int i;
	char c, senha[33] = "";
	Sleep(300);
	do{
		system("cls");
		printf("%s ", msgm);
  		for(i = 0; i < strlen(senha); i++){
			putchar('*');
		}
		c = getch();
		for(i = 0; i < strlen(characters); i++){
			if(c == characters[i]){
				senha[strlen(senha)] = c;
				break;
			}else if(c == 8){
				senha[strlen(senha)-1] = NULL;
				break;
			}else if(isspace(c)){
				senha[strlen(senha)] = '\0';
				break;
			}
		}
	}while(!isspace(c));
	strcpy(masq,senha);
}
void menu(){
	do{
		msg("### Menu principal ###\n");
		puts("Escolha uma opção:");
		puts("1 - Registar-se");
		puts("2 - Entrar");
		puts("0 - Sair");
		printf("\nDigite: ");
		scanf("%d", &op); /*Recebe do usuario um inteiro*/
		fflush(stdin);
		switch(op){
			case 0: /*Encerra o programa*/
				msg("Obrigado por utilizar nosso sistema!");
				break;
			case 1: /*Chama a função login*/
				criarConta();
				break;
			case 2: /*Chama a função criar conta*/
				login();
				break;
			default: /*Imprime uma mensagem de erro*/
				msg("Opção inválida!");
		}
	}while(op != 0);
}
void criarConta(){
	char nomea[31] = "", senhaa[2][33] = {"", ""};
	do{
		int r;
		msg("### Criar arquivo ###\n");
		printf("Digite o nome do arquivo: ");
		gets(nomea); /*Recebe do usuario uma string para ser o nome do arquivo*/
		fflush(stdin); /*Esvazia o buffer para não ocasionar erros de leitura*/
		nomeArquivo(nomea); /*Chama a função para concatenar*/
		FILE *file = fopen(nomea,"rb"); /*Abre o arquivo como modo de leitura em binario*/
		if(file != NULL){ /*Condição que verifica se o arquivo já existe*/
			msg("Já existe um arquivo com este nome, deseja continuar com este nome?\n1 - Sim\n0 - Não\n");
			printf("Digite: ");
			scanf("%d", &r);
			fflush(stdin);
			if(r == 1){
				fclose(file); /*Nesta opção o usuario aceita substituir um arquivo que já existe*/
				break;
			}else{
				fclose(file); /*Nesta opção o usuario retorna para o inicio da estrutura de repetição*/
			}
		}else{
			fclose(file);
			break;
		}
	}while(1);
	
	FILE *file = fopen(nomea,"wb"); /*Abre o arquivo no modo de escrita em binario*/
	if(file != NULL){
  		fflush(stdin);
		mask(senhaa[0], "### Criar arquivo ###\n\nDigite a senha do arquivo:");
		mask(senhaa[1], "### Criar arquivo ###\n\nDigite novamente a senha do arquivo:");
		if(strcmp(senhaa[0], senhaa[1]) == 0){
			cripto(senhaa, 'c'); /*Criptografa a senha para salvar no arquivo*/
			int t = fwrite(senhaa,sizeof(char),32,file); /*Função que escreve em um arquivo e recebe como retorno um inteiro*/
			if(t == 32){ /*Verifica se salvou corretamente a senha no arquivo*/
				msg("Arquivo criado com sucesso!");
				fclose(file);
			}else{
				msg("Erro ao criar arquivo!");
				fclose(file);
			}
		}else{
			msg("Senhas diferentes!");
			fclose(file);
			remove(nomea);
		}
	}else{
		msg("Erro ao criar arquivo!");
		fclose(file);
	}
}
void login(){
	msg("### Login ###\n");
	char nomea[31], senhaa[2][33]; /*senha é um vetor de string que contém dois elementos*/
	printf("Digite o nome do arquivo: ");
	gets(nomea);
	fflush(stdin);
	nomeArquivo(nomea);
	FILE *file = fopen(nomea,"rb"); 
	if(file != NULL){ /*Condição que verifica se o arquivo existe*/
		strcpy(nomearq,nomea); /*Copia a string com o nome do arquivo para a variavel global que guarda o nome do arquivo*/
		mask(senhaa[0], "### Login ###\n\nDigite a senha do arquivo:");
		cripto(senhaa[0], 'c'); /*Criptografa a senha*/
		int t = fread(senhaa[1],sizeof(char),32,file); /*Le a senha do arquivo e guarda no indice 1*/
		if(strcmp(senhaa[0],senhaa[1]) == 0 && t == 32){ /*Condição que compara as senhas e se o arquivo foi lido corretamente*/
			msg("Logado com sucesso!");
			fclose(file);
			menuUser(); /*Chama a função menu do usuario quando logado*/
		}else{
			msg("Senha errada!");
			fclose(file);
		}
	}else{
		msg("Este arquivo não exite!");
		fclose(file);
	}
}
void gerarSenha(char *senha){
	int qtd, i = 0, r, o;
	do{
		puts("\nEscolha uma opção:");
		puts("1 - Digitar a senha");
		puts("2 - Gerar uma senha");
		printf("\nDigite: ");
		scanf("%d", &r);
		fflush(stdin);
		switch(r){
			case 1: /*Opção escolhida pelo usuario para digitar a senha*/
				printf("\nDigite a senha: ");
				scanf("%s", senha);
				cripto(senha, 'c');
				break;
			case 2: /*Opção escolhida pelo usuario para gerar uma senha*/
				do{
					o = 1;
					puts("\nEscolha a opção: ");
					puts("1 - Senha alfabética");
					puts("2 - Senha numérica");
					puts("3 - Senha alfanumérica");
					puts("4 - Senha alfanumérica + caracteres especiais");
					printf("\nDigite: ");
					scanf("%d", &r);
					fflush(stdin);
					printf("\nDigite a quantidade de caracteres: ");
					scanf("%d", &qtd); /*Recebe um inteiro que diz a quantidade de caracteres*/
					fflush(stdin);
					switch(r){
						case 1:
							for(i = 0; i < qtd; i++){ /*For que vai de 0 até a qtd-1 digitada pelo usuario*/
								senha[i] = characters[rand() % 52]; /*Preenche aleatoriamente com um char de 0 a 51*/
							}
							break;
						case 2:
							for(i = 0; i < qtd; i++){
								senha[i] = characters[rand() % 10 + 52]; /*Preenche aleatoriamente com um char de 52 a 61 */
							}
							break;
						case 3:
							for(i = 0; i < qtd; i++){
								senha[i] = characters[rand() % 62]; /*Preenche aleatoriamente com um char de 0 a 61*/
							}
							break;
						case 4:
							for(i = 0; i < qtd; i++){
								senha[i] = characters[rand() % strlen(characters)]; /*Preenche aleatoriamente com um char de 0 a até o tamanha de elementos do vetor c*/
							}
							break;
						default:
							o--; /*Volta para o inicio da estrutura de repetição*/
					}
					senha[i] = '\0'; /*Guarda na ultima posição do vetor um indicar parao fim da string*/
				}while(o == 0);
				printf("Sua senha é: %s\n", senha);
				system("pause");
				cripto(senha, 'c'); /*Criptografa a senha*/
				break;
			default:
				r = 0;
				puts("Opção inválida!\n");
		}
	}while(r == 0);
}
void cripto(char *texto, char modo){
	int i, k = 130; /*k é uma constante de criptografia*/
	switch(modo){
		case 'c': /*Caso a variavel modo seja c, ele vai criptografar*/
			k *= 1;
			break;
  		case 'd': /*Caso a variavel modo seja c, ele vai descriptografar*/
  			k *= -1;
	}
	for(i = 0; i < strlen(texto); i++){ /*For que vai de 0 até o tamanho da string recebida como parametro*/
		*(texto+i) += k; /*Em cada indice da string soma a constante*/
	}
}
void menuUser(){
	do{
		msg("### Menu da conta ###\n");
		puts("Escolha uma opção:");
		puts("1 - Cadastrar uma conta");
		puts("2 - Listar contas");
		puts("3 - Atualizar uma conta");
		puts("4 - Deletar uma conta");
		puts("5 - Alterar senha do arquivo");
		puts("0 - Sair");
		printf("\nDigite: ");
		scanf("%d", &op);
		fflush(stdin);
		switch(op){
			case 0: /*Opção escolhida para retornar ao menu principal*/
				msg("Sessão encerrada!");
				break;
			case 1: /*Opção escolhida para guardar um conta*/
				cadSenha();
				break;
   			case 2: /*Opção que mostra as contas existentes*/
   				listaSenha();
   				break;
			case 3: /*Opção que atualiza a senha de uma conta*/
				attSenha();
				break;
			case 4: /*Opção que apaga uma conta*/
				delSenha();
				break;
			case 5: /*Opção que atualiza a senha do arquivo*/
				attSenhaArq();
				break;
			default: /*Opção que mostra uma mensagem de erro*/
				msg("Opção inválida!");
		}
	}while(op != 0); /*Quando o operador for 0, sai da estrutura de repetição*/
	op++; /*Adiciona mais um para não sair da função menu principal*/
}
void cadSenha(){
	conta account; /*Estrutura do tipo conta*/
	int r;
	msg("### Cadastrar conta ###\n");
	printf("Digite o nome da plataforma: ");
	gets(account.plataforma); /*Guarda o nome da plataforma em um dos atributos da estrutura*/
	cripto(account.plataforma, 'c');
	fflush(stdin);
	printf("Digite o email ou nome de usuario: ");
	scanf("%s", account.email);
	cripto(account.email, 'c');
	fflush(stdin);
	gerarSenha(account.senha); /*Função que gera uma senha, passando como parametro um atributo da estrutura*/
	account.ativo = 1; /*Atribui 1 para dizer que aquela conta está ativa*/
	FILE *file = fopen(nomearq, "a+b"); /*Abre o arquivo no modo leitura e escrita e sempre escreve no final do arquivo*/
	r = fwrite(&account, sizeof(conta), 1, file); /*Guarda no final do arquivo a estrutura conta*/
	if(r == 1){
		msg("Conta cadastrada com sucesso!");
	}
		fclose(file);
}
void listaSenha(){
	msg("### Listagem de contas ###\n");
	FILE *file = fopen(nomearq, "rb");
	fseek(file, 0, SEEK_END); /*Posiciona o ponteiro no final do arquivo*/
	int t = (ftell(file)-32)/84, i, r = 0; /*A função ftell retorna a quantidade de bytes do arquivo. Já a variável t guardará a quantidade de contas guardadas*/
	if(t){ /*Se existir pelo menos uma conta*/
		conta c[t]; /*Cria um array de uma estrura conta com t elementos*/
		rewind(file); /*Posiciona o ponteiro para o inicio do arquivo*/
		fseek(file, 32, SEEK_SET); /*Move o ponteiro para depois da senha do arquivo*/
		fread(c, sizeof(conta), t, file); /*Le o arquivo e guarda no array de estruturas as contas criadas*/
		for(i = 0; i < t; i++){ /*For que vai de 0 até a quantidade de contas criadas */
			if((i+c)->ativo){ /*Condição que verifica se a conta extá ativa*/
				cripto((i+c)->plataforma, 'd'); /*Primeiro há uma algebra de ponteiros, que direciona em qual estrutura vai modificar o atributo plataforma*/
				cripto((i+c)->email, 'd');
				cripto((i+c)->senha, 'd');
				puts("-----------////-----------\n");
				printf("ID: %d\n", i+1); /*Valor relacional a ordem guarda no arquivo*/
				printf("Plataforma: %s\n", (i+c)->plataforma);
				printf("Email/Nome de usuario: %s\n", (i+c)->email);
				printf("Senha: %s\n\n", (i+c)->senha);
			}else{
				r++; /*Se não adiciona +1 a variavel r*/
			}
		}
		if(r == t){ /*Se o numero de contas desativadas for igual ao numero de contas no arquivo*/
			puts("-----------////-----------\nNenhuma conta cadastrada!\n");
		}
	}else{
		puts("-----------////-----------\nNenhuma conta cadastrada!\n");
	}
	system("pause");
	fclose(file);
}
void attSenha(){
	int id, r;
	msg("### Atualização de conta ###\n");
	printf("Digite o ID da conta: ");
	scanf("%d", &id); /*Recebe do usuario um id, que relaciona a ordem de contas no arquivo*/
	fflush(stdin);
	FILE *file = fopen(nomearq, "r+b"); /*Abre o arquivo no modo de leitura e escrita e sobrepõe os dados*/
	conta c;
	fseek(file, 32+sizeof(conta)*(--id), SEEK_SET); /*Posiciona o ponteiro no inicio da estrutura indicada pelo id*/
	r = fread(&c, sizeof(conta), 1, file); /*Guarda uma estrutura do tipo conta*/
	if(r == 1 && c.ativo){ /*Condição que verifica se o arquivo foi lido corretamente e se a conta está ativa*/
		cripto(c.plataforma, 'd');
		cripto(c.email, 'd');
		cripto(c.senha, 'd');
		puts("-----------////-----------\n");
		printf("Plataforma: %s\n", c.plataforma);
		printf("Email/Nome de usuario: %s\n", c.email);
		printf("Senha antiga: %s\n", c.senha);
		gerarSenha(c.senha); /*Gera uma nova senha*/
		rewind(file);
		fseek(file, 32+sizeof(conta)*id, SEEK_SET); /*Posiciona o ponteiro para o inicio da estrutura indicada pelo id*/
		cripto(c.plataforma, 'c');
		cripto(c.email, 'c');
		c.ativo = 1;
		r = fwrite(&c, sizeof(conta),1,file);  /*Sobrepõe as informações no arquivo*/
		if(r == 1){
			msg("Senha atualizada com sucesso!");
		}else{
			msg("Erro ao editar!");
		}
	}else{
		msg("Este ID não existe"); /*Mensagem de erro, sendo uma das causas a conta desativada*/
	}
	fclose(file);
}
void delSenha(){
 int r, id;
	msg("### Deletar conta ###\n");
	printf("Digite o ID da conta: ");
	scanf("%d", &id);
	fflush(stdin);
	FILE *file = fopen(nomearq, "r+b");
	conta c;
	fseek(file, 32+sizeof(conta)*(--id), SEEK_SET);
	r = fread(&c, sizeof(conta), 1, file);
	if(r == 1 && c.ativo){
		cripto(c.plataforma, 'd');
		cripto(c.email, 'd');
		cripto(c.senha, 'd');
		puts("-----------////-----------\n");
		printf("Plataforma: %s\n", c.plataforma);
		printf("Email/Nome de usuario: %s\n", c.email);
		printf("Senha: %s\n", c.senha);
		printf("\nDeseja apagar esta conta?\n1 - Sim\n0 - Não\n\nDigite: ");
		scanf("%d", &r); /*Recebe um inteiro do usuario que confirma se quer desativar a conta*/
		fflush(stdin);
		if(r == 1){
			c.ativo = 0; /*Altera o valor do atributo da estrutura, que assim indica que a conta está desativada*/
			rewind(file);
			fseek(file, 32+sizeof(conta)*id, SEEK_SET);
			cripto(c.plataforma, 'c');
			cripto(c.email, 'c');
			cripto(c.senha, 'c');
			r = fwrite(&c, sizeof(conta),1,file);
			if(r == 1){
				msg("Conta deletada com sucesso!");
			}else{
				msg("Erro ao deletar!");
			}
		}
	}else{
		msg("Este ID não existe!");
	}
	fclose(file);
}
void attSenhaArq(){
	msg("### Alterar senha ###\n");
	char senha[2][33];
	mask(senha[0], "### Alterar senha ###\n\nDigite a senha atual do arquivo:");
	cripto(senha[0], 'c');
	FILE *file = fopen(nomearq,"r+b");
	int t = fread(senha[1],sizeof(char),32,file); /*Le a senha do arquivo e guarda no indice 1*/
	if(strcmp(senha[0], senha[1]) == 0 && t == 32){ /*Condição que compara as senhas e se o arquivo foi lido corretamente*/
		mask(senha[0], "### Alterar senha ###\n\nDigite a nova senha do arquivo:");
		mask(senha[1], "### Alterar senha ###\n\nDigite mais uma vez a nova senha do arquivo:");
		if(strcmp(senha[0],senha[1]) == 0){
			cripto(senha[0], 'c');
			rewind(file);
			int r = fwrite(senha, sizeof(char), 32,file); /*Salva no arquivo uma nova senha*/
			if(r == 32){
				msg("Senha alterada com sucesso!");
			}else{
				msg("Erro ao alterar senha");
			}
		}else{
			msg("Senhas diferentes, não foi possível alterar!");
		}
	}else{
		msg("Senha errada!");
	}
	fclose(file);
}
