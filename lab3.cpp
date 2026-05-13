#include <iostream>

using namespace std;

template<typename T, int N>
class Vector
{
private:
    T data[N];

public:

    // Конструктор по умолчанию
    Vector()
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = T();
        }
    }

    // Конструктор заполнения одним значением
    Vector(T value)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = value;
        }
    }

    // Конструктор копирования
    Vector(const Vector<T, N>& other)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = other[i];
        }
    }

    // Конструктор преобразования типа
    template<typename U>
    Vector(const Vector<U, N>& other)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = static_cast<T>(other[i]);
        }
    }

    // Ввод элементов
    void input()
    {
        cout << "Enter " << N << " elements:" << endl;

        for (int i = 0; i < N; i++)
        {
            cin >> data[i];
        }
    }

    // Доступ по индексу
    T& operator[](int index)
    {
        if (index < 0)
        {
            index = N + index;
        }

        return data[index];
    }

    // Доступ по индексу (const)
    const T& operator[](int index) const
    {
        if (index < 0)
        {
            index = N + index;
        }

        return data[index];
    }

    // Размер вектора
    int size() const
    {
        return N;
    }

    // Вывод вектора
    void print() const
    {
        cout << "[ ";

        for (int i = 0; i < N; i++)
        {
            cout << data[i] << " ";
        }

        cout << "]" << endl;
    }

    // resize
    template<int NewSize>
    Vector<T, NewSize> resize() const
    {
        Vector<T, NewSize> result;

        int minSize;

        if (N < NewSize)
        {
            minSize = N;
        }
        else
        {
            minSize = NewSize;
        }

        for (int i = 0; i < minSize; i++)
        {
            result[i] = data[i];
        }

        return result;
    }

    // convert
    template<typename NewType>
    Vector<NewType, N> convert() const
    {
        Vector<NewType, N> result;

        for (int i = 0; i < N; i++)
        {
            result[i] = static_cast<NewType>(data[i]);
        }

        return result;
    }

    // slice
    template<int Start, int End>
    auto slice() const
    {
        constexpr int realStart =
            (Start < 0) ? N + Start : Start;

        constexpr int realEnd =
            (End < 0) ? N + End : End;

        constexpr int step =
            (realStart <= realEnd) ? 1 : -1;

        constexpr int newSize =
            (realStart <= realEnd)
            ? (realEnd - realStart + 1)
            : (realStart - realEnd + 1);

        Vector<T, newSize> result;

        int j = 0;

        for (
            int i = realStart;
            (step == 1) ? (i <= realEnd) : (i >= realEnd);
            i += step
        )
        {
            result[j] = data[i];
            j++;
        }

        return result;
    }
};

// Сложение векторов
template<typename T1, typename T2, int N>
auto operator+(const Vector<T1, N>& a,
               const Vector<T2, N>& b)
{
    using ResultType = decltype(T1() + T2());

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = a[i] + b[i];
    }

    return result;
}

// Вычитание векторов
template<typename T1, typename T2, int N>
auto operator-(const Vector<T1, N>& a,
               const Vector<T2, N>& b)
{
    using ResultType = decltype(T1() - T2());

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = a[i] - b[i];
    }

    return result;
}

// Умножение вектора на число
template<typename T, typename U, int N>
auto operator*(const Vector<T, N>& v, U value)
{
    using ResultType = decltype(T() * U());

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = v[i] * value;
    }

    return result;
}

// Деление вектора на число
template<typename T, typename U, int N>
auto operator/(const Vector<T, N>& v, U value)
{
    using ResultType = decltype(T() / U());

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = v[i] / value;
    }

    return result;
}

// Поэлементное умножение
template<typename T1, typename T2, int N>
auto operator*(const Vector<T1, N>& a,
               const Vector<T2, N>& b)
{
    using ResultType = decltype(T1() * T2());

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = a[i] * b[i];
    }

    return result;
}

// Поэлементное деление
template<typename T1, typename T2, int N>
auto operator/(const Vector<T1, N>& a,
               const Vector<T2, N>& b)
{
    using ResultType = decltype(T1() / T2());

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] = a[i] / b[i];
    }

    return result;
}

// weighted_sum
template<typename T1, typename T2,
         typename A, typename B,
         int N>
auto weighted_sum(const Vector<T1, N>& v1,
                  A alpha,
                  const Vector<T2, N>& v2,
                  B beta)
{
    using ResultType =
        decltype(alpha * v1[0] + beta * v2[0]);

    Vector<ResultType, N> result;

    for (int i = 0; i < N; i++)
    {
        result[i] =
            alpha * v1[i] +
            beta * v2[i];
    }

    return result;
}

// concat
template<typename T1, typename T2,
         int N1, int N2>
auto concat(const Vector<T1, N1>& a,
            const Vector<T2, N2>& b)
{
    using ResultType = decltype(T1() + T2());

    Vector<ResultType, N1 + N2> result;

    for (int i = 0; i < N1; i++)
    {
        result[i] = a[i];
    }

    for (int i = 0; i < N2; i++)
    {
        result[N1 + i] = b[i];
    }

    return result;
}

int main()
{
    Vector<int, 5> v1;
    Vector<double, 5> v2;

    cout << "INPUT VECTOR V1" << endl;
    v1.input();

    cout << endl;

    cout << "INPUT VECTOR V2" << endl;
    v2.input();

    cout << endl;

    cout << "VECTOR V1" << endl;
    v1.print();

    cout << endl;

    cout << "VECTOR V2" << endl;
    v2.print();

    cout << endl;

    cout << "SUM" << endl;
    auto sum = v1 + v2;
    sum.print();

    cout << endl;

    cout << "SUBTRACTION" << endl;
    auto sub = v1 - v2;
    sub.print();

    cout << endl;

    cout << "MULTIPLY BY NUMBER" << endl;
    auto multNum = v1 * 10;
    multNum.print();

    cout << endl;

    cout << "DIVIDE BY NUMBER" << endl;
    auto divNum = v1 / 2;
    divNum.print();

    cout << endl;

    cout << "ELEMENT MULTIPLICATION" << endl;
    auto multVec = v1 * v2;
    multVec.print();

    cout << endl;

    cout << "ELEMENT DIVISION" << endl;
    auto divVec = v1 / v2;
    divVec.print();

    cout << endl;

    cout << "NEGATIVE INDEX" << endl;
    cout << v1[-1] << endl;

    cout << endl;

    cout << "RESIZE" << endl;
    auto resized = v1.resize<8>();
    resized.print();

    cout << endl;

    cout << "CONVERT TO FLOAT" << endl;
    auto converted = v1.convert<float>();
    converted.print();

    cout << endl;

    cout << "SLICE 1..3" << endl;
    auto part1 = v1.slice<1, 3>();
    part1.print();

    cout << endl;

    cout << "SLICE REVERSE" << endl;
    auto part2 = v1.slice<4, 1>();
    part2.print();

    cout << endl;

    cout << "WEIGHTED SUM" << endl;
    auto ws = weighted_sum(v1, 0.7, v2, 3.2);
    ws.print();

    cout << endl;

    cout << "CONCAT" << endl;
    auto joined = concat(v1, v2);
    joined.print();

    cout << endl;

    return 0;
}
