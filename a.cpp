#include <iostream>

int main() {
    size_t n = 100'000'000;
    std::cout << sizeof(int)*n;
    int* arr = (int*)malloc(n*sizeof(int));
    for (size_t i = 0; i < n; i++) {
        arr[i] = i;
    }
    std::cout << (arr) << " " << (arr + 1) << " " << (arr + 2) << '\n';
    std::cout<<std::endl;
    arr = (int*)realloc(arr, n*sizeof(int)/2);
    std::cout << (arr) << " " << (arr + 1) << " " << (arr + 2) << '\n';
    free(arr);
    return 0;
}