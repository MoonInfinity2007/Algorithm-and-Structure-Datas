O(F(n)) = {g(n) : E n0 > 0, c > 0}
for any n >= m : 0 <= f(n) <= c * g(n)
|  | Insert | Remove | Search |
| -------- | -------- | -------- | -------- |
| Queue | O(1) | O(n) | O(n) |
| Deque | O(1) | O(n) | O(n) |
| Array | O(n) | O(n) | O(n) |
| Tree | | | O(n) |
Insertion sort
Сортирует список втсавляя следующий элемент после самого большего элемента, что меньше вставляемого
Merge sort
Делит списки на две
Quick sort
QuickSort(a, l, r):
    q = partition(a)
    QuickSort(a, l, q - 1)
    QuickSort(a, 1 + 1, r)
    Мы берем элемент q (какой-то) из массива, потом меняем элементы чтобы те что меньше q были слева, а справа те что больше и запускаем для этих двух сортировку рукурсивно
    QS(A, l, r):
        i = l - 1
        j = l
        pivot = a[r]
        For j = 1 to R - 1:
            if a[j] < [pivot]:
                ++i;
                swap(a[i], a[j])
        i++
        swap(a[i], a[r])
        QS(a, l, i - 1)
        QS(a, i + 1, r)
        return a
n! <= leaves of tree <= 2^(h-1)
2^(h - 1) >= n!
h >= 1 + log2(n!)
h >= log2(n!) >= nlog(n)
h = Omega(nlogn)
Counting Sort
Ну кроме очев, можно представить как префиксную сумму и по этому массиву вычитать из этого массива, чтобы получилось сортировка