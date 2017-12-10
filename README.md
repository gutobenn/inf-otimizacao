# Otimização

Sequential Ordering Problem com Busca Tabu

## TODO
- Como compilar e usar
- verificar TODOs

## Instance to dat
e.g:
g++ instanceToDat.cpp -o instanceToDat
./instanceToDat < instances/ESC07.sop > instances/ESC07.sop

## Executar GLPK
glpsol -m glpk.mod -d instances/ESC07.dat -o saida.txt --tmlim 120
