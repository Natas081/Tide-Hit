# Tide-Hit 

**Tide-Hit** é um jogo de sobrevivência estilo Arkanoid utilizando a biblioteca Raylib. O objetivo é sobreviver o máximo de tempo possível em um nível infinito onde a dificuldade aumenta progressivamente.

## Grupo:
* **Felipe Espínola**
* **Gabriel Victor**
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

# Instruções de Compilação e Execução

Ambiente **Linux** (ou WSL no Windows) utilizando `Make`.

### Pré-requisitos
* **GCC**
* **Make**
* **Git**

### Como Rodar (Sequência Exata)

Siga estes 9 passos no terminal, executando um comando por vez:

#### 1. Preparação do Ambiente

* **Passo 1:** Atualizar o sistema:
    ```bash
    sudo apt install
    ```
* **Passo 2:** Atualizar o sistema:
    ```bash
    sudo apt update
    ```

* **Passo 3:** Instalar ferramentas essenciais (compiladores e bibliotecas gráficas):
    ```bash
    sudo apt install build-essential git libx11-dev xserver-xorg-dev xorg-dev
    ```

#### 2. Download e Compilação

* **Passo 4:** Clonar o repositório:
    ```bash
    git clone https://github.com/Natas081/Tide-Hit
    ```
* **Passo 5:** Entrar na pasta do jogo:
    ```bash
    cd Tide-Hit
    ```
* **Passo 6:** Compilar a Raylib (entrar na pasta):
    ```bash
    cd raylib/src
    ```
* **Passo 7:** Compilar a Raylib (executar make):
    ```bash
    make
    ```
* **Passo 8:** Retornar à pasta raiz:
    ```bash
    cd ../..
    ```
* **Passo 9:** Compilar o jogo principal:
    ```bash
    make
    ```

#### 3. Execução

* **Passo 10:** Iniciar o jogo:
    ```bash
    ./tidehit
    ```
