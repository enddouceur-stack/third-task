#include <iostream>
using namespace std;

template <typename T>
class Vector {
private:
    T* data;
    int size;

public:

    Vector();

    Vector(const Vector<T>& other);

    Vector(int n, T value);

    template <typename U>
    Vector(const Vector<U>& other);

    ~Vector();

    int getSize() const;

    T& operator[](int index);

    const T& operator[](int index) const;

    void print() const;

    void input();

    template <typename U>
    auto operator+(U value) const;

    template <typename U>
    auto operator-(U value) const;

    template <typename U>
    auto operator*(U value) const;

    template <typename U>
    auto operator/(U value) const;

    template <typename U>
    auto operator+(const Vector<U>& other) const;

    template <typename U>
    auto operator-(const Vector<U>& other) const;

    template <typename U>
    auto operator*(const Vector<U>& other) const;

    template <typename U>
    auto operator/(const Vector<U>& other) const;

    template <int NewSize>
    Vector<T> resize() const;

    template <typename NewType>
    Vector<NewType> convert() const;

    template <int Start, int End>
    Vector<T> slice() const;

    template <typename U, typename A, typename B>
    static auto weightedSum(
        const Vector<T>& v1,
        A a,
        const Vector<U>& v2,
        B b
    );

    template <typename U>
    auto concat(const Vector<U>& other) const;
};



// ===== Реалізація =====

template <typename T>
Vector<T>::Vector() {
    size = 0;
    data = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {

    size = other.size;

    data = new T[size];

    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>::Vector(int n, T value) {

    size = n;

    data = new T[size];

    for (int i = 0; i < size; i++) {
        data[i] = value;
    }
}

template <typename T>
template <typename U>
Vector<T>::Vector(const Vector<U>& other) {

    size = other.getSize();

    data = new T[size];

    for (int i = 0; i < size; i++) {
        data[i] = static_cast<T>(other[i]);
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
int Vector<T>::getSize() const {
    return size;
}

template <typename T>
T& Vector<T>::operator[](int index) {

    if (index < 0) {
        index = size + index;
    }

    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {

    if (index < 0) {
        index = size + index;
    }

    return data[index];
}

template <typename T>
void Vector<T>::print() const {

    cout << "[ ";

    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }

    cout << "]" << endl;
}

template <typename T>
void Vector<T>::input() {

    for (int i = 0; i < size; i++) {
        cout << "Element " << i << ": ";
        cin >> data[i];
    }
}



// ===== Операції зі скаляром =====

template <typename T>
template <typename U>
auto Vector<T>::operator+(U value) const {

    Vector<decltype(T() + U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] + value;
    }

    return result;
}

template <typename T>
template <typename U>
auto Vector<T>::operator-(U value) const {

    Vector<decltype(T() - U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] - value;
    }

    return result;
}

template <typename T>
template <typename U>
auto Vector<T>::operator*(U value) const {

    Vector<decltype(T() * U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] * value;
    }

    return result;
}

template <typename T>
template <typename U>
auto Vector<T>::operator/(U value) const {

    Vector<decltype(T() / U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] / value;
    }

    return result;
}



// ===== Операції з вектором =====

template <typename T>
template <typename U>
auto Vector<T>::operator+(const Vector<U>& other) const {

    Vector<decltype(T() + U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] + other[i];
    }

    return result;
}

template <typename T>
template <typename U>
auto Vector<T>::operator-(const Vector<U>& other) const {

    Vector<decltype(T() - U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] - other[i];
    }

    return result;
}

template <typename T>
template <typename U>
auto Vector<T>::operator*(const Vector<U>& other) const {

    Vector<decltype(T() * U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] * other[i];
    }

    return result;
}

template <typename T>
template <typename U>
auto Vector<T>::operator/(const Vector<U>& other) const {

    Vector<decltype(T() / U())> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i] / other[i];
    }

    return result;
}



// ===== resize =====

template <typename T>
template <int NewSize>
Vector<T> Vector<T>::resize() const {

    Vector<T> result(NewSize, T());

    int limit = (size < NewSize) ? size : NewSize;

    for (int i = 0; i < limit; i++) {
        result[i] = data[i];
    }

    return result;
}



// ===== convert =====

template <typename T>
template <typename NewType>
Vector<NewType> Vector<T>::convert() const {

    Vector<NewType> result(size, NewType());

    for (int i = 0; i < size; i++) {
        result[i] = static_cast<NewType>(data[i]);
    }

    return result;
}



// ===== slice =====

template <typename T>
template <int Start, int End>
Vector<T> Vector<T>::slice() const {

    int start = Start;
    int end = End;

    if (start < 0) {
        start = size + start;
    }

    if (end < 0) {
        end = size + end;
    }

    if (start <= end) {

        int newSize = end - start + 1;

        Vector<T> result(newSize, T());

        int j = 0;

        for (int i = start; i <= end; i++) {
            result[j++] = data[i];
        }

        return result;
    }
    else {

        int newSize = start - end + 1;

        Vector<T> result(newSize, T());

        int j = 0;

        for (int i = start; i >= end; i--) {
            result[j++] = data[i];
        }

        return result;
    }
}



// ===== weightedSum =====

template <typename T>
template <typename U, typename A, typename B>
auto Vector<T>::weightedSum(
    const Vector<T>& v1,
    A a,
    const Vector<U>& v2,
    B b
) {

    using ResultType = decltype(a * v1[0] + b * v2[0]);

    int size = v1.getSize();

    Vector<ResultType> result(size, 0);

    for (int i = 0; i < size; i++) {
        result[i] = a * v1[i] + b * v2[i];
    }

    return result;
}



// ===== concat =====

template <typename T>
template <typename U>
auto Vector<T>::concat(const Vector<U>& other) const {

    using ResultType = decltype(T() + U());

    int newSize = size + other.getSize();

    Vector<ResultType> result(newSize, 0);

    for (int i = 0; i < size; i++) {
        result[i] = data[i];
    }

    for (int i = 0; i < other.getSize(); i++) {
        result[size + i] = other[i];
    }

    return result;
}



// ===== main =====

int main() {

    int n;

    cout << "Enter vector size: ";
    cin >> n;

    Vector<int> v1(n, 0);

    cout << "\nEnter elements for v1:\n";
    v1.input();

    cout << "\nv1 = ";
    v1.print();

    // Скаляр
    int scalar;

    cout << "\nEnter scalar: ";
    cin >> scalar;

    auto sumScalar = v1 + scalar;

    cout << "v1 + scalar = ";
    sumScalar.print();

    // Другий вектор
    Vector<int> v2(n, 0);

    cout << "\nEnter elements for v2:\n";
    v2.input();

    cout << "\nv2 = ";
    v2.print();

    // Додавання векторів
    auto sumVectors = v1 + v2;

    cout << "v1 + v2 = ";
    sumVectors.print();

    // resize
    auto bigger = v1.resize<10>();

    cout << "\nResize to 10:\n";
    bigger.print();

    // convert
    auto floatVector = v1.convert<float>();

    cout << "\nConvert to float:\n";
    floatVector.print();

    // slice
    auto sliced = v1.slice<0, 2>();

    cout << "\nSlice <0,2>:\n";
    sliced.print();

    // weighted sum
    auto ws = Vector<int>::weightedSum(v1, 0.5, v2, 2.0);

    cout << "\nWeighted sum:\n";
    ws.print();

    // concat
    auto combined = v1.concat(v2);

    cout << "\nConcatenation:\n";
    combined.print();

    return 0;
}
