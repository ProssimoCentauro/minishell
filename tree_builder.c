#include "minishell.h"

// Funzione ausiliaria per costruire un sotto-albero di comandi
static t_token* build_command_subtree(t_token** tokens, int* index) {
    t_token* subtree_root = NULL;

    // Scendi fino a trovare un delimitatore o l'inizio dell'array
    while (*index >= 0) {
        if (tokens[*index]->type & (AND | OR | PIPE)) {
            break;
        }

        if (!subtree_root) {
            subtree_root = tokens[*index];
        } else {
            // Gestisci gruppi o concatenazioni di comandi
            tokens[*index]->right = subtree_root;
            subtree_root = tokens[*index];
        }

        (*index)--;
    }

    return subtree_root;
}

t_token* build_command_tree(t_token** tokens, int token_count) {
    //t_token* root = NULL;
    t_token* current = NULL;
    int i = token_count - 1;  // Iniziamo dall'ultimo token

    while (i >= 0) {
        // Priorità ai delimitatori logici (&&, ||)
        if (tokens[i]->type & (AND | OR)) {
            t_token* delimiter_node = tokens[i];

            // Trova l'operando destro (se non già impostato)
            if (!delimiter_node->right) {
                delimiter_node->right = current;
                current = NULL;
            }

            // Trova l'operando sinistro
            if (i > 0) {
                delimiter_node->left = build_command_subtree(tokens, &i);
            }

            current = delimiter_node;
        }
        // Gestione dei pipe
        else if (tokens[i]->type & PIPE) {
            t_token* pipe_node = tokens[i];

            // Il nodo corrente diventa figlio destro del pipe
            pipe_node->right = current;
            current = NULL;

            // Trova l'operando sinistro
            if (i > 0) {
                pipe_node->left = build_command_subtree(tokens, &i);
            }

            current = pipe_node;
        }
        // Gestione dei redirect
        else if (tokens[i]->type & (IN | OUT | APPEND | HEREDOC)) {
            t_token* redirect_node = tokens[i];

            // Collega il file di redirect
            if (i + 1 < token_count && tokens[i+1]->type & FILENAME) {
                redirect_node->right = tokens[i+1];
                i++;
            }

            // Il comando precedente diventa figlio sinistro
            if (current) {
                redirect_node->left = current;
                current = redirect_node;
            }
        }
        // Gestione dei comandi e gruppi
        else if (tokens[i]->type & (CMD | OPEN | CLOSE)) {
            if (!current) {
                current = tokens[i];
            }
        }

        i--;
    }

    return current;  // Restituisce la radice dell'albero
}


////////////////////////////////////////////////////////////////////
///

// Funzione per ottenere una stringa dal tipo di token
static const char* get_type_string(t_type type) {
    switch(type) {
        case CMD: return "CMD";
        case DELIMETER: return "DELIMETER";
        case AND: return "&&";
        case OR: return "||";
        case REDIRECT: return "REDIRECT";
        case PIPE: return "PIPE";
        case IN: return "<";
        case OUT: return ">";
        case APPEND: return ">>";
        case HEREDOC: return "<<";
        case FILENAME: return "FILENAME";
        case OPEN: return "(";
        case CLOSE: return ")";
        default: return "UNKNOWN";
    }
}

void print_command_tree(t_token* node, int depth) {
    // Controllo nodo nullo
    if (!node) {
        printf("Albero nullo\n");
        return;
    }

    // Buffer per l'indentazione
    char indent[128] = {0};
    for (int i = 0; i < depth; i++) {
        strcat(indent, "    ");
    }

    // Debug: stampa informazioni complete del nodo
    printf("%sNodo - Type: %s, SubType: %s\n",
           indent,
           type_to_str(node->type),
           type_to_str(node->sub_type));

    // Stampa del contenuto
    if (node->content) {
        printf("%sContent: %s\n", indent, (char*)node->content);
    }

    // Debug: stampa stato dei figli
    printf("%sLeft child: %p\n", indent, (void*)node->left);
    printf("%sRight child: %p\n", indent, (void*)node->right);

    // Stampa ricorsiva
    if (node->left) {
        printf("%s├── Left:\n", indent);
        print_command_tree(node->left, depth + 1);
    }

    if (node->right) {
        printf("%s└── Right:\n", indent);
        print_command_tree(node->right, depth + 1);
    }
}


/*
// Funzione ricorsiva per stampare l'albero
void print_command_tree(t_token* node, int depth) {
    // Controllo nodo nullo
    if (!node) return;

    // Indentazione per mostrare la gerarchia
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    // Stampa del contenuto del nodo
    if (node->content) {
        printf("%s: %s\n", 
               get_type_string(node->type), 
               (char*)node->content);
    } else {
        printf("%s\n", get_type_string(node->type));
    }

    // Stampa ricorsiva del sottoalbero sinistro
    if (node->left) {
        print_command_tree(node->left, depth + 1);
    }

    // Stampa ricorsiva del sottoalbero destro
    if (node->right) {
        print_command_tree(node->right, depth + 1);
    }
}*/
