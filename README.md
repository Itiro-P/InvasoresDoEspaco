# Invasores do Espaço
## Sobre
Este é um clone do jogo Space Invaders do Atari. Aqui você controla uma nave e elimina os inimigos que aparecem em sua frente.

---

## Índice
- [Funcionalidades](#-funcionalidades)
- [Como Jogar](#-como-jogar)
- [Instalação](#-instalação)
- [Licença](#-licença)

---

## Funcionalidades:

- **Controle da Nave**: Movimente a nave para a esquerda e direita.
- **Sistema de Pontuação**: Pontue ao destruir inimigos.
- **Interface Gráfica**: Design moderno e responsivo.

---

## Como Jogar

1. **Movimentação**:
   - Use as teclas **←** (esquerda) e **→** (direita) para mover a nave.
2. **Objetivo**:
   - Destrua todos os inimigos antes que eles cheguem até você.
3. **Pontuação**:
   - Cada inimigo destruído aumenta sua pontuação.

---

## Instalação

As releases foram exportadas para o sistema Windows; assim seus usuários podem apenas baixar o jogo na página de releases, extrair e abrir o main.exe.

Caso use outro sistema operacional. Você precisará baixar o projeto e compilar para sua máquina. O projeto usa C++ 17, SFML 3.0 e no mínimo o Cmake 3.5 para rodar.

## Passos
1. Clone o repositório:
   ```bash
   git clone https://github.com/Ichiro-P/InvasoresDoEspaco.git

2. Navegue até o repositório do projeto:
   ```bash
   cd InvasoresDoEspaco

3. Compile com Cmake
   ```bash
   mkdir build && cd build
   cmake ..
   make

4. Execute o jogo:
   ```bash
   ./main

## Licença

The source code is licensed under Public Domain.
The Font is from [Google Fonts](https://fonts.google.com/specimen/Pixelify+Sans).
The Sprites are from [The Spriters Resource](https://www.spriters-resource.com/arcade/spaceinv/); and the icon is from [IconMark](https://www.flaticon.com/authors/iconmark). 
All credits to its owners.
