#include <iostream>
#include <iomanip>

class Polynom
{
public:
    // конструктор по-умолчанию
    // количество коэффициентов равно нулю
    // коэффициенты - нулевой указатель
    Polynom() : degree(0), array(nullptr)
    {

    }

    // конструктор с 2 аргументами
    // первый - степень, второй - массив коэффициентов
    Polynom(std::size_t N, double* c)
    {
        set(N, c);
    }

    //конструктор копии
    Polynom(const Polynom& obj) :
        degree(obj.getDegree()),
        //если размер не равен 0 то выделяем память, если равен - инициализируем нулевым указателем
        array(degree ? new double[degree + 1] : nullptr)
    {
        if (degree == 0)
        { return; }

        //поэлементное копирование
        for (std::size_t i = 0; i <= degree; i++)
        { array[i] = obj.array[i]; }
    }

    // оператор проверки на равенство
    bool operator == (const Polynom& obj) const
    {
        // полиномы с разными размерами не могут быть равны
        if (degree != obj.getDegree())
        { return false; }

        if (degree == 0)
        { return true; }

        for (std::size_t i = 0; i <= degree; i++)
            if(array[i] != obj.array[i])
            { return false; }

        return true;
    }

    // оператор проверки на неравенство
    // обратная операция к проверке на равенство
    bool operator != (const Polynom& obj) const
    {
        return !(*this == obj);
    }

    // оператор присваивания
    Polynom& operator = (const Polynom& obj)
    {
        if (this == &obj)
        { return *this; } // самоприсваивание

        //очищаем старые данные
        delete[] array;

        degree = obj.getDegree();

        if (degree != 0)
        {

            //выделяем память и копируем элементы массива
            array = new double[degree + 1];
            for (std::size_t i = 0; i <= degree; i++)
            {
                array[i] = obj.array[i];
            }
        }
        else
        {
            array = nullptr;

        }
        return *this;
    }

    // получить коэффициенты
    double* get()
    {
        return array;
    }

    // установить степень и коэффициенты
    void set(std::size_t N, double* c)
    {
        delete[] array;
        degree = N;
        array = c;
    }

    // получить степень
    std::size_t getDegree() const
    {
        return degree;
    }

    //деструктор
    ~Polynom(void)
    {
        std::cout << "Dtor\n";
        delete[] array;
    }

    // перегруженный оператор вывода
    friend std::ostream& operator<< (std::ostream& stream,
                                     const Polynom& p)
    {
        if(p.getDegree() != 0)
        {
            for (int i = p.degree; i > 0; i--)
            {
                double c = p.array[i];
                if(c != 0)
                {
                    std::cout << p.array[i] << "x^" << i << " + ";
                }
            }
            std::cout << p.array[0] << '\n';
        }

        return stream;
    }

    friend std::istream& operator>> (std::istream& stream,
                                     Polynom& number)
    {
        // вводим степень
        std::size_t degree;
        stream >> degree;
        double* temp = new double[degree + 1];

        // вводим коэффициенты
        for (std::size_t i = 0; i <= degree; i++)
        { stream >> temp[i]; }

        number.set(degree, temp);

        return stream;
    }

    // перегруженный оператор сложения с числом (справа)
    friend Polynom operator + (Polynom a, double number)
    {
        a.array[0] += number;
        return a;
    }

    // сложение с числом (слева)
    friend Polynom operator + (double number, Polynom a)
    {
        a.array[0] += number;
        return a;
    }

private:

    std::size_t degree; // степень
    double* array; // массив коэффициентов
};

int main()
{
    // конструктор по-умолчанию
    Polynom a;

    int psize = 4;

    double* temp = new double[psize + 1]();
    temp[2] = 1;
    temp[4] = 2;

    // констуктор копирования
    Polynom b(a);
    b.set(psize, temp);// set
    Polynom c;
    c = b;// присваивание
    // проверка на равенство и неравенство
    std::cout << "a == b\t" << std::boolalpha << (a == b) << '\n';
    std::cout << "a != c\t" << std::boolalpha << (a != c) << '\n';
    std::cout << "c == b\t" << std::boolalpha << (c == b) << '\n';
    std::cout << c; // вывод

    std::cout << "Enter degree of polynom and coefficients:\n";
    std::cin >> a; // ввод
    std::cout << a;
    a = (a + 2); // сложение с числом справа
    std::cout << a;
    a = (3 + a); // сложение с числом слева
    std::cout << a;

    // get
    for(std::size_t i = 0; i <= a.getDegree(); i++)
    {
        std::cout << a.get()[i] << ' ';
    }
}
