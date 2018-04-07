#include <stdio.h>
#include <string.h>

void imprime_mensagem(char mensagem[])
{
    unsigned int i;
    printf(" ");
    for (i=0; i<strlen(mensagem); ++i)
        printf("-");
    printf(" \n|%s| \n ", mensagem);
    for (i=0; i<strlen(mensagem); ++i)
        printf("-");
    printf("\n");
}

int main()
{
    char frase[] = " Submissao feita com sucesso! ";
    imprime_mensagem(frase);
    return 0;
}
