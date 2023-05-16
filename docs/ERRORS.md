- [x] minishell fechando após execução do programa
- [ ] commandos por caminho absoluto não estão rodando
- [ ] $? Não implementado
- [ ] argumentos incorretos na presença de redirect
- [ ] heredoc completamente quebrado
- [ ] heredoc em conflito com minishell após sigint recebido
- [X] redirections antes do comando não funcionam
- [X] pipe não é fechada corretamente, congelando o grep e efins
- [x] builtin ainda não foram integrados
- [X] prompt sendo mostrado duas vezes no ctrl-c

TESTE RÉGUA 15/05

- [x] Comando por caminho absoluto não funciona
- [ ] Comando não encontrado não printando erro e gerando invalid read
- [x] std fd sendo fechado ha ausência de pipe
- [ ] EXIT não exitando com comandos extras
- [ ] ECHO bypass de formatação "aparecendo"
- [ ] $? Não implementado

https://www.thegeekstuff.com/2010/10/linux-error-codes/
errno list (above)