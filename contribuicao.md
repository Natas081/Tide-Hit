#  Contribuindo para o Tidehit

Obrigado pelo interesse em contribuir para o **Tidehit**! Este é um jogo estilo *breakout* com física de maré dinâmica, desenvolvido em C puro utilizando a biblioteca [Raylib](https://www.raylib.com/).

Seja para corrigir um bug, adicionar uma nova mecânica aquática ou melhorar a arte, sua ajuda é bem-vinda.

##  Como Rodar o Projeto

Para contribuir, você precisa conseguir rodar o jogo na sua máquina.

### Pré-requisitos
* **Compilador C:** GCC (Recomendado).
* **Make:** Para automação da compilação.
* **Raylib:** A biblioteca gráfica.
    * *Linux:* `sudo apt install libraylib-dev` (ou equivalente na sua distro).
    * *Windows:* Recomenda-se usar o kit de desenvolvimento do w64devkit ou configurar as libs no MinGW.

### Compilando e Executando

1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/SEU-USUARIO/tidehit.git](https://github.com/SEU-USUARIO/tidehit.git)
    cd tidehit
    ```

2.  **Compile o jogo:**
    Basta rodar o comando `make` no terminal. O nosso `makefile` cuidará das dependências.
    ```bash
    make
    ```

3.  **Jogue:**
    ```bash
    ./tidehit
    ```

4.  **Limpando a build (caso necessário):**
    ```bash
    make clean
    ```

## Estrutura do Código



Para facilitar sua navegação:

* **`tidehit.c`**: Contém a função `main`. É responsável apenas por abrir a janela, inicializar o loop principal e fechar o jogo.
* **`game.h`**: O "cérebro" das definições. Aqui ficam todas as `structs` (Jogador, Bola, EstadoJogo), constantes (`#define`) e protótipos de funções. Se você criar uma nova struct, coloque-a aqui.
* **`game.c`**: Onde a mágica acontece. Contém toda a lógica de física (`atualizarBola`, `verificarColisoes`), renderização (`desenharTelaJogo`) e gerenciamento de memória.
* **`makefile`**: Script de compilação automatizada.

##  O que estamos procurando?

Aqui estão algumas ideias de *features* que queremos implementar (Roadmap):

- [ ] **Sons e Música:** Adicionar efeitos sonoros para impacto, power-ups e *splash* na água.
- [ ] **Ciclo Dia/Noite:** Alterar o gradiente do fundo conforme o tempo passa.
- [ ] **Novos Power-ups:** Bóias explosivas ou lasers.
- [ ] **Menu de Opções:** Controle de volume e dificuldade.
- [ ] **Portabilidade:** Melhorar o Makefile para compilar facilmente no Windows/MacOS.

##  Padrões de Código

Como estamos programando em C, a organização é vital para evitar vazamentos de memória (memory leaks).

1.  **Idioma:** Variáveis e comentários em **Português**.
2.  **Estilo:** Tente seguir o estilo existente (chaves na mesma linha ou linha abaixo, identação consistente).
3.  **Memória:** Se você usar `malloc`, certifique-se de que há um `free` correspondente na função `liberarEstado` ou onde for apropriado.
4.  **Raylib:** Evite lógica complexa dentro das funções `BeginDrawing()` e `EndDrawing()`. Deixe essa área apenas para funções de desenho (`Draw...`).

## Como enviar uma alteração (Pull Request)

1.  Faça um **Fork** deste repositório.
2.  Crie uma branch para sua feature (`git checkout -b feature/minha-nova-feature`).
3.  Commit suas mudanças (`git commit -m 'Adiciona suporte a joystick'`).
4.  Faça o Push para a branch (`git push origin feature/minha-nova-feature`).
5.  Abra um **Pull Request**.

---

Divirta-se codando e cuidado com a maré! 