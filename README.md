# ControleDeEstoque
# Controle de Estoque

Sistema de gerenciamento de estoque em C com alocação dinâmica de memória.

## Funcionalidades

- Cadastrar produtos com nome, quantidade e preço
- Listar todos os produtos em formato de tabela
- Editar nome, preço ou quantidade de um produto
- Remover produtos manualmente
- Buscar produto pelo nome
- Remoção automática de produtos com estoque zerado

## Como compilar

```bash
gcc main.c -o estoque
```

## Como executar

```bash
./estoque
```

## Menu

```
===MENU===
1. Cadastrar item
2. Remover item
3. Listar items
4. Editar item
5. Buscar itens
0. Sair
```

## Estrutura do projeto

```
.
├── main.c
└── README.md
```

## Struct principal

```c
typedef struct {
    int id;
    char product[50];
    int quantity;
    float price;
    float total;
} Stock;
```

## Detalhes técnicos

- Memória alocada dinamicamente com `malloc`/`realloc` conforme produtos são adicionados ou removidos
- IDs gerados de forma incremental e não reutilizados após remoção
- A função `checkQuantity` percorre o estoque após edições e remove automaticamente qualquer produto com quantidade `<= 0`
- Saída formatada com colunas de largura fixa usando `snprintf` + `printf`

## Requisitos

- GCC ou qualquer compilador C padrão (C99+)
- Sistema Linux/Unix ou Windows com MinGW
