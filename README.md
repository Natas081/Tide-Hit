# Tide-Hit 

**Tide-Hit** é um jogo de sobrevivência estilo Arkanoid utilizando a biblioteca Raylib. O objetivo é sobreviver o máximo de tempo possível em um nível infinito onde a dificuldade aumenta progressivamente.

## Grupo:
* **Felipe Espínola**
* **Gabriel**
* **Natan Luis**

## Funcionalidades do Jogo
* **Modo Sobrevivência:** O nível nunca acaba. Novos blocos reaparecem aleatoriamente quando a tela esvazia.
* **Dificuldade Dinâmica:** A bola acelera a cada intervalo de tempo (60s, 40s, etc).
* **Sistema de HP nos Blocos:**
  * Cinza: 3 Hits (Difícil)
  * Azul Escuro: 2 Hits (Médio)
  * Lilás: 1 Hit (Fácil)
* **Top Scores:** Sistema de recordes salvo em arquivo binário, ordenado do maior para o menor.

## Requisitos Técnicos Atendidos
Requisitos:
- **Estruturas (structs):** Para Jogador, Bola, Blocos e Estado do Jogo.
- **Ponteiros:** Manipulação de estados e passagem de parâmetros.
- **Alocação Dinâmica:** Uso de `malloc` e `free` para criar e destruir blocos.
- **Listas Encadeadas:** Gerenciamento dos blocos ativos na tela.
- **Matrizes:** Mapeamento inicial do nível.
- **Arquivos:** Leitura e escrita de recordes (`scores.dat`).

## Instruções de Compilação e Execução

Ambiente Linux (ou WSL no Windows) utilizando `Make`.

### Pré-requisitos
* GCC
* Make
* Biblioteca Raylib instalada (`sudo apt install libraylib-dev`)

### Como rodar
1. Clone este repositório:
   ```bash
   git clone [https://github.com/Natas081/Tide-Hit.git](https://github.com/Natas081/Tide-Hit.git)

   ✅ RESUMO BEM FÁCIL: Como fizemos para rodar o jogo no Linux

Instalamos coisas que o Linux precisa para rodar jogos.
Tipo “programas de suporte”. Sem isso o computador não entende gráficos, janelas, sons etc.

Baixamos a Raylib, que é a “ferramenta” que seu jogo usa.

Compilamos a Raylib no Linux.
Isso é como “montar” a Raylib dentro do sistema para que o Linux saiba usar ela.

Instalamos a Raylib no sistema, para qualquer jogo poder usar.

Entramos na pasta onde seu jogo está, que fica dentro do Windows, mas acessamos pelo Linux.

Descobrimos qual arquivo tinha o main, ou seja, onde o jogo começa.

Compilamos seu jogo usando o Raylib, juntando seus arquivos .c e a Raylib.

Rodamos o jogo, e pronto — ele abriu normal no Linux.
