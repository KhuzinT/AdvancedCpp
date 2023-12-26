# Homework № 4

# [Min-cost-to-connect-all-points](https://leetcode.com/problems/min-cost-to-connect-all-points/description/)

Решение задачи сводится к нахождению минимального остовного дерева

Для его нахождения можно использовать алгоритм Прима, Крускала или Борувки 

~~Я буду использовать алгоритм [Крускала](http://e-maxx.ru/algo/mst_kruskal_with_dsu), 
т.к. в нем применяется DSU, которое уже написано~~

~~Алгоритм заключается в следующем: сначала мы сортируем ребра по весам, затем проходимся по отсортированным ребрам, 
объединяя вершины. Если какие-то две вершины еще не объединены, то делаем это, добавляя соединяющее ребро в ответ. 
Это ребро будет входить в МОД, т.к. ребра отсортированы~~

Я буду использовать алгоритм [Прима](https://e-maxx.ru/algo/mst_prim), так как граф плотный

Алгоритм заключается в следующем: минимальный остов строится постепенно, добавлением в него рёбер по одному 

Изначально остов состоит из одной вершины. Затем выбирается ребро минимального веса, исходящее из этой вершины, и добавляется в минимальный остов. 
После этого остов содержит уже две вершины, и теперь ищется и добавляется ребро минимального веса, имеющее один конец в одной из двух выбранных вершин, а другой — во всех остальных, кроме этих двух

И так далее, т.е. всякий раз ищется минимальное по весу ребро, один конец которого — уже взятая в остов вершина, а другой конец — ещё не взятая, 
и это ребро добавляется в остов. Этот процесс повторяется до тех пор, пока остов не станет содержать все вершины (или, что то же самое, n-1 ребро)

# [Minimum-weighted-subgraph-with-the-required-paths](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/description/)

Идея решения - если есть подграф, который удовлетворяет условию, то в нем существует такая вершина x,
что есть путь от src1 и src2 до x, а также от x до dest (или от dest до x в инвертированном графе).
Тогда мы можем найти минимальное пути от нужных вершин до x - их сумма и будет ответом

Но как понять, какая вершина является x? С помощью алгоритма Дейкстры можно найти минимальное расстояние
от src1, src2 и dest до всех остальных вершин, а затем пройтись циклом по вершинам, обновляя сумму расстояний до текущей
вершины. Вершина, на которой реализуется минимальное расстояние, является x
