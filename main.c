#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // Variável para guardar o texto escrito pelo utilizador
    char texto[100];

    while (1)
    {
        // Mostrar o nome da shell
        printf("myshell> ");

        // Ler o texto introduzido pelo utilizador
        fgets(texto, 100, stdin);

        // Remover o ENTER (\n) que o fgets guarda
        texto[strcspn(texto, "\n")] = '\0';

        // Se o utilizador escrever "exit", termina o programa
        if (strcmp(texto, "exit") == 0)
        {
            printf("A terminar o programa...\n");
            break;
        }

        // Se o utilizador escrever "clear", limpa o ecrã
        else if (strcmp(texto, "clear") == 0)
        {
            system("clear");
            continue;
        }

        // Se o utilizador escrever "help", mostra ajuda
        else if (strcmp(texto, "help") == 0)
        {
            printf("Comandos disponíveis:\n");
            printf("exit  - Termina o programa\n");
            printf("clear - Limpa o ecrã\n");
            printf("help  - Mostra esta ajuda\n");

            continue;
        }

        // Separar o comando do argumento
        char *comando;
        char *argumento;

        comando = strtok(texto, " ");
        argumento = strtok(NULL, " ");

        // Evita erros se o utilizador apenas carregar ENTER
        if (comando == NULL)
        {
            continue;
        }

        // Mostrar o comando encontrado
        printf("Comando: %s\n", comando);

        pid_t pid = fork();

        if (pid == 0)
        {
            // Processo filho

            if (argumento == NULL)
            {
                execlp(comando, comando, NULL);
            }
            else
            {
                execlp(comando, comando, argumento, NULL);
            }

            printf("Comando não encontrado.\n");
        }

        else
        {
            // Processo pai espera pelo filho
            wait(NULL);
        }
    }
    return 0;
}