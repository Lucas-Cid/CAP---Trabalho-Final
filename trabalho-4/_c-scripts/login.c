#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POST 7

void die(const char msg[255]) {
	printf("\n%s\n", msg);
	exit(1);
}

void pageRedirect(const char usrName[15], int pin, const char path[255]) {

}

typedef struct x
{
    int ID;
    char usrOrigem[10];
    int like;
    int deslike;
    char msg[180];
} postagem;

char *capturaQuery (const char varname[15], const char query_string[255])
{
    char *p;
    char resposta[500];
    char *q = resposta;
    //necessario incluir a biblioteca <string.h>
    p = strstr(query_string, varname);
    p += strlen(varname) + 1;
    while (*p != '&' && *p != '\0')
    {
        if (*p == '+')
        {
            *q = ' ';
        }
        else
        {
            *q = *p;
        }
        q++;
        p++;
    }
    *q = '\0';

    char *out = resposta;
    return out;
}

int main() {
	FILE *fp = fopen("../trabalho-4/_registros/usuarios.txt", "a+");
	if (fp == NULL) die("Impossivel acessar o arquivo");

	// Pega os dados da entrada-padrão
	// todo E se a entrada-padrão estiver vazia?
    char dados[100];
    fgets(dados, sizeof(dados), stdin);

    //prefixo db_ = DataBase, ou seja, se refere aos dados salvos no arquivo
	char usrName[255], db_usrName[255], nome[255], aux[5];
	int pin, db_pin;
	int login = 0;

    // Captura os dados digitados pelo usuário
    strcpy(usrName, capturaQuery("usrname", dados));
    strcpy(aux, capturaQuery("pin", dados));
	pin = atoi(aux);

    // escaneia até achar a combinação ou até o fim do arquivo
	while (!feof(fp) && !login) {
		fscanf(fp, "%s %d %*d %*d %*s %[^\n]\n", db_usrName, &db_pin, nome);

		// strcmp retorna 0 caso ambas as strings sejam iguais
		// compara os dados capturados com os do arquivo
		if (!strcmp(db_usrName, usrName) && db_pin == pin)
			login = 1;
	}

	// resultados
	printf(
	    "Content-Type: text/html\n\n"
	    "<!doctype html>"
        "<html>"

        "<head>"
            "<meta charset=\"UTF-8\">"
            "<title>Azkaboard</title>"
        "</head>"
	);

	if (!login) {

	    // LOGIN RECUSADO
	    printf(
	        "<h1>Não foi possível verificar seu login</h1>"
	        "<p>Verifique seus dados e tente novamente</p>"
	        "<form method=\"post\" action=\"login.cgi\">"
	            "<input name=\"usrname\" placeholder=\"Nome de usuário\">"
	            "<input name=\"pin\" placeholder=\"Código de acesso\">"
	            "<input type=\"submit\" value=\"Fazer login\">"
	        "</form>"
	        "<hl>"
	        "<br>"
	        "<br>"
	        "<a href=\"../trabalho-4/index.html\">Voltar para a página inicial</a>"
	    );

	} else {
	    // LOGIN APROVADO

	    // Imprime um formulário oculto para preservar as informações do usuário
        printf(
        "<form method=\"post\" action=\"dashboard.cgi\" id=\"autosend\">"
            "<input type=\"hidden\" value=\"%s\" name=\"usrname\">"
            "<input type=\"hidden\" value=\"%d\" name=\"pin\">"
            "<input type=\"hidden\" value=\"%s\" name=\"nomeComp\">"
        "</form>"

        "<script>"
            "document.getElementById(\"autosend\").submit();"
        "</script>",
        usrName, pin, nome
        );
//
//
//
//		printf(
//		    "<h1>Login aprovado!</h1>"
//		    "Bem-vindo, <strong>%s</strong>.</h1><br><br>",
//		    nome
//		);
//
//		// Imprime o formulario de postagens
//		printf(
//		    "<form method=\"post\" action=\"post-it.cgi\">"
//		        "<input name=\"usrname\" type=\"hidden\" value=\"%s\">"
//		        "<input name=\"pin\" type=\"hidden\" value=\"%d\">"
//		        "<input name=\"msg\" placeholder=\"Digite o post aqui\">"
//		        "<input type=\"submit\" value=\"Enviar\">"
//		    "</form>"
//		    "<br>"
//		    "<br>"
//		    "<br>",
//
//		    usrName, pin
//		);
//
//        // Abre o arquivo de postagens
//        FILE *posts;
//        if ( (posts = fopen("../trabalho-4/_registros/postagens.txt", "r")) == NULL )
//            printf(
//                "<strong>Abertura do arquivo de postagens falhou!</strong>"
//                "<script>window.stop()</script>"
//            );
//
//
//        /** EXIBE AS POSTAGENS **/
//        postagem nPostagem;
//        FILE *getposts;
//
//        /**** Escreve o conteudo adequado no arquivo ****/
//        char fullQuery[522], postName[522], postMsg[522];
//        char auxNome[522], auxMsg[522];
//
//        for (int i = 0; i < MAX_POST; i++) {
//            // Pega a query completa
//            fgets(fullQuery, sizeof(fullQuery), getposts);
//            printf("Query completa: %s<br>", fullQuery);
//
//            // salva as variaveis
//            strcpy(postName, capturaQuery("user", fullQuery));
//            strcpy(postMsg, capturaQuery("msg", fullQuery));
//
//            // exibe os dados
//            printf("<strong>Postado por</strong>: %s<br>", postName);
//            printf("<strong>Mensagem</strong>: %s<br><hr>", postMsg);
//        }
//
	}
}