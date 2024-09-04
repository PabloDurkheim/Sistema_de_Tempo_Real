# Tarefa 3.1 - Problema dos 4 Trens

**Objetivo**: Implementar um programa que simule a dinâmica de quatro trens em um circuito de trilhos utilizando conceitos de programação concorrente. O programa deve garantir que não ocorram colisões entre os trens, que os trilhos compartilhados sejam gerenciados de forma segura, e que não haja deadlocks. Além disso, deve haver uma interface para controlar as velocidades dos trens e outra para visualizar a posição de cada trem em tempo real.
## Requisitos da Tarefa

1 - Movimentação Independente dos Trens:

* Cada trem se move independentemente em seu próprio circuito de trilhos, respeitando o sentido indicado.

2 - Prevenção de Colisões:

* Garantir que não haja mais de um trem simultaneamente no mesmo segmento de trilho, especialmente nos trilhos compartilhados (L3, L4, L7, L9).

3 - Prevenção de Deadlocks:

* Implementar mecanismos que evitem deadlocks, onde dois ou mais trens poderiam ficar esperando indefinidamente para acessar um trilho compartilhado.

4 - Interface de Controle:

* Deve haver uma interface que permita ao usuário ajustar as velocidades dos trens.

5 - Visualização em Tempo Real:

* O programa deve incluir uma interface gráfica que mostre a posição de cada trem a cada instante.

## Conceitos de Programação Concorrente Aplicados

Threads:

* Uma thread dedicada para cada trem, uma para o painel de controle e outra para a visualização dos trens.

Região Crítica e Semáforos:

* Uso de semáforos para garantir que somente um trem acesse um trilho compartilhado por vez, evitando colisões e garantindo a exclusão mútua.

Sincronização:

* Sincronização entre as threads para garantir que as operações críticas sejam executadas de forma segura.

## Detalhes de Implementação

Simulação da Movimentação:

* Os trens se movem ao longo dos trilhos representados por retângulos na tela, mudando de direção ao alcançar as extremidades.

Controle de Velocidade:

* Cada trem tem sua velocidade controlada por um slider, permitindo ajustes dinâmicos durante a simulação.

Semáforos para Controle de Acesso:

* Uso de semáforos para cada trem, garantindo que apenas um trem possa acessar um trilho compartilhado de cada vez.

Thread de Colisão:

* Uma thread dedicada para gerenciar a prioridade e liberar semáforos conforme necessário, evitando conflitos entre os trens.
