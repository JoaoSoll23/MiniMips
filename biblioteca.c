#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void Carregar_Memoria_Instrucoes(struct instrucao *inst_name) { //carrega memória de instruções

setlocale(LC_ALL, "Portuguese");

    char nomefile[100];
    printf("\tDigite o nome do arquivo .mem: ");
    printf("\n\t");
    scanf("%s", nomefile);
    printf("\n");

// Abre o arquivo para leitura
    FILE *file = fopen(nomefile, "r");
    if (file == NULL) {
        printf("\tErro ao abrir o arquivo.\n");
    }
    else{
        printf("\tMemória de instruções carregada!\n");
    }

    // Inicializa todos os 256 opcodes como -1, serve para sinalizar que o espaço está vazio, sem instruções
    for (int i = 0; i < 256; i++) {
        inst_name[i].opcode = -1;
    }

    int posicao = 0;

    // Lê cada linha do arquivo
    while (fgets(inst_name[posicao].inst_char, sizeof(inst_name[posicao].inst_char), file)) {
        // Remove o caractere de nova linha, se presente
        inst_name[posicao].inst_char[strcspn(inst_name[posicao].inst_char, "\n")] = '\0';

        // Verifica se a linha tem exatamente 16 bits
        if (strlen(inst_name[posicao].inst_char) != 16) {
            continue;
        }

        // Separa o opcode (4 primeiros bits)
        char opcode[5] = {0}; // 4 bits + 1 para o caractere nulo
        strncpy(opcode, inst_name[posicao].inst_char, 4); // Copia os 4 primeiros bits para o opcode

        // Converte o opcode para número inteiro
        unsigned int opcode_num = (unsigned int)strtol(opcode, NULL, 2);

        // Verifica o tipo de instrução para armazenar os dados nas variáveis corretas
        if (opcode_num == 4) {
            // Instrução tipo I (ADDI)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};   // 3 bits + 1 para nulo
            char rt[4] = {0};   // 3 bits + 1 para nulo
            char imm[7] = {0};  // 6 bits + 1 para nulo

            // Copia os bits correspondentes para os campos
            strncpy(opcode, inst_name[posicao].inst_char, 4);   // Bits 1 a 4 (opcode)
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);   // Bits 5 a 7 (rs)
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);   // Bits 8 a 10 (rt)
            strncpy(imm, inst_name[posicao].inst_char + 10, 6); // Bits 11 a 16 (imm)

        //Verificar se o valor do imm é positivo ou negativo, se for negativo, desfazer a operação de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 é negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            inst_name[posicao].imm = inst_name[posicao].imm +1; //add +1 no valor convertido
            inst_name[posicao].imm = inst_name[posicao].imm*(-1); //inverte o sinal
        }

        else{
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);


        } else if (opcode_num == 11) {
            // Instrução tipo I (LW)
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2);

        } else if (opcode_num == 15) {
            // Instrução tipo I (SW)
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2);

        } else if (opcode_num == 8) {
            // Instrução tipo I (BEQ)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

        //Verificar se o valor do imm é positivo ou negativo, se for negativo, desfazer a operação de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 é negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            inst_name[posicao].imm = inst_name[posicao].imm +1; //add +1 no valor convertido
            inst_name[posicao].imm = inst_name[posicao].imm*(-1); //inverte o sinal
        }

        else{
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);

        } else if (opcode_num == 2) {
            // Instrução tipo J
            char opcode[5] = {0};
            char addr[8] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(addr, inst_name[posicao].inst_char + 9, 7);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].addr = (int)strtol(addr, NULL, 2);

        } else if (opcode_num == 0) {
            // Instrução tipo R
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char rd[4] = {0};
            char funct[4] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(rd, inst_name[posicao].inst_char + 10, 3);
            strncpy(funct, inst_name[posicao].inst_char + 13, 3);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].rd = (int)strtol(rd, NULL, 2);
            inst_name[posicao].funct = (int)strtol(funct, NULL, 2);

        } else {
            printf("Tipo de instrução não identificada.\n");
        }

        posicao++;

        if (posicao >= 256) {
            printf("\tLimite máximo de instruções atingido.\n");
            break;
        }
    }

    fclose(file);
}

