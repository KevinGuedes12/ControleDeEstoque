#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


typedef struct {
    int id;
    char product[50];
    int quantity;
    float price;
    float total;
} Stock;
void clearBuffer() { // função so pra limpa o buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void checkQuantity(Stock **product, int *n) {
    for (int i = 0; i < *n; i++) {
        if ((*product)[i].quantity <= 0) {// o checkQuantit faz um varredura no Stock procurando por "quantidade" igual a 0
            printf("Produto '%s' zerou o estoque! Removendo...\n", (*product)[i].product);

            for (int j = i; j < (*n) - 1; j++) { //esse for
                (*product)[j] = (*product)[j + 1];
            }

            (*n)--;

            if (*n == 0) {
                free(*product);
                *product = NULL;
            } else {
                *product = (Stock*) realloc(*product, (*n) * sizeof(Stock));
            }

            i--;
        }
    }
}

void list(Stock *product, int n) {
    if (n == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-12s %-12s\n", "ID", "PRODUTO", "QTD", "PRECO", "TOTAL");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        char price_fmt[12], total_fmt[12];
        //snprintf converte float para string formatada
        snprintf(price_fmt, sizeof(price_fmt), "R$%.2f", product[i].price);
        snprintf(total_fmt, sizeof(total_fmt), "R$%.2f", product[i].total);

        printf("%-5d %-20s %-10d %-12s %-12s\n",
            product[i].id,
            product[i].product,
            product[i].quantity,
            price_fmt,
            total_fmt);
    }
    printf("\n");
}

void cadastration(Stock **product, int *n, int *id) {
    (*n)++;
    *product = (Stock*) realloc(*product, sizeof(Stock) * (*n));

    if (*product == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    int i = (*n) - 1;

    (*product)[i].id = (*id)++;



    printf("Produto: ");
    scanf(" %49s", (*product)[i].product);

    printf("Quantidade: ");
    scanf("%d", &(*product)[i].quantity);

    printf("Preco: ");
    scanf("%f", &(*product)[i].price);
    clearBuffer();

    (*product)[i].total = (*product)[i].quantity * (*product)[i].price;

    printf("Cadastrado com sucesso! (ID: %d)\n", (*product)[i].id);
}

void delete(Stock **product, int *n) {
    if (*n == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int id;
    printf("ID do produto para remover: ");
    scanf("%d", &id);

    int idx = -1;

    for (int i = 0; i < *n; i++) {
        if ((*product)[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("ID %d nao encontrado.\n", id);
        return;
    }

    for (int i = idx; i < (*n) - 1; i++) {
        (*product)[i] = (*product)[i + 1];
    }

    (*n)--;

    if (*n == 0) {
        free(*product);
        *product = NULL;
    } else {
        *product = (Stock*) realloc(*product, (*n) * sizeof(Stock));
    }

    printf("Produto removido com sucesso!\n");
}

void editItem(Stock **product, int *n) {
    if (*n == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int id;
    printf("ID do produto para editar: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if ((*product)[i].id == id) {
            int opcs;

            printf("1. Editar nome\n");
            printf("2. Editar preco\n");
            printf("3. Editar quantidade\n");
            printf("4. Editar tudo\n");
            printf("Opcao: ");
            scanf("%d", &opcs);

            switch (opcs) {
                case 1:
                    printf("Novo nome: ");
                    scanf(" %49s", (*product)[i].product);
                    break;
                case 2:
                    printf("Novo preco: ");
                    scanf("%f", &(*product)[i].price); // %f, não %49s
                    clearBuffer();
                    (*product)[i].total = (*product)[i].quantity * (*product)[i].price;
                    break;
                case 3:
                    printf("Nova quantidade: ");
                    scanf("%d", &(*product)[i].quantity);
                    (*product)[i].total = (*product)[i].quantity * (*product)[i].price;
                    break;
                case 4:
                    printf("Novo nome: ");
                    scanf(" %49s", (*product)[i].product);

                    printf("Nova quantidade: ");
                    scanf("%d", &(*product)[i].quantity);

                    printf("Novo preco: ");
                    scanf("%f", &(*product)[i].price);
                    (*product)[i].total = (*product)[i].quantity * (*product)[i].price;
                    break;
                default:
                    printf("Opcao invalida.\n");
                    return;
            }

            printf("Editado com sucesso!\n");
            checkQuantity(product, n);
            return;
        }
    }

    printf("ID %d nao encontrado.\n", id);
}
void buscarItens(Stock *product, int n) {
    int encontrado = 0;
    char item [50];
    printf("Buscar itens: ");
    scanf("%s",&item);

    for (int i = 0; i < n; i++) {
        if (strcmp(product[i].product, item) == 0) {

            encontrado = 1;
            printf("\n%-5s %-20s %-10s %-12s %-12s\n", "ID", "PRODUTO", "QTD", "PRECO", "TOTAL");
            printf("------------------------------------------------------------\n");
            char price_fmt[12], total_fmt[12];
            //snprintf converte float para string formatada
            snprintf(price_fmt, sizeof(price_fmt), "R$%.2f", product[i].price);
            snprintf(total_fmt, sizeof(total_fmt), "R$%.2f", product[i].total);

            printf("%-5d %-20s %-10d %-12s %-12s\n",
                product[i].id,
                product[i].product,
                product[i].quantity,
                price_fmt,
                total_fmt);
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado");
    }

}


int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Stock *product = NULL;
    int opcs;
    int n = 0;
    int id = 1;

    do {
        printf("\n===MENU===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar items\n");
        printf("4. Editar item\n");
        printf("5. Buscar itens\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcs);
        clearBuffer();


        switch (opcs) {
            case 1: cadastration(&product, &n, &id);   break;
            case 2: delete(&product, &n);              break;
            case 3: list(product, n);                  break;
            case 4: editItem(&product, &n);            break;
            case 5: buscarItens(product, n);           break;
            case 0: printf("Saindo...\n");       break;
            default: printf("Opcao invalida.\n");
        }

    } while (opcs != 0);

    free(product);
    return 0;
}