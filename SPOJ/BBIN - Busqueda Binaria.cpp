/*BBIN - Busqueda Binaria
#binary-search

Dado un arreglo (vector) de N enteros ordenados de forma no decreciente, se realizaran Q consultas, cada una consta de un entero. Utilice búsqueda binaria para responder el indice de la primera ocurrencia del entero solicitado en el arreglo.
Input

En la primera linea recibirá un entero N (1 <= N <= 10^5) y un entero Q (1 <= Q <= 10^5).

En la segunda linea hay N enteros separados por espacios, cada entero toma un valor entre 1 y 10^9.

A continuación siguen Q lineas, cada una con un entero entre 1 y 10^9, representando una consulta.
Output

Por cada consulta (en el orden en que estas fueron recibidas) imprima una linea que consiste de un entero, el índice de la primera aparición del elemento consultado, o -1 si no está presente en los N enteros iniciales.
Example

Input:

10 4

1 3 4 5 5 6 7 8 8 17

3

5

9

1

Output:

1

3

-1

0

*/

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> vec (n);
    
    for (auto& num: vec) std::cin >> num;
    
    while (q--)
    {
        int num;
        std::cin >> num;
        
        auto it = std::lower_bound(std::begin(vec), std::end(vec), num);
        
        if (it == vec.end() || *it != num)
            std::cout << -1 << std::endl;
        else
            std::cout << std::distance(vec.begin(), it) << std::endl;
    }
    
    return 0;
}
