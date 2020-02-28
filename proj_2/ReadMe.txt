Sobre
Este projeto foi realizado por Miguel Pinto up201806206 e Nuno Oliveira up201806525.
Nao contém dependéncias para além da STL do C++ e pode ser utilizado tanto em Windows como Linux.
Se utilizar em windows, para uma melhor experiencia e leitura é aconselhado aumentar a largura da consola manualmente.

Especificaçoes de implementação
-Class Clients
O VATnumber (usado como identificador unico do cliente) tem obrigatoriamente de conter 9 digitos e ser unico conforme a norma portuguesa.
Pode-se alterar todas as carateristicas do objeto cliente (exceto total de compras efetuadas, calculado automaticamente), incluindo devolver pacotes comprados.
-Class Packet
Após a primeira leitura os pacotes ficarão ordenados (crescente) por ID e partir desse ponto o ID de cada packet criado será a incrementação do último.
O ID de cada Packet nao pode ser alterado, nem o numero de pacotes reservados.
Ao alterar o numero total de lugares o programa nao aceita se for menor que o numero de lugares reservados.
De resto, tudo pode ser modificado.
-Class Address
DoorNumber apenas aceita numero inteiros positivos (excluindo o 0).
PostalCode apenas aceita o formato da norma portuguesa (XXXX-XXX, em que X representa um inteiro)
-Class Data
Nada relevante a apontar

Especificações gerais
-Em qualquer ponto de execuçao do programa o utilizador pode introduzir "!q" para cancelar a operação e voltar ao menu anterior
-Quando um cliente é criado, nao terá pacotes comprados. Da mesma forma o pacote terá 0 reservas.
-Foi implementada a possibilidade de um cliente devolver pacotes comprados.
No entanto para tal ser possivel tivemos que, no ato de compra, obrigar o cliente a reservar tantos lugares como o tamanho do seu agregado, visto que, devido ao formato de escrita, nao havia maneira de guardar quantas reservas foram feitas para cada compra.
-No fim de cada operação de alteração, criação e remoção o utilizador deparar-se-á com uma janela para confirmar (ou não) o que fez.
-Se nao forem utilizadas operações de alteração, criação e remoção, ao fechar o programa nao escreve tudo de novo. Pelo contrário se alguma foi, de facto, utilizada ao fechar, o o programa pergunta ao utilizador se quer de facto guardar todas as alterações o cancelar e manter os dados anteriores.
-Para pesquisar lugares por destino o programa nao é case sensitive (ex: o utilizador dá input "porto" e o programa dará output aos packets com destino "Porto", "porto", etc).
-As vendas da agencia e o dinheiro feito aparecerá no menu inicial juntamente com o resto dos dados da agência. O codigo foi escrito de modo a que estes valores sejam adquiridos apenas pelo vetor dos pacotes.
-Quando necessaria a pesquisa de pacotes, é feita por pesquisa binária para aumentar performance.



