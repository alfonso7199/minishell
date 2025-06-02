
int error_msg(char *msg)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, "\n", 1);
    return (false);
}

int ft_error(int error, t_tools *tools)
{
    if (error == 0)
        error_msg("syntax error near unexpected token 'newline'");
    else if (error == 1)
        error_msg("memory error: unable to assign memory");
    else if (error == 2)
        error_msg("syntax error: unable to locate closing quotation");
    else if (error == 3)
        error_msg("Parser problem");
    else if (error == 4)
        error_msg("Failed to create pipe");
    else if (error == 5)
        error_msg("Failed to fork");
    else if (error == 6)
        error_msg("outfile: Error");
    else if (error == 7)
        error_msg("infile: No such file or directory");
    else if (error == 8)
        error_msg("Path does not exist");
    else if (error == 9)
        error_msg("exit: too many arguments");
    else if (error == 10)
        error_msg("cd: no such file or directory");
    else
        error_msg("Unknown error");        
    if (tools)
        reset_tools(tools);
    return (EXIT_FAILURE);
}