void Carregar_Memoria_Dados(struct mem_dado *d_dado, int *tamanho) { //carrega a memória de dados

    char nomefile[100];
    printf("\tDigite o nome do arquivo .dat: ");
    printf("\n\t");
    scanf("%s", nomefile);
    printf("\n");

    //"r" faz a abertura para leitura, arquivo binário
    FILE *arq = fopen(nomefile, "r");
        if (arq == NULL){
            printf("\tErro ao abrir o arquivo.\n");
        }
        else{
            printf("\tMemória de dados carregada!\n");
        }
        *tamanho = 0;
    while(fscanf(arq, "%d", &d_dado[*tamanho].dado) != EOF && *tamanho < 256) {
                (*tamanho)++;
            }
        fclose(arq);
}


void Imprimir_Memorias_Instrucoes(struct instrucao *inst_name) { //Imprime as memória de instruções

    for(int i=0; i<256; i++) {

        if (inst_name[i].opcode == -1) {
        }
        else if (inst_name[i].opcode == 0) {
            printf("Tipo R - opcode: %d, rs: %d, rt: %d, rd: %d, funct: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].rd, inst_name[i].funct);
        }
        else if(inst_name[i].opcode == 2) {
            printf("Tipo J - opcode: %d, addr: %d\n", inst_name[i].opcode, inst_name[i].addr);
        }
        else if(inst_name[i].opcode == 8) {
            printf("Tipo BEQ - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 15) {
            printf("Tipo SW - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 11) {
                printf("Tipo LW - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 4) {
                printf("Tipo ADDI - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else{
            printf("Tipo de instrução inválida!\n");
        }
    }
    printf("\n");
}

void ImprimirMemorias_d(struct mem_dado *d_dado, int *tamanho){  //Imprime aa memória de dados.

    *tamanho = 256;
    for (int x = 0; x < 16; x++) {
        for(int y = 0; y < 16; y++) {
            int mem = x * 16 + y;
            if (mem < *tamanho) {
                printf("Mem[%d] %d\t", mem, d_dado[mem].dado);
                }
            }
            printf("\n");
        }
}

//**Modelagem do banco de registradores**//

void Escrever_Registrador(int *banco_de_registradores, int indice, int valor) {     //salva valores nos registradores

    if(indice >= 0 && indice < 8) {
        banco_de_registradores[indice] = valor;
    }
    else {
        printf("\tÍndice de registrador não encontrado!\n");
    }

}

int Ler_Registrador(int *banco_de_registradores, int indice) {          //lê valores armazenados nos registradores

    if(indice >= 0 && indice < 8) {
        return banco_de_registradores[indice];
    }
    else{
        printf("\tÍndice de registrador não encontrado!\n");
    }
}

void Imprimir_BancoRG(int *banco_de_registradores) {                   //imprime os valores armazenados no banco de registradores
    printf("********Banco de Registradores********\n");
    printf("\n");
    for(int x=0; x<8; x++) {
        printf("\tRG[%d] = %d\n", x, banco_de_registradores[x]);
    }
    printf("\n");
}

//**Modelagem do banco de registradores**//

int Calculos_ULA(int *PC, struct instrucao *inst_name, struct mem_dado *d_dado, int *banco_de_registradores) { //Executa os cálculos

    int resultado = 0;

    if(inst_name[*PC].opcode == 0) { //Tipo R

        switch(inst_name[*PC].funct) {                                                                                                        // faz a verificação do campo funct para informar qual operação realizar
    case 0:     //soma
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + Ler_Registrador(banco_de_registradores, inst_name[*PC].rt); //faz a soma dos valores armazenados em rs e rt
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado não foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);                                                          //guarda o resultado no registrador indicado por rd
        }
        break;

    case 2:     //sub
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) - Ler_Registrador(banco_de_registradores, inst_name[*PC].rt);
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado não foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);
        }
        break;

    case 4:     //and
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) & Ler_Registrador(banco_de_registradores, inst_name[*PC].rt);
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado não foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);
        }
        break;

    case 5:     //or
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) | Ler_Registrador(banco_de_registradores, inst_name[*PC].rt);
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado não foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);
        }
         break;
        }
    }
    else if(inst_name[*PC].opcode == 4) { //Tipo I Addi
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + inst_name[*PC].imm;  //faz a soma com o valor imm que pode ser negativo
        if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado não foi armazenado\n");
        }
        else{
        Escrever_Registrador(banco_de_registradores, inst_name[*PC].rt, resultado); //se não tiver overflow, guarda o resultado no registrador indicado por rt
        }
    }
    else if(inst_name[*PC].opcode == 8) {   //Tipo I Beq
        if(Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) == Ler_Registrador(banco_de_registradores, inst_name[*PC].rt)){ //verifica se os valores armazenados nos registradores são iguais
            printf("\tInstrução não gerou valor de resultado.\n\n");
            *PC += inst_name[*PC].imm;      //se forem iguais, PC é atualizado com um novo valor
        }
        else{
            printf("\tInstrução não gerou valor de resultado.\n\n");
            (*PC)++;                        // se não forem iguais, incrementa para a próxima instrução
        }
    }
    else if(inst_name[*PC].opcode == 11){ //Tipo I LW
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + inst_name[*PC].imm;                // endereço = rs + imm
        if(resultado < 0 || resultado > 255){
            printf("\tEndereço de memória inválido!\n");
        }else{
        Escrever_Registrador(banco_de_registradores, inst_name[*PC].rt, Ler_Memoria_Dados(resultado, d_dado));      // armazena no registrador
        }

    }
    else if(inst_name[*PC].opcode == 15){//Tipo I SW
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + inst_name[*PC].imm;                // endereço = rs + imm. Lê da memória e armazena no registrador
        if(resultado < 0 || resultado > 255){
            printf("\tEndereço de memória inválido!\n");
        }else{
        Escrever_Memoria_Dados(resultado, Ler_Registrador(banco_de_registradores, inst_name[*PC].rt), d_dado);      // Armazena na memória de dados
        }

    }
    return resultado;
}

