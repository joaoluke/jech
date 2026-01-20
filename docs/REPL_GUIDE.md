# Guia do REPL Interativo Jech

O REPL (Read-Eval-Print Loop) do Jech oferece uma interface interativa para testar e experimentar com a linguagem.

## Recursos de Navegação

### Histórico de Comandos
- **Seta ⬆️ (Para Cima)**: Navega para comandos anteriores no histórico
- **Seta ⬇️ (Para Baixo)**: Navega para comandos mais recentes no histórico
- **Ctrl+R**: Busca reversa no histórico (funcionalidade padrão do readline)

### Edição de Linha
- **Seta ⬅️ (Esquerda)**: Move o cursor para a esquerda
- **Seta ➡️ (Direita)**: Move o cursor para a direita
- **Ctrl+A**: Move o cursor para o início da linha
- **Ctrl+E**: Move o cursor para o final da linha
- **Ctrl+K**: Deleta do cursor até o final da linha
- **Ctrl+U**: Deleta do cursor até o início da linha
- **Ctrl+W**: Deleta a palavra anterior
- **Ctrl+L**: Limpa a tela

### Comandos Especiais
- `exit` ou `quit`: Sai do REPL
- `help`: Mostra ajuda sobre comandos e sintaxe
- `clear`: Limpa todas as variáveis e arrays da memória

## Exemplos de Uso

```bash
$ ./jech
Jech Interactive Shell v0.1.0
Type 'exit' or 'quit' to leave, 'help' for help, 'clear' to clear variables
>>> keep x = 10;
>>> say(x);
10
>>> # Pressione ⬆️ para recuperar "say(x);"
>>> say(x);
10
>>> keep numbers = [1, 2, 3, 4, 5];
>>> numbers.map(* 2);
>>> say(numbers);
[2.00, 4.00, 6.00, 8.00, 10.00]
>>> # Pressione ⬆️ múltiplas vezes para navegar no histórico
>>> exit
Goodbye!
```

## Tecnologia

O REPL do Jech utiliza a biblioteca **GNU Readline**, que oferece:
- Edição de linha avançada
- Histórico de comandos persistente durante a sessão
- Atalhos de teclado padrão do Emacs
- Suporte completo para navegação com setas

## Dicas

1. **Reutilize comandos**: Use ⬆️ para recuperar comandos anteriores em vez de digitá-los novamente
2. **Edite comandos**: Recupere um comando com ⬆️ e edite-o antes de executar
3. **Experimente livremente**: Use `clear` para resetar o estado e começar do zero
4. **Busca rápida**: Use Ctrl+R e digite parte de um comando para buscá-lo no histórico
