# MINISHELL 42

# NOTES

1. les commandes echo, export, etc fonctionnent independement de la case.
2. la commande exit et ctrl-D affiche le message "exit" sur le prompt
7. ctrl+C creer un new prompt
3. ouvrir un nouveau bash dans le bash lors de l'appel de ./minishell dans le minishell
4. echo sans arguments doit gerer l'entree standard
5. gerer le flag -c dans l'executable (./minishell -c ..."
6. pourquoi multi_pipeline en static ne compile pas ?
7. verif le cas des tabs
8. gerer les signaux
9. gerer le `?`
10. return (status);
11. if (isatty(0))
12. Bien verifier que le fichhier file existe dans echo < file
13. echo message 1 >> file message 2


# FORBIDDEN SPECIAL PARAMETERS 

$#
$$
$*
$-
$@
$0
$!

echo $varbar
echo ${var}bar

# RETRO INGENEERING

1. A quoi sert sg()->stop;
2. echo yolo |


# TO DO

1. checher les lines incorectes
exemples:
>	| echo hello
>	echo hello | | wc
>	cat <
> 	echo "'hello"'



# DOC

https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/