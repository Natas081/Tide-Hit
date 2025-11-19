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