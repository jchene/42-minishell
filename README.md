# MINISHELL

TO DO LIST

•	Update exit_codes dans flag_words() et expand $? par le code

•	Environement (shlvl, pwd, oldpwd)

•	ctrl-C: interactif: ok
			passif: affiche 2 fois $ au lie d'une
			heredoc: doit sortir de la commande

	ctrl-D: interactif: ok
			passif: ok
			heredoc: ok (oubli de \n avant le nouveau prompt?)

	ctrl-\: interactif: affiche le caractere au lieu de rien
			passif: ok (oubli du message core dump?)
			heredoc: affiche le caractere au lieu de rien

•	Norme & tests
