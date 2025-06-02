#include "minishell.h"

static t_cmd *new_cmd(void) {
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->args = NULL;
    cmd->redirections = NULL;
    cmd->next = NULL;
    return cmd;
}
