## PASMO - ASSEMBLADOR Z80 MULTIPLATAFORMA

(C) 2004-2022 Julián Albo  
Uso e distribuição permitidos sob os termos da licença GPL v.3.

### Para baixar atualizações ou obter mais informações:

[https://pasmo.speccy.org/](https://pasmo.speccy.org/)

- - -

### Para compilar o projeto:

#### Configurar e compilação:
    
`cmake -S . -B build`
    
`cmake --build build`

#### Configuração e compilação alternativa (usando Ninja):
`cmake -Wno-dev --fresh -B build -G Ninja`

`ninja -C build`
    
#### Executar os testes automáticos via CTest:
    
`cd build && ctest --output-on-failure`
    
#### Executar testes customizados manualmente:
    
`tests/test_cli.sh`
    

### Documentação

A documentação está disponível apenas em inglês no arquivo `pasmodoc.html`, incluído neste pacote, ou no site do Pasmo. Também estão disponíveis arquivos `.asm` de exemplo no pacote de fontes.

- - -

## Para montar (assemble):

`pasmo [ opções ] arquivo.asm arquivo.bin [ arquivo.simbolos [ arquivo.publicos ] ]`

### Opções:

| **Opção** | **Descrição** |
| --- | --- |
| `-d` | Mostrar informações de depuração durante a montagem. |
| `-1` | Mostrar informações de depuração também na primeira passagem. |
| `-v` | Modo verboso. Exibe o progresso durante a montagem. |
| `-I` | Adiciona um diretório à lista de busca para arquivos em `INCLUDE` e `INCBIN`. |
| `--bin` | Gera o arquivo objeto em formato binário puro, sem cabeçalho. |
| `--hex` | Gera o arquivo objeto no formato Intel HEX. |
| `--prl` | Gera o arquivo objeto no formato PRL, adequado para RSX do CP/M Plus. |
| `--cmd` | Gera o arquivo objeto no formato CMD do CP/M 86. |
| `--plus3dos` | Gera o arquivo objeto com cabeçalho PLUS3DOS (disco Spectrum). |
| `--tap` | Gera um arquivo `.tap` para emuladores Spectrum (imagem de fita). |
| `--tzx` | Gera um arquivo `.tzx` para emuladores Spectrum (imagem de fita). |
| `--cdt` | Gera um arquivo `.cdt` para emuladores Amstrad CPC (imagem de fita). |
| `--tapbas` | Igual a `--tap`, mas adiciona um carregador Basic. |
| `--tzxbas` | Igual a `--tzx`, mas adiciona um carregador Basic. |
| `--cdtbas` | Igual a `--cdt`, mas adiciona um carregador Basic. |
| `--amsdos` | Gera o arquivo objeto com cabeçalho Amsdos (disco Amstrad CPC). |
| `--msx` | Gera o arquivo objeto com cabeçalho para uso com `BLOAD` no MSX Basic. |
| `--public` | A listagem da tabela de símbolos incluirá apenas os símbolos declarados como `PUBLIC`. |
| `--name` | Nome para o cabeçalho nos formatos que o utilizam. Se não especificado, será usado o nome do arquivo. |
| `--err` | Direciona as mensagens de erro para a saída padrão em vez da saída de erro. |
| `--nocase` | Torna os identificadores insensíveis a maiúsculas e minúsculas. |
| `--alocal` | Modo autolocal: rótulos que começam com `_` são locais e seu escopo termina no próximo rótulo global. |
| `-B`, `--bracket` | Modo apenas colchetes: os parênteses são reservados para expressões. |
| `-E`, `--equ` | Pré-define um rótulo. |
| `-8`, `--w8080` | Exibe um aviso ao usar instruções Z80 que não existem no 8080. |
| `--86` | Gera código 8086. |
| `--sdrel` | Gera arquivos objeto no formato .rel do linker SDCC. |
| `--trs` | Gera arquivos objeto no formato CMD para TRS-80. |

**Nota:** Se nenhuma opção de formato de saída for especificada, será assumido `--bin`.

- - -

### Informações de Depuração

As informações de depuração são enviadas para a saída padrão, enquanto as mensagens de erro são enviadas para a saída de erro.

- - -

**Comentários e críticas:** julian.notfound@gmail.com