# Otimização
Sequential Ordering Problem com Busca Tabu

## Instance to dat
No diretório raíz

Compilação: g++ instanceToDat.cpp -o instanceToDat

Utilização: ./instanceToDat < instances/ESC07.sop > instances/ESC07.dat
onde instances/ESC07.sop é o caminho relativo para o arquivo da instância  e instances/ESC07.dat o caminho relativo onde a saída será salva.

## SOP main:
Os comandos abaixo devem ser executados na pasta src.

Compilação: g++ main.cpp -o main

Utilização: ./main ../instances/ESC07.sop 2
onde ../instances_ESC07.sop é o caminho relativo para o arquivo da instância e 2 é o identificador da semente aleatória a ser utilizada.

O número de iterações limite é definido em uma constante logo no início do arquivo main.cpp

## Executar GLPK
Na pasta raíz, executar o seguinte comando para resolver o problema instances/ESC07.dat utilizando o GLPK e salvar a saída no arquivo.txt, com limite de uma hora
glpsol -m glpk.mod -d instances/ESC07.dat -o saida.txt --tmlim 3600
