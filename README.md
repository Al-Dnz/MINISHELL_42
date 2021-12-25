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

# NOTES

1. les commandes echo, export, etc fonctionnent independement de la case.
5. gerer le flag -c dans l'executable (./minishell -c ..."


# TO DO

11. CLEAN EXIT ! + leaks
12. Bien verifier que le fichhier file existe dans echo < file
13. echo message 1 >> file message 2

1. checher les lines incorectes
exemples:
>	| echo hello
>	echo hello | | wc
>	cat <
> 	echo "'hello"'

# DOC

https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/