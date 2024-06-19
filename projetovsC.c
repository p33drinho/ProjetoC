#include <stdio.h>      
#include <string.h>    
#define MAX_REGISTROS 30   
typedef struct {
    char nome[20];       
    char celular[20];    
} Registro;
// Função para adicionar um registro
void adicionarRegistro(Registro *registros, int *numRegistros) {
    if (*numRegistros >= MAX_REGISTROS) {      // Verifica se o limite de registros foi atingido
        printf("voce atingiu o maximo de registros possiveis.\n");  // Informa que o limite foi atingido
        return;  
    }
    printf("nome: ");    // Pede o nome do registro
    scanf("%s", registros[*numRegistros].nome);  // Lê o nome do registro
    printf("celular: "); // Pede o celular do registro
    scanf("%s", registros[*numRegistros].celular); // Lê o celular do registro
    (*numRegistros)++;  // Incrementa o número de registros
}
// Função para buscar um registro pelo nome
void buscarRegistro(Registro *registros, int numRegistros) {
    char nomeBuscado[50];  // Nome do registro a ser buscado
    printf("nome do registro para buscar: ");  // Pede o nome do registro a buscar
    scanf("%s", nomeBuscado);  // Lê o nome do registro
    for (int i = 0; i < numRegistros; i++) {  // Itera pelos registros
        if (strcmp(registros[i].nome, nomeBuscado) == 0) {  // Compara os nomes
            printf("registro encontrado: nome: %s, celular: %s\n", registros[i].nome, registros[i].celular);  // Imprime o registro encontrado
            return;  
        }
    }
    printf("registro nao foi encontrado.\n");  
}
// Função para excluir um registro pelo nome
void excluirRegistro(Registro *registros, int *numRegistros) {
    char nomeExclusao[50];  // Nome do registro a ser excluído
    printf("nome do registro que quer excluir: ");  // Pede o nome do registro a excluir
    scanf("%s", nomeExclusao);  // Lê o nome do registro
    for (int i = 0; i < *numRegistros; i++) {  // Itera pelos registros
        if (strcmp(registros[i].nome, nomeExclusao) == 0) {  // Compara os nomes
            registros[i] = registros[*numRegistros - 1];  // Substitui o registro pelo último registro do array
            (*numRegistros)--;  // Decrementa o número de registros
            return;  
        }
    }
    printf("registro nao fui encontrado.\n");  
}
// Função para salvar os registros em um arquivo binário
void salvarRegistros(Registro *registros, int numRegistros) {
    FILE *file = fopen("registros.dat", "wb");  // Abre o arquivo para escrita binária
    if (file == NULL) return;  // Verifica se o arquivo foi aberto com sucesso
    fwrite(&numRegistros, sizeof(int), 1, file);  // Escreve o número de registros no arquivo
    fwrite(registros, sizeof(Registro), numRegistros, file);  // Escreve os registros no arquivo
    fclose(file);  // Fecha o arquivo
}
// Função para carregar os registros de um arquivo binário
void carregarRegistros(Registro *registros, int *numRegistros) {
    FILE *file = fopen("registros.dat", "rb");  // Abre o arquivo para leitura binária
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        *numRegistros = 0;  // Se não, define o número de registros como 0
        return;  
    }
    fread(numRegistros, sizeof(int), 1, file);  // Lê o número de registros do arquivo
    fread(registros, sizeof(Registro), *numRegistros, file);  // Lê os registros do arquivo
    fclose(file);  // Fecha o arquivo
}
int main() {
    Registro registros[MAX_REGISTROS];  // Array de registros
    int numRegistros = 0;  // Número de registros
    int opcao;  // Opção do menu
    carregarRegistros(registros, &numRegistros);  // Carrega os registros do arquivo
    do {
        printf("1. adicionar registro\n");  // Imprime a opção de adicionar registro
        printf("2. buscar registro\n");  // Imprime a opção de buscar registro
        printf("3. excluir registro\n");  // Imprime a opção de excluir registro
        printf("4. sair\n");  // Imprime a opção de sair
        printf("escolha uma das opcoes acima: ");  // Pede para escolher uma opção
        scanf("%d", &opcao);  // Lê a opção escolhida
        switch (opcao) {
            case 1:
                adicionarRegistro(registros, &numRegistros);  // Chama a função para adicionar registro
                break;
            case 2:
                buscarRegistro(registros, numRegistros);  // Chama a função para buscar registro
                break;
            case 3:
                excluirRegistro(registros, &numRegistros);  // Chama a função para excluir registro
                break;
            case 4:
                salvarRegistros(registros, numRegistros);  // Chama a função para salvar registros
                break;
            default:
                printf("opcao nao valida, bote outra opcao.\n");  // Informa que a opção escolhida é inválida
        }
    } while (opcao != 4);  // Continua até a opção ser sair

    return 0; 
}