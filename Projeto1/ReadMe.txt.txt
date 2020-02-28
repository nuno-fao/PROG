Primeiramente para o programa funcionar os ficheiros "clients.txt" e "packs.txt" tem de existir, nem que vazios.
Nao usei structs para datas e moradas pelo facto de originalmente como ia fazer o algoritmo era mais simples facto de o algoritmo de leitura ficar mais simples. Quando me lembrei duma alternativa ja era um pouco tarde para voltar atras.
Pode-me ter passado algum problema envolvendo a mistura de getlines e >>.
A meio o visual studio esteve a dar um problema assinalando os "cin" e "cout" todos como ambiguos mas desaparecia e aparecia constantemente, nao sei ao certo porque.
Devido a uma ma gestao de tempo e organizaçao do trabalho em geral nao consegui comprir todos os objetivos ficando em falta pesquisar os pacotes por data de começo e fim, e visualizar os pacotes vendidos a um cliente especifico.
No entanto, acho que dos 8 objetivos o todos os outros que nao mencionei foram implementados.
No que diz respeito ao que ainda podia melhor no programa:
-verificar se os ficheiros existem antes de os tentar abrir e dar fatal error.
-como é obvio, acabar os objetivos.
-prevençao do erro no sentido em que, no fim do programa se der erro a meio da escrita, tudo que seria escrito depois do erro seria perdido. Para melhorar isto estava a pensar criar um ficheiro para guardar o conteudo inicial antes de altera-lo mas, novamente por culpa minha, nao tive tempo.
-ordenar de alguma maneiras a informação para poder, quando necessario, fazer pesquisa binaria o que aumenta muito a performance do programa com databases maiores.
-nas funçoes de alterar packs/clientes nao da para alterar todos os membros(packs comprados, etc.).
-facilitar a navegaçao pelos menos tornando-a mais intuitiva e limpar a command line quando necessario.
-"aprender" a comentar o codigo de forma eficiente visto que passei demasiado a lembrar-me como defini determinada função e o porque de certos statements, etc.