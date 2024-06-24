#include <stdio.h>
#include <string.h>

#define LIMITE 30

typedef struct {
    char nomeContato[20];
    char telefone[20];
} Contato;

//adicionar um contato
void adicionarContato(Contato *agenda, int *totalContatos) {
    if (*totalContatos >= LIMITE) {
        printf("Limite de contatos atingido\n");
        return;
    }
    printf("Insira o nome: ");
    scanf("%s", agenda[*totalContatos].nomeContato);
    printf("Insira o telefone: ");
    scanf("%s", agenda[*totalContatos].telefone);
    (*totalContatos)++;
}

//buscar contato pelo nome
void buscarContato(Contato *agenda, int totalContatos) {
    char nomeProcurado[50];
    printf("Digite o nome do contato que procura: ");
    scanf("%s", nomeProcurado);
    for (int i = 0; i < totalContatos; i++) {
        if (strcmp(agenda[i].nomeContato, nomeProcurado) == 0) {
            printf("Contato encontrado: Nome: %s, Telefone: %s\n", agenda[i].nomeContato, agenda[i].telefone);
            return;
        }
    }
    printf("Contato não encontrado\n");
}

// excluir contato pelo nome
void excluirContato(Contato *agenda, int *totalContatos) {
    char nomeParaExcluir[50];
    printf("Digite o nome do contato que deseja excluir: ");
    scanf("%s", nomeParaExcluir);
    for (int i = 0; i < *totalContatos; i++) {
        if (strcmp(agenda[i].nomeContato, nomeParaExcluir) == 0) {
            agenda[i] = agenda[*totalContatos - 1];
            (*totalContatos)--;
            printf("Contato excluído\n");
            return;
        }
    }
    printf("Contato não encontrado\n");
}

// salvar os contatos em um arquivo binário
void salvarContatos(Contato *agenda, int totalContatos) {
    FILE *arquivo = fopen("agenda.dat", "wb");
    if (arquivo == NULL) return;
    fwrite(&totalContatos, sizeof(int), 1, arquivo);
    fwrite(agenda, sizeof(Contato), totalContatos, arquivo);
    fclose(arquivo);
}

// carrega os contatos de um arquivo binário
void carregarContatos(Contato *agenda, int *totalContatos) {
    FILE *arquivo = fopen("agenda.dat", "rb");
    if (arquivo == NULL) {
        *totalContatos = 0;
        return;
    }
    fread(totalContatos, sizeof(int), 1, arquivo);
    fread(agenda, sizeof(Contato), *totalContatos, arquivo);
    fclose(arquivo);
}

int main() {
    Contato agenda[LIMITE];
    int totalContatos = 0;
    int escolha;

    carregarContatos(agenda, &totalContatos);

    do {
        printf("1-Adicionar contato\n");
        printf("2-Buscar contato\n");
        printf("3-Excluir contato\n");
        printf("4-Sair\n");
        printf("Escolha uma opçaao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarContato(agenda, &totalContatos);
                break;
            case 2:
                buscarContato(agenda, totalContatos);
                break;
            case 3:
                excluirContato(agenda, &totalContatos);
                break;
            case 4:
                salvarContatos(agenda, totalContatos);
                break;
            default:
                printf("Opção invlida, tente novamente\n");
        }

    } while (escolha != 4);{
    return 0;}
}