void Executar_Instrucao(int *PC, struct instrucao *inst_name, struct mem_dado *d_dado, int *banco_de_registradores) {   //Executa as instruções

    Visualizar_Instrucao_Atual(PC, inst_name);
    Imprimir_BancoRG(banco_de_registradores);

    if(inst_name[*PC].opcode == 2) {
         printf("\tInstrução não gerou valor de resultado.\n\n");
        *PC = inst_name[*PC].addr;                                                     //realiza as do tipo J, alterando diretamente o PC
    }
    else if(inst_name[*PC].opcode == -1) {                                            // se o opcode estiver como -1, indica que não há mais instruções válidas
            printf("\tPC está apontando para um campo vazio!\n\n");
    }
    else if(inst_name[*PC].opcode != 8){
        int resultado = Calculos_ULA(PC, inst_name, d_dado, banco_de_registradores);                    // chama a função da ula que verifica o opcode e executa a operação
            printf("\tResultado da ULA: %d\n\n", resultado);
        }else{
            Calculos_ULA(PC, inst_name, d_dado, banco_de_registradores);
        }
}

int Ler_Memoria_Dados(int endereco, struct mem_dado *d_dado){
    if (endereco < 0 || endereco >= 256) {
        printf("\tEndereço inválido.\n");
    }
    return d_dado[endereco].dado; // Retorna o dado no endereço
}

void Escrever_Memoria_Dados(int endereco, int valor, struct mem_dado *d_dado){
    if (endereco < 0 || endereco >= 256) {
        printf("\tEndereço inválido.\n");
    }
    d_dado[endereco].dado = valor; // Armazena o valor no endereço
}

