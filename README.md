# MatrizRain

Animação estilo **Matrix Rain** no terminal, escrita em C.

## Funcionalidades

- Geração de colunas com caracteres aleatórios (`0` e `1`)
- Efeito de rastro com intensidade de verde decrescente
- Velocidade aleatória por coluna
- Adaptação automática ao redimensionar o terminal

## Requisitos

- Compilador C (`gcc` ou `clang`)
- Terminal com suporte a:
  - sequências ANSI (cores e posicionamento de cursor)
  - cores true color (24-bit), para melhor resultado
- Sistema Unix-like (Linux/macOS) **ou** Windows via WSL/MSYS2

> Observação: o código usa `unistd.h` e `sys/ioctl.h`, então pode não compilar no CMD/PowerShell puro sem ambiente compatível POSIX.

## Como compilar

### Linux/macOS (gcc)

```bash
gcc -O2 -Wall -Wextra -o main main.c
```

### Linux/macOS (clang)

```bash
clang -O2 -Wall -Wextra -o main main.c
```

### Windows (WSL)

No terminal do WSL, dentro da pasta do projeto:

```bash
gcc -O2 -Wall -Wextra -o main main.c
```

## Como executar

```bash
./main
```

Para encerrar, use `Ctrl + C`.

## Estrutura

- `main.c`: código-fonte principal da animação
- `.gitignore`: arquivos ignorados pelo Git
