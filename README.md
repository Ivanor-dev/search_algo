# APS2 – Algoritmos de Ordenação

Implementação em C de cinco algoritmos de ordenação e programa de experimentos que mede o tempo de execução em diferentes tamanhos e tipos de array.

**Algoritmos:** Insertion Sort, Selection Sort, Quick Sort (Hoare), Quick Sort (Lomuto) e Merge Sort.

**Tipos de array:** aleatório, poucos valores únicos (10 valores), ordenado e ordem inversa.

**Tamanhos:** 1.000, 10.000, 100.000 e 1.000.000 de elementos.

## Estrutura

```
aps2/
├── CMakeLists.txt
├── main.c              # gera as entradas, executa, mede o tempo e grava o CSV
├── sorts.h             # declarações das funções de ordenação
├── insertion_sort.c
├── selection_sort.c
├── quick_sort.c        # Hoare e Lomuto
└── merge_sort.c
```

## Requisitos

- CMake 3.10 ou superior
- Compilador C (GCC, Clang ou MinGW)

## Compilar

Na pasta `aps2`:

```bash
cmake -S . -B build
cmake --build build
```

O `CMakeLists.txt` usa o modo **Release** por padrão (otimizações ligadas), necessário para medir o tempo corretamente. Se preferir informar explicitamente:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

## Executar

```bash
./build/aps2
```

No Windows com MinGW: `.\build\aps2.exe`.

Com Visual Studio (MSVC), compile com `cmake --build build --config Release` e execute `.\build\Release\aps2.exe`. Observação: o `main.c` usa `clock_gettime`, que não existe no MSVC; use GCC/MinGW/Clang ou troque a função de tempo.

O programa imprime a tabela de tempos na tela e grava `resultados.csv` **na pasta em que for executado**. Para guardar o CSV junto ao projeto, execute a partir da pasta `aps2`:

```bash
./build/aps2
```

## Saída

`resultados.csv`, com as colunas:

| algoritmo | tipo | tamanho | tempo_s |
|-----------|------|---------|---------|

Combinações não executadas ficam com `tempo_s` vazio.

## Ajustes

**Tamanhos, repetições e tipos:** em `main.c`, `TAMANHOS` e a variável `reps` (média de 5 execuções para n ≤ 10.000 e 1 execução acima disso).

**Combinações puladas:** por padrão, Insertion e Selection não rodam com n = 1.000.000, e o Quick Sort (Lomuto) não roda com poucos valores únicos nesse tamanho, pois são quadráticos e levam minutos. Para executá-los, aumente `LIMITE_QUADRATICO` e ajuste a função `deve_pular()` em `main.c`. A execução completa leva cerca de 25 minutos.

## Detalhes de implementação

- **Quick Sort (Hoare):** pivô no elemento central.
- **Quick Sort (Lomuto):** pivô aleatório, movido para o fim do trecho.
- **Recursão do Quick Sort:** feita apenas sobre a partição menor; a maior vira laço (profundidade O(log n), sem estouro de pilha).
- **Merge Sort:** sentinelas `INT_MAX` e vetores auxiliares alocados com `malloc`.
- **Verificação:** após cada execução o programa confere se o array ficou ordenado e avisa em caso de erro.
- **Reprodutibilidade:** os arrays são gerados com semente fixa e todos os algoritmos ordenam cópias dos mesmos dados.

## Limpar

```bash
rm -rf build resultados.csv
```