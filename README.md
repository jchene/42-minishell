# MINISHELL

TO DO LIST

- [ctrl + backslash]

    •	interactif -> affiche le caractere au lieu de rien

    •	passif -> ??

    •	heredoc -> affiche le caractere au lieu de rien


- tests - leaks - exit_codes

    •	[cmd] -> valgrind --leak-check=full --track-fds=yes --vgdb-error=0 ./minishell

    •	[https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0]

    •	[sujet correction]


- norme

void	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args && args[1])
	{
		if (args && args[0] && args[1] && args[2])
		{
			printf("bash: exit: too many arguments\n");
			return ;
		}
		exit_code = ft_atoi(args[1]);
		exit_code = exit_code % 256;
		if (exit_code < 0)
		{
			exit_code *= -1;
			exit_code = 256 - exit_code;
		}
	}
	(data())->exit_code = exit_code;
	if (ft_strcmp((data())->p_start->str, "exit"))
		data()->stop = 1;
}
