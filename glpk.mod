/* Número de nós */
param n, integer, >= 3;

/* Constante muito grande */
param M;

/* Conjunto de vértices */
set V:= 0..n-1;

/* Custo do nó i ao nó j */
param c{i in V, j in V};

/* Pares de precedência. O primeiro (i), precede o segundo (j).*/
param p{i in V, j in V};

/* Variáveis de Decisão */
/* x(i,j) = 1 se aresta está no caminho, 0 caso contrário */
var x{i in V, j in V}, binary;

/* Ordem de visitação. Possui valor 0 para o primeiro nó i visitado, 1 para o segundo, e assim por diante. */
var o{i in V} >= 0;



/* FUNÇÃO OBJETIVO */
minimize total: sum{i in V, j in V: i !=j} x[i,j] * c[i,j];


/* RESTRIÇÕES */

/* Viajante sai de cada nó i exatamente uma vez, exceto no último */
s.t. leave{i in V: i!=n-1}: sum{j in V: i!=j} x[i,j] = 1;

/* Viajante chega em cada nó j exatamente uma vez, exceto no primeiro */
s.t. enter{j in V: j!=0}: sum{i in V: i!=j} x[i,j] = 1;

/* Viajante nunca sai do último nó */
s.t. leave_last{j in V}: x[n-1, j] = 0;

/* Viajante nunca chega no primeiro nó */
s.t. enter_first{i in V}: x[i,0] = 0;

/* Viajante deve obedecer a precedência fornecida pela instância */
s.t. precedence{i in V, j in V: i != j and p[i,j] = 1}: o[i] + 1 <= o[j];

/* Viajante segue a ordem de visitação (evita subtours) */
s.t. visit_order{i in V, j in V: i != j}: o[i] + 1 <= o[j] - M * (x[i,j] - 1);


solve;

printf "Caminho ótimo tem custo %d\n",
   sum{i in V, j in V} c[i,j] * x[i,j];
printf("      De      Para      Custo\n");
printf{i in V, j in V: x[i,j]} "     %3d       %3d   %8g\n",
i, j, c[i,j];

end;
