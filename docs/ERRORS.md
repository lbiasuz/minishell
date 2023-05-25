- [x] minishell fechando após execução do programa
- [x] commandos por caminho absoluto não estão rodando
- [x] $? Não implementado
- [x] argumentos incorretos na presença de redirect
- [ ] heredoc completamente quebrado
- [ ] heredoc em conflito com minishell após sigint recebido
- [X] redirections antes do comando não funcionam
- [X] pipe não é fechada corretamente, congelando o grep e efins
- [x] builtin ainda não foram integrados
- [X] prompt sendo mostrado duas vezes no ctrl-c

TESTE RÉGUA 15/05

- [x] Comando por caminho absoluto não funciona
- [x] Comando não encontrado não printando erro e gerando invalid read
- [x] std fd sendo fechado ha ausência de pipe
- [X] EXIT não exitando com comandos extras
- [X] ECHO bypass de formatação "aparecendo"
- [x] $? Não implementado
- [ ] Falha ao abrir arquivo não exitando filho
- [x] Caso especial de redireção para builtins

https://www.thegeekstuff.com/2010/10/linux-error-codes/
errno list (above)
