# MINISHELL 42

# OPERATOR TAKEN AS CHAR

&&

# FORBIDDEN SPECIAL PARAMETERS 


||
;
\
$#
$$
$*
$-
$@
$0
$!



-----------------------------------------------------------

# DISABLE VALGRIND READLINE LEAKS
alias minishell_leaks='valgrind --leak-check=full --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell'

--track-fds=yes 

# NOTES

1. les commandes echo, export, etc fonctionnent independement de la case.
5. gerer le flag -c dans l'executable (./minishell -c ..."


# TO DO

[ ] Set fd=2 in error messages
[ ] CLEAN EXIT ! + leaks
[ ] display var env in heredoc
[X] Bien verifier que le fichhier file existe dans echo < file
[ ] echo message 1 >> file message 2

1. checher les lines incorectes
exemples:
>	| echo hello
>	echo hello | | wc
>	cat <
> 	echo "'hello"'

# DOC

https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/