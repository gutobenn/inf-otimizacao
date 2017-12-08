/* Número de nós */
param n, integer, >= 3;

/* CONJUNTOS */
set V := 1..n;                /* vertices */
set E, within V cross V;      /* arestas */

/* custo do nó i ao nó j */
param c{(i,j) in E};

/* Pares de precedencia*/
param p{(i,j) in E};

/* VARIAVEIS DE DECISAO */
/* x(i,j) = 1 se aresta está no caminho, 0 caso contrário */
/* v(i) = 1 se vertice ja foi vizitado, 0 caso contrário */
var x{(i,j) in E}, binary;
var v{(i) in V} >= 0;


/* FUNCAO OBJETIVO */
minimize total: sum{(i,j) in E: i!=j} c[i,j] * x[i,j];


/* RESTRIÇÕES */

/* viajante sai de cada nó i exatamente uma vez */
s.t. leave{i in V}: sum{(i,j) in E: i!=0} x[i,j] = 1;

/* viajante chega em cada nó j exatamente uma vez */
s.t. enter{j in V}: sum{(i,j) in E: j!=n} x[i,j] = 1;

/* Partir do nó 0 */
s.t. departure{j in V: j!=0}: sum{(0,j) in E} x[0,j] = 1;

/* Chegar no nó N */
s.t. arrival{i in V: i!=N}: sum{(i,N) in E} x[i,N] = 1;

/* Restricao de precedencia (ta certa?)*/
s.t. precedence{i in N, j in V: i!=j and i!=0 and j!=N}: v[i] + 1 <= v[j];

/* TODO parte de conservacao (subtours) */

/* TODO confirmar que n ta dando loop */

solve;

/*printf "Caminho ótimo tem custo %d\n",
   sum{(i,j) in E} c[i,j] * x[i,j];
printf("De   Para   Custo\n");
printf{(i,j) in E: x[i,j]} "      %3d       %3d   %8g\n",
i, j, c[i,j];
*/
