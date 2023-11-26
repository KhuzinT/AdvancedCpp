# Homework № 4

# [Min-cost-to-connect-all-points](https://leetcode.com/problems/min-cost-to-connect-all-points/description/)

Решение задачи сводится к нахождению минимального остовного дерева

Для его нахождения можно использовать алгоритм Прима, Крускала или Борувки. Я буду использовать алгоритм [Крускала](http://e-maxx.ru/algo/mst_kruskal_with_dsu), 
т.к. в нем применяется DSU, которое уже написано 

Алгоритм заключается в следующем: сначала мы сортируем ребра по весам, затем проходимся по отсортированным ребрам, 
объединяя вершины. Если какие-то две вершины еще не объединены, то делаем это, добавляя соединяющее ребро в ответ. 
Это ребро будет входить в МОД, т.к. ребра отсортированы 

# [Minimum-weighted-subgraph-with-the-required-paths](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/description/)


