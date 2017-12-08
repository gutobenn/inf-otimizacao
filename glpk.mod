/* Número de nós */
param n, integer, >= 3;

/* CONJUNTOS */
set V := 1..n;                /* vertices */
set E, within V cross V;      /* arestas */

/* custo do nó i ao nó j */
param c{(i,j) in E};


/* VARIAVEIS DE DECISAO */
/* x(i,j) = 1 se aresta está no caminho, 0 caso contrário */
var x{(i,j) in E}, binary;


/* FUNCAO OBJETIVO */
minimize total: sum{(i,j) in E} c[i,j] * x[i,j];


/* RESTRIÇÕES */

/* viajante sai de cada nó i exatamente uma vez */
s.t. leave{i in V}: sum{(i,j) in E} x[i,j] = 1;

/* viajante chega em cada nó j exatamente uma vez */
s.t. enter{j in V}: sum{(i,j) in E} x[i,j] = 1;

/* TODO parte de conservacao (subtours) */

/* TODO nao repetir nó .. isso ja n ta inclusa nas 2 primeiras?*/

/* TODO restricao de precedencia */

/* TODO definir nó de partida e de chegada? */

solve;

/*printf "Caminho ótimo tem custo %d\n",
   sum{(i,j) in E} c[i,j] * x[i,j];
printf("De   Para   Custo\n");
printf{(i,j) in E: x[i,j]} "      %3d       %3d   %8g\n",
i, j, c[i,j];
*/
