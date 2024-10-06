#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    //Declaração de structs
    struct instrucao *inst_name = malloc(256 * sizeof(struct instrucao)); //alocando dinamicamente a memória para receber 256 espaços de mem do tipo instrucao
    struct mem_dado *d_dado = malloc(256 * sizeof(struct mem_dado));      //alocando dinamicamente a memória para receber 256 espaços de mem do tipo mem_dado
    struct estado_salvo estado;

    //Declaração de variáveis
    int num_opcao = 0;                        //Controla o menu
    int PC = 0;                               //Variável que controla o valor do PC durante a execução do programa
    int memoria_instrucoes_carregada = 0;     //Indica se as memórias de instruções foi carregada
    int banco_de_registradores[8] = {0};      //Inicializa o banco de rg
    int tamanho = 0;                          //variável utilizada em algumas funções da memória de dados

    //Inicio do menu
    printf("\t\tMenu Principal \n\n");
    printf("\t(1)  Carregar memória de instruções.\n"); //.mem
    printf("\t(2)  Carregar memória de Dados.\n"); //.dat
    printf("\t(3)  Imprimir memórias (instruções e dados).\n"); //(instucoes e dados)
    printf("\t(4)  Imprimir banco de registradores.\n");
    printf("\t(5)  Imprimir todo o simulador (registradores e memórias).\n"); //(registradores e memorias)
    printf("\t(6)  Salvar .asm\n");
    printf("\t(7)  Salvar .dat\n");
    printf("\t(8)  Executar Programa.\n"); //run
    printf("\t(9)  Executar uma instrução.\n"); //step
    printf("\t(10) Voltar uma instrução.\n"); //back
    printf("\t(11) Encerrar o programa.\n\n");

    while(num_opcao != 11){

            printf("\n");
            printf("\tINFORME QUAL OPÇÃO DESEJA: ");
            scanf("%d", &num_opcao);
            printf("\n");

            switch (num_opcao){

            case 1 :
                Carregar_Memoria_Instrucoes(inst_name);
                memoria_instrucoes_carregada = 1;                                       // Atualiza para 1 indicando que a memória foi carregada
                break;

            case 2 :
                Carregar_Memoria_Dados(d_dado, &tamanho);
                break;

            case 3 :
                if (memoria_instrucoes_carregada == 1) {
                    printf("********Memória de Instruções********\n\n");
                    Imprimir_Memorias_Instrucoes(inst_name);
                }
                else {
                    printf("\tMemórias de instruções não carregada.\n\n");
                }
                printf("********Memória de Dados********\n\n");
                ImprimirMemorias_d(d_dado, &tamanho);
                break;

            case 4 :
                Imprimir_BancoRG(banco_de_registradores);
                break;

            case 5 :
                Imprimir_BancoRG(banco_de_registradores);
                if (memoria_instrucoes_carregada == 1) {
                printf("********Memória de Instruções********\n\n");
                Imprimir_Memorias_Instrucoes(inst_name);
                }
                else{
                    printf("\tMemória de instruções não carregada.\n\n");
                }
                printf("********Memória de Dados********\n\n");
                ImprimirMemorias_d(d_dado, &tamanho);
                break;

            case 6 :
                if (memoria_instrucoes_carregada == 1) {
                    Salva_Asm(inst_name);
                    }
                    else{
                    printf("\tMemórias de instruções não foi carregada.\n");
                    }
                break;

            case 7 :
                    Salva_Dado(d_dado, &tamanho);
                break;

            case 8 :
                if (memoria_instrucoes_carregada == 1) {
                    while (PC < 256 && inst_name[PC].opcode != -1) {                                    // Programa roda até não haver mais instruções
                        if (inst_name[PC].opcode == 2 || inst_name[PC].opcode == 8) {                   // se for do tipo J ou BEQ, ele realiza a mudança no PC diretamente pelas funções
                            Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                            Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                            printf("********Próxima Instrução********\n\n");
                            printf("\tPC = %d\n\n", PC);
                        } else {
                            Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                            Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                            printf("********Próxima Instrução********\n\n");
                            PC++;
                            printf("\tPC = %d\n\n", PC);
                        }
                    }
                } else {
                    printf("\tMemórias de instruções não foi carregada.\n");
                }
                break;

            case 9 :
                if (memoria_instrucoes_carregada == 1) {
                    if (inst_name[PC].opcode == 2 || inst_name[PC].opcode == 8) {                        // se for do tipo J ou BEQ, ele realiza a mudança do PC diretamente pelas funções
                        Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                        Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                        printf("********Próxima Instrução********\n\n");
                        printf("\tPC = %d\n\n", PC);
                    } else {                                                                             // se não for, ele incrementa o PC após a instrução ser executada
                        Salva_Estado(&PC, d_dado, &estado, banco_de_registradores);
                        Executar_Instrucao(&PC, inst_name, d_dado, banco_de_registradores);
                        printf("********Próxima Instrução********\n\n");
                        PC++;
                        printf("\tPC = %d\n\n", PC);
                    }
                } else {
                    printf("\tMemórias de instruções não foi carregada.\n");
                }
                break;

            case 10 :
                if(PC == 0){
                    printf("\tNão é possível retornar uma instrução\n\n");
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
                printf("\tOpção inválida.\n");
                break;
            }
    }

    //libera a memória alocada dinamicamente pelo malloc
    free(inst_name);
    free(d_dado);

    return 0;
}
