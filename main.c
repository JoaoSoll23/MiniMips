#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    //Declara��o de structs
    struct instrucao *inst_name = malloc(256 * sizeof(struct instrucao)); //alocando dinamicamente a mem�ria para receber 256 espa�os de mem do tipo instrucao
    struct mem_dado *d_dado = malloc(256 * sizeof(struct mem_dado));      //alocando dinamicamente a mem�ria para receber 256 espa�os de mem do tipo mem_dado
    struct estado_salvo estado;

    //Declara��o de vari�veis
    int num_opcao = 0;                        //Controla o menu
    int PC = 0;                               //Vari�vel que controla o valor do PC durante a execu��o do programa
    int memoria_instrucoes_carregada = 0;     //Indica se as mem�rias de instru��es foi carregada
    int banco_de_registradores[8] = {0};      //Inicializa o banco de rg
    int tamanho = 0;                          //vari�vel utilizada em algumas fun��es da mem�ria de dados

    //Inicio do menu
    printf("\t\tMenu Principal \n\n");
    printf("\t(1)  Carregar mem�ria de instru��es.\n"); //.mem
    printf("\t(2)  Carregar mem�ria de Dados.\n"); //.dat
    printf("\t(3)  Imprimir mem�rias (instru��es e dados).\n"); //(instucoes e dados)
    printf("\t(4)  Imprimir banco de registradores.\n");
    printf("\t(5)  Imprimir todo o simulador (registradores e mem�rias).\n"); //(registradores e memorias)
    printf("\t(6)  Salvar .asm\n");
    printf("\t(7)  Salvar .dat\n");
    printf("\t(8)  Executar Programa.\n"); //run
    printf("\t(9)  Executar uma instru��o.\n"); //step
    printf("\t(10) Voltar uma instru��o.\n"); //back
    printf("\t(11) Encerrar o programa.\n\n");

    while(num_opcao != 11){

            printf("\n");
            printf("\tINFORME QUAL OP��O DESEJA: ");
            scanf("%d", &num_opcao);
            printf("\n");

            switch (num_opcao){

            case 1 :
                Carregar_Memoria_Instrucoes(inst_name);
                memoria_instrucoes_carregada = 1;                                       // Atualiza para 1 indicando que a mem�ria foi carregada
                break;

            case 2 :
                Carregar_Memoria_Dados(d_dado, &tamanho);
                break;

            case 3 :
                if (memoria_instrucoes_carregada == 1) {
                    printf("********Mem�ria de Instru��es********\n\n");
                    Imprimir_Memorias_Instrucoes(inst_name);
                }
                else {
                    printf("\tMem�rias de instru��es n�o carregada.\n\n");
                }
                printf("********Mem�ria de Dados********\n\n");
                ImprimirMemorias_d(d_dado, &tamanho);
                break;

            case 4 :
                Imprimir_BancoRG(banco_de_registradores);
                break;

            case 5 :
                Imprimir_BancoRG(banco_de_registradores);
                if (memoria_instrucoes_carregada == 1) {
                printf("********Mem�ria de Instru��es********\n\n");
                Imprimir_Memorias_Instrucoes(inst_name);
                }
                else{
                    printf("\tMem�ria de instru��es n�o carregada.\n\n");
                }
                printf("********Mem�ria de Dados********\n\n");
                ImprimirMemorias_d(d_dado, &tamanho);
                break;

            case 6 :
                if (memoria_instrucoes_carregada == 1) {
                    Salva_Asm(inst_name);
                    }
                    else{
                    printf("\tMem�rias de instru��es n�o foi carregada.\n");
                    }
                break;

            case 7 :
                    Salva_Dado(d_dado, &tamanho);
                break;

            case 8 :
                if (memoria_instrucoes_carregada == 1) {
                    while (PC < 256 && inst_name[PC].opcode != -1) {                                    // Programa roda at� n�o haver mais instru��es
                        if (inst_name[PC].opcode == 2 || inst_name[PC].opcode == 8) {                   // se for do tipo J ou BEQ, ele realiza a mudan�a no PC diretamente pelas fun��es
                            Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                            Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                            printf("********Pr�xima Instru��o********\n\n");
                            printf("\tPC = %d\n\n", PC);
                        } else {
                            Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                            Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                            printf("********Pr�xima Instru��o********\n\n");
                            PC++;
                            printf("\tPC = %d\n\n", PC);
                        }
                    }
                } else {
                    printf("\tMem�rias de instru��es n�o foi carregada.\n");
                }
                break;

            case 9 :
                if (memoria_instrucoes_carregada == 1) {
                    if (inst_name[PC].opcode == 2 || inst_name[PC].opcode == 8) {                        // se for do tipo J ou BEQ, ele realiza a mudan�a do PC diretamente pelas fun��es
                        Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                        Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                        printf("********Pr�xima Instru��o********\n\n");
                        printf("\tPC = %d\n\n", PC);
                    } else {                                                                             // se n�o for, ele incrementa o PC ap�s a instru��o ser executada
                        Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                        Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                        printf("********Pr�xima Instru��o********\n\n");
                        PC++;
                        printf("\tPC = %d\n\n", PC);
                    }
                } else {
                    printf("\tMem�rias de instru��es n�o foi carregada.\n");
                }
                break;

            case 10 :
                if(PC == 0){
                    printf("\tN�o � poss�vel retornar uma instru��o\n\n");
                }
                else{
                    Retorna_Estado(&estado, &PC, d_dado, banco_de_registradores);
                    printf("\tPC = %d\n", PC);
                }

                break;

            case 11:
                printf("\tPrograma encerrado!\n");
                break;

            default:
                printf("\tOp��o inv�lida.\n");
                break;
            }
    }

    //libera a mem�ria alocada dinamicamente pelo malloc
    free(inst_name);
    free(d_dado);

    return 0;
}
