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
/* v(i) = 1 se vertice ja foi visitado, 0 caso contrário */   /* TODO como setar valor ? */
var x{i in V, j in V}, binary;
var v{i in V} >= 0;


/* FUNCAO OBJETIVO */
minimize total: sum{(i,j) in E: i!=j} c[i,j] * x[i,j];


/* RESTRIÇÕES */

/* TODO Conservacao (eliminacao de subtours) */

/* Viajante sai de cada nó i exatamente uma vez, exceto no último */
s.t. leave{i in V}: sum{(i,j) in E: j!=n} x[i,j] = 1;

/* Viajante chega em cada nó j exatamente uma vez, exceto no primeiro */
s.t. enter{j in V}: sum{(i,j) in E: i!=0} x[i,j] = 1;

/* Restricao de precedencia */
s.t. precedence{i in V, j in V: i!=j and i!=0 and j!=n}: v[i] + 1 <= v[j];

/* TODO ? */
/* Restricao de que todo vertice foi visitado */
/*s.t. precedence{i in V}: v[i] = 1; */

solve;

/*printf "Caminho ótimo tem custo %d\n",
   sum{(i,j) in E} c[i,j] * x[i,j];
printf("De   Para   Custo\n");
printf{(i,j) in E: x[i,j]} "      %3d       %3d   %8g\n",
i, j, c[i,j];
*/


end;