void Salva_Dado(struct mem_dado *d_dado, int *tamanho){
        printf("\n\n");

        char nomearq[100];

        printf("\tDigite o nome do arquivo .dat: ");
        scanf("%s", nomearq);
        printf("\n");

        FILE *arq = fopen(nomearq, "w");
        if (arq == NULL) {
        printf("\tErro ao abrir o arquivo");
        }

        for(int x = 0; x<*tamanho; x++){
            fprintf(arq,"%d\n", d_dado[x].dado);
        }
        fclose(arq);
}

 void Salva_Asm(struct instrucao *inst_name){
        char nomearq[100];

        printf("\tDigite o nome do arquivo .asm: ");
        scanf("%s", nomearq);
        printf("\n");

        FILE *arq2 = fopen(nomearq, "w");
        if (arq2 == NULL) {
        printf("\tErro ao abrir o arquivo");
        }

        for(int i=0; i < 256; i++){
            if(inst_name[i].opcode == 0){
                if(inst_name[i].funct == 0){
                    fprintf(arq2,"ADD $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 2){
                    fprintf(arq2,"SUB $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 4){
                    fprintf(arq2,"AND $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 5){
                    fprintf(arq2,"OR $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
            }
            else if(inst_name[i].opcode == 4){
                    fprintf(arq2,"ADDI $t%d, $t%d, %d\n", inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
            }else if(inst_name[i].opcode == 11){
                    fprintf(arq2,"LW $t%d, %d($t%d)\n", inst_name[i].rt,inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 15){
                    fprintf(arq2,"SW $t%d, %d($t%d)\n", inst_name[i].rs, inst_name[i].imm, inst_name[i].rt);
            }else if(inst_name[i].opcode == 8){
                    fprintf(arq2,"BEQ $t%d, $t%d, %d\n", inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
            }else if(inst_name[i].opcode == 2){
                    fprintf(arq2,"J %d\n", inst_name[i].addr);
            }
        }

        fclose(arq2);
 }

void Visualizar_Instrucao_Atual(int *PC, struct instrucao *inst_name){

        printf("****************--INSTRUÇÃO ATUAL--****************\n\n");
            if(inst_name[*PC].opcode == 0){
                if(inst_name[*PC].funct == 0){
                    printf("\tADD $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
                else if(inst_name[*PC].funct == 2){
                    printf("\tSUB $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
                else if(inst_name[*PC].funct == 4){
                    printf("\tAND $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
                else if(inst_name[*PC].funct == 5){
                    printf("\tOR $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
            }
            else if(inst_name[*PC].opcode == 4){
                    printf("\tADDI $t%d, $t%d, %d\n", inst_name[*PC].rs, inst_name[*PC].rt, inst_name[*PC].imm);
            }else if(inst_name[*PC].opcode == 11){
                    printf("\tLW $t%d, %d($t%d)\n", inst_name[*PC].rt,inst_name[*PC].imm, inst_name[*PC].rs);
            }else if(inst_name[*PC].opcode == 15){
                    printf("\tSW $t%d, %d($t%d)\n", inst_name[*PC].rs, inst_name[*PC].imm, inst_name[*PC].rt);
            }else if(inst_name[*PC].opcode == 8){
                    printf("\tBEQ $t%d, $t%d, %d\n", inst_name[*PC].rs, inst_name[*PC].rt, inst_name[*PC].imm);
            }else if(inst_name[*PC].opcode == 2){
                    printf("\tJ %d\n", inst_name[*PC].addr);
            }
        printf("\n");
 }

void Salva_Estado(int *PC, struct mem_dado *d_dado, struct estado_salvo *estado, int *banco_de_registradores) {
    // Salvar o PC
    estado->copia_PC = *PC;

    // Salvar o estado dos registradores
    for (int i = 0; i < 8; i++) {
        estado->copia_banco_de_registradores[i] = banco_de_registradores[i];
    }

    // Salvar o estado da memória
    for (int i = 0; i < 256; i++) {
        estado->copia_memoria[i] = d_dado[i];
    }
}

void Retorna_Estado(struct estado_salvo *estado, int *PC, struct mem_dado *d_dado, int *banco_de_registradores) {
    // Restaurar o PC
    *PC = estado->copia_PC;

    // Restaurar os registradores
    for (int i = 0; i < 8; i++) {
        banco_de_registradores[i] = estado->copia_banco_de_registradores[i];
    }

    // Restaurar a memória
    for (int i = 0; i < 256; i++) {
        d_dado[i] = estado->copia_memoria[i];
    }
}
