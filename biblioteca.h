#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

struct instrucao {
    char inst_char[17];
    int opcode;
    int rs;
    int rt;
    int rd;
    int funct;
    int imm;
    int addr;
};

struct mem_dado {
    char dado_char[8];
    int dado;
};

struct estado_salvo {
    int copia_PC;
    int copia_banco_de_registradores[8];
    struct mem_dado copia_memoria[256];
};

void Carregar_Memoria_Instrucoes(struct instrucao *inst_name);

void Carregar_Memoria_Dados(struct mem_dado *d_dado, int *tamanho);

void Escrever_Registrador(int *banco_de_registradores, int indice, int valor);

void Executar_Instrucao(int *PC, struct instrucao *inst_name, struct mem_dado *d_dado, int *banco_de_registradores);

int Ler_Registrador(int *banco_de_registradores, int indice);

int Calculos_ULA(int *PC, struct instrucao *inst_name, struct mem_dado *d_dado, int *banco_de_registradores);

void Imprimir_Memorias_Instrucoes(struct instrucao *inst_name);

void ImprimirMemorias_d(struct mem_dado *d_dado, int *tamanho);

void Imprimir_BancoRG(int *banco_de_registradores);

void Escrever_Memoria_Dados(int endereco, int valor, struct mem_dado *d_dado);

int Ler_Memoria_Dados(int endereco, struct mem_dado *d_dado);

void Salva_Dado(struct mem_dado *d_dado, int *tamanho);

void Salva_Asm(struct instrucao *inst_name);

void Visualizar_Instrucao_Atual(int *PC, struct instrucao *inst_name);

void Retorna_Estado(struct estado_salvo *estado, int *PC, struct mem_dado *d_dado,  int *banco_de_registradores);

void Salva_Estado(int *PC, struct mem_dado *d_dado, struct estado_salvo *estado, int *banco_de_registradores);

#endif // BIBLIOTECA_H_INCLUDED
