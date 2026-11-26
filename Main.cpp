#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <utility>
 
constexpr int N1 = 1000;
constexpr int N2 = 10000;
constexpr int N3 = 100000;
constexpr int N4 = 1000000;
constexpr int N5 = 3000000;
 
constexpr bool MOSTRAR_PROGRESO = true;
 
void mostrarBarra(int actual, int total) {
    if (!MOSTRAR_PROGRESO) return;
    const int anchoBarra = 40;
    float progreso = (float)actual / total;
    int pos = (int)(anchoBarra * progreso);
 
    std::cout << "\rOrdenando: [";
    for (int i = 0; i < anchoBarra; ++i) {
        if (i < pos) std::cout << "█";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progreso * 100.0f) << "% " << std::flush;
}
 
//---------------------------------------------------------------------------
void selectionSort(std::vector<int>& arr) {
    int n = (int)arr.size();
    int paso = std::max(1, n / 100);
 
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        if (min != i) std::swap(arr[i], arr[min]);
 
        if (i % paso == 0) mostrarBarra(i + 1, n);
    }
    mostrarBarra(n, n);
    if (MOSTRAR_PROGRESO) std::cout << '\n';
}
 
//---------------------------------------------------------------------------
void bubbleSort(std::vector<int>& arr) {
    int n = (int)arr.size();
    int paso = std::max(1, n / 100);
 
    for (int i = 0; i < n - 1; i++) {
        bool intercambiado = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                intercambiado = true;
            }
        }
        if (i % paso == 0) mostrarBarra(i + 1, n);
        if (!intercambiado) break;
    }
    mostrarBarra(n, n);
    if (MOSTRAR_PROGRESO) std::cout << '\n';
}
 
//---------------------------------------------------------------------------
void merge(std::vector<int>& arr, std::vector<int>& aux, int izq, int medio, int der) {
    int i = izq;
    int j = medio + 1;
    int k = izq;
 
    while (i <= medio && j <= der) {
        if (arr[i] <= arr[j]) aux[k++] = arr[i++];
        else                  aux[k++] = arr[j++];
    }
    while (i <= medio) aux[k++] = arr[i++];
    while (j <= der)   aux[k++] = arr[j++];
 
    for (k = izq; k <= der; k++) arr[k] = aux[k];
}
 
void mergeSortRec(std::vector<int>& arr, std::vector<int>& aux, int izq, int der) {
    if (izq >= der) return;
    int medio = izq + (der - izq) / 2;
    mergeSortRec(arr, aux, izq, medio);
    mergeSortRec(arr, aux, medio + 1, der);
    merge(arr, aux, izq, medio, der);
}
 
void mergeSort(std::vector<int>& arr) {
    int n = (int)arr.size();
    if (n < 2) return;
    std::vector<int> aux(n);  // un solo buffer, una sola alocación
    mergeSortRec(arr, aux, 0, n - 1);
}
 
//---------------------------------------------------------------------------
int particion(std::vector<int>& arr, int izq, int der) {
    // Mediana de tres: deja la mediana en arr[der] como pivote
    int medio = izq + (der - izq) / 2;
    if (arr[medio] < arr[izq]) std::swap(arr[medio], arr[izq]);
    if (arr[der]   < arr[izq]) std::swap(arr[der],   arr[izq]);
    if (arr[medio] < arr[der]) std::swap(arr[medio], arr[der]);
    int pivote = arr[der];
 
    int i = izq - 1;
    for (int j = izq; j < der; j++) {
        if (arr[j] < pivote) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[der]);
    return i + 1;
}
 
void quickSortRec(std::vector<int>& arr, int izq, int der) {
    // Recursión solo en el lado menor, iteración en el mayor: stack O(log n)
    while (izq < der) {
        int p = particion(arr, izq, der);
        if (p - izq < der - p) {
            quickSortRec(arr, izq, p - 1);
            izq = p + 1;
        } else {
            quickSortRec(arr, p + 1, der);
            der = p - 1;
        }
    }
}
 
void quickSort(std::vector<int>& arr) {
    if (arr.size() > 1) quickSortRec(arr, 0, (int)arr.size() - 1);
}
 
//---------------------------------------------------------------------------
void heapify(std::vector<int>& arr, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;
 
    if (izq < n && arr[izq] > arr[mayor]) mayor = izq;
    if (der < n && arr[der] > arr[mayor]) mayor = der;
 
    if (mayor != i) {
        std::swap(arr[i], arr[mayor]);
        heapify(arr, n, mayor);
    }
}
 
void heapSort(std::vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
 
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
 
//---------------------------------------------------------------------------
void insertionSort(std::vector<int>& arr) {
    int n = (int)arr.size();
    int paso = std::max(1, n / 100);
 
    for (int i = 1; i < n; i++) {
        int actual = arr[i];
        int j = i - 1;
 
        while (j >= 0 && arr[j] > actual) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = actual;
 
        if (i % paso == 0) mostrarBarra(i + 1, n);
    }
    mostrarBarra(n, n);
    if (MOSTRAR_PROGRESO) std::cout << '\n';
}
 
//---------------------------------------------------------------------------
int main() {
    const int tamano = N3;
 
    std::vector<int> arr(tamano);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 999999);
    for (int& x : arr) x = dist(gen);
 
    int opcion;
    std::string nombrealg;
    std::cout << "=========SORTS============\n";
    std::cout << "1. Selection Sort\n2. Bubble Sort\n3. Merge Sort\n"
                 "4. Quick Sort\n5. Heap Sort\n6. Insertion Sort\n";
    std::cout << "Elige una opcion:\n";
 
    if (!(std::cin >> opcion) || opcion < 1 || opcion > 6) {
        std::cout << "Opcion no disponible\n";
        return 1;
    }
 
    switch (opcion) {
        case 1: nombrealg = "Selection Sort"; break;
        case 2: nombrealg = "Bubble Sort";    break;
        case 3: nombrealg = "Merge Sort";     break;
        case 4: nombrealg = "Quick Sort";     break;
        case 5: nombrealg = "Heap Sort";      break;
        case 6: nombrealg = "Insertion Sort"; break;
    }
 
    auto inicio = std::chrono::steady_clock::now();
    switch (opcion) {
        case 1: selectionSort(arr); break;
        case 2: bubbleSort(arr);    break;
        case 3: mergeSort(arr);     break;
        case 4: quickSort(arr);     break;
        case 5: heapSort(arr);      break;
        case 6: insertionSort(arr); break;
    }
    auto fin = std::chrono::steady_clock::now();
 
    std::chrono::duration<double> tiempo = fin - inicio;
 
    std::cout << "Algoritmo: " << nombrealg << '\n';
    std::cout << "Arreglo de " << tamano << " elementos "
              << (std::is_sorted(arr.begin(), arr.end()) ? "ordenado correctamente." : "NO QUEDO ORDENADO.")
              << '\n';
    std::cout << "Tiempo de ejecucion: " << tiempo.count() << " segundos.\n";
 
    return 0;
}
 