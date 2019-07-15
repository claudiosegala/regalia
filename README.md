# Regalia

Um jogo de batalha em plataforma multiplayer local de até 4 jogadores. Vence o jogador que alcançar 3 vitórias. A temática é de mágia com dois personagens (Mister N e Gótica).

![tela instruções](data/initial.jpeg)


## História

Um poderoso mago, autor e detentor do livro supremo de magia morre. Por razões emocionais, o livro foi enterrado junto com ele, fato que infelizmente não passou despercebido por alguns magos. Se especula que o livro possui encantamento tão poderosos que quem conseguisse tê-lo se tornaria o novo mago mais poderoso. Logo, diversos magos do mundo começaram a se movimentar para conseguir tal poder. Uma nova era no mundo da magia começou.

Preocupado, um monge atlético, em busca do equilíbrio no mundo busca assegurar o controle do livro, para evitar que caia nas mãos do mal. Ao mesmo tempo, Sebastião, o alquimista, já velhinho e muito saudosista com o passado vê aí uma oportunidade de recuperar a sua juventude. Mr N, o maior ilusionista do mundo, atualmente em dificuldades financeiras acredita que o livro pode ajudá-lo a desenvolver o truque perfeito. Todos se movimentam até a Necrópole lugar favorito na vida da Gótica, uma jovem com poderes das trevas. 

Para a infelicidade deles, todos acharam o túmulo do grande mago ao mesmo tempo, porém era o grande mago havia colocado uma armadilha. Todos foram teleportados para dentro do livro e agora somente um deles sairá com vida.

## Observações

+ Cada partida dura 45 segundos, se estender, balas se tornam invencíveis para acelerar a morte dos jogadores
+ Existem 3 tipos de balas, o primeiro tipo não exige carregamento, o segundo exige 1s e o terceiro exige 2s
+ Balas caem de nível quando refletem na parede
+ Quanto maior o nível da bala, mais rápida ela é
+ Se carregar o tiro por mais de 3s, se perde o carregamento
+ Balas não se anulam
+ Não é possível se acertar

## Como Jogar

O modo preferível para se executar seria usando Visual Studio. Visto que o projeto foi desenvolvido utilizando o mesmo, mas em caso de não tê-lo configurado na sua máquina, basta seguir com as instruções abaixo.

Considerando que você já tem o SDL2 instalado e configurado. Conecte no mínimo dois controles de xbox (360 ou One) ou PlayStation (PS2, PS3 ou PS4).

Para jogar basta executar o seguinte:

```bash
$ cd regalia
$ make run
```

### Instruções de como jogar o jogo

Uma vez o jogo iniciado, se encontrará na tela inicial, pressione A para ir para o menu. Use os stick para escolher as opções e aperte A para selecionar. Uma vez que selecionar para jogar, será redirecionado para a tela de seleção de personagem. Segue a baixo a página de seleção de personagens com as instruções de como jogar.

![tela instruções](data/instructions.jpeg)

## Inspiração

Esse jogo foi fortemente inspirado em towerfall, mas com uma pegada estratégida um pouco diferente utilizando tiros mágicos que refletem na parede.

![tela instruções](data/game.jpeg)

## Membros

+ Claudio Segala Rodrigues Silva Filho - 150032552
  + Responsável principalmente pela colisão entre objetos, física e lógica dos estados
+ Gustavo Henrique Fernandes Carvalho - 14/0021671
  + Responsável principalmente pelas animações e pelos tile maps.
+ Ricardo Arôso Mendes Kury - 14/0161082
  + Responsável principalmente pela física, efeitos sonoros e movimentações e configuração dos gamepafs
