/* Número de nós */
param n, integer, >= 3;

/* CONJUNTOS */
set V := 0..n-1;                /* vertices */
set E, within V cross V;      /* arestas */

/* custo do nó i ao nó j */
/*param c{(i,j) in E};*/
param c{i in V, j in V};

/* Pares de precedencia*/
/*param p{(i,j) in E};*/
param p{i in V, j in V};

/* VARIAVEIS DE DECISAO */
/* x(i,j) = 1 se aresta está no caminho, 0 caso contrário */
/* v(i) = 1 se vertice ja foi visitado, 0 caso contrário */   /* TODO como setar valor ? */
var x{i in V, j in V}, binary;
var v{i in V} binary;

/* FUNCAO OBJETIVO */
/*minimize total: sum{(i,j) in E: i!=j} c[i,j] * x[i,j];*/
minimize total: sum{i in V, j in V: i!=j} c[i,j] * x[i,j];


/* RESTRIÇÕES */

/* TODO Conservacao (eliminacao de subtours) */

/* Viajante sai de cada nó i exatamente uma vez, exceto no último */
s.t. leave{i in V: i!=n-1}: sum{j in V: i!=j} x[i,j] = 1;

/* Viajante nunca sai do último nó */
s.t. leave_last{j in V}: x[n-1, j] = 0;

/* Viajante chega em cada nó j exatamente uma vez, exceto no primeiro */
s.t. enter{j in V: j!=0}: sum{i in V: i!=j} x[i,j] = 1;

/* Viajante nunca chega no primeiro nó */
s.t. enter_first{i in V}: x[i,0] = 0;

/* Viajante tem que ir para outro nó */
s.t. visit_other_node{i in V}: x[i,i] = 0;

s.t. visit_all_nodes{i in V}: v[i] = 1;

/*s.t. c6{i in V, j in V: i!=j and i!=n-1 and j!=0}: v[i] + 1 <= v[j] + 1000000 * (1-x[i,j]) ;*/

/* Restricao de precedencia */
s.t. precedence{i in V, j in V: p[i,j]=1 and i!=j and i!=0 and j!=n-1}: v[i] + 1 <= v[j];

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
