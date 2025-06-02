#include "minishell.h"

static t_token *create_token(t_token_type type, char *value) {
    t_token *new = malloc(sizeof(t_token));
    new->type = type;
    new->value = value;
    new->next = NULL;
    return new;
}
