# Homework № 5

# [Longest-repeating-character-replacement](https://leetcode.com/problems/longest-repeating-character-replacement/description/)

Метод скользящего окна

Будем отслеживать начало и конец окна, а также массив частоты символа в окне и максимальное значение этой частоты. Далее просто сдвигаем окно, пока можем, обновляя частоты. 
Если размер окна больше чем максимальная частоты в окне + k, то нужно уменьшить размер окна, сдвинув указатель на начало

Заметим, что мы на каждом шаге сдвигаем указатель на конец окна и только иногда сдвигаем указатель на начало. 
Таким образом, размер окна никогда не уменьшиться и можно вернуть его как ответ

# [Find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/)

