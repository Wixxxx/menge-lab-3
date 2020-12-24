#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

template <class T>
class Menge
{
private:
	int size;
	T* menge;
public:
	Menge(int newsize = 0);
	Menge(const Menge<T>& copy);
	~Menge();

	bool istMenge(T a); // Проверка на входимость эл-та в множество
	bool istBeinhalten(Menge& a); // Проверка на содержание одно множества в другом
	bool check(T a); // Проверка на существование эл-та в множестве

	void eingabe(T a); // Добавление эл-та в множество
	void vernichtung(T a); // Удаление эл-та из множества
	void sortierung(); // Сортировка множества (прямым выбором)
	Menge vereinigung(Menge& a); // Объединение множеств
	Menge kreuzung(Menge& a); // Пересечение множеств
	T getSize();

	Menge operator= (const Menge& a);

	template<class T> friend istream& operator>> (istream& in, Menge<T>& a); // Ввод с клавиатуры
	template<class T> friend ostream& operator<< (ostream& out, Menge<T>& a); // Вывод в консоль
	template<class T> friend ifstream& operator>> (ifstream& f_in, Menge<T>& a); // Ввод из файла
	template<class T> friend ofstream& operator<< (ofstream& f_out, Menge<T>& a); // Вывод в файл
};

int inSize();
int AddElement();

int main()
{
	setlocale(LC_ALL, "Russian");
	printf("<===== Множества =====>\n");
	ifstream f("randomly_sorted.txt");

	Menge<int> M1(inSize());
	f >> M1;
	cout << M1;

	Menge<int> M2(inSize());
	f >> M2;
	cout << M2;

	Menge<int> M3(inSize());
	f >> M3;
	cout << M3;

	if (M1.getSize() > M2.getSize())
	{
		if (M1.getSize() > M3.getSize())
			cout << "В множестве 1 больше всего элементов - " << M1.getSize() << endl;
		else if (M1.getSize() == M3.getSize())
			cout << "Одинаковое кол-во элементов в 1-ом и 3-ем" << endl;
	}
	else
	{
		if (M2.getSize() > M3.getSize())
			cout << "В множестве 2 больше всего элементов - " << M2.getSize() << endl;
		else if (M1.getSize() == M2.getSize() && M2.getSize() == M3.getSize())
			cout << "Одинаковое кол-во элементов" << endl;
		else if (M2.getSize() == M3.getSize())
			cout << "Одинаковое кол-во элементов в 2-ом и 3-ем" << endl;
		else
			cout << "В множестве 3 больше всего элементов - " << M3.getSize() << endl;
	}

	Menge<int> menge1 = M1.kreuzung(M2);

	if (M1.istBeinhalten(M2))
		cout << "Множество 1 содержится в множестве 2" << endl;
	else
		cout << "Множество 1 не содержится в множестве 2" << endl;

	if (M2.istBeinhalten(M1))
		cout << "Множество 2 содержится в множестве 1" << endl;
	else
		cout << "Множество 2 не содержится в множестве 1" << endl;

	cout << "Добавить в множество 1 элемент - " << endl;
	M1.eingabe(AddElement());
	cout << M1;

	cout << "Удалить из множества 2 элемент - " << endl;
	M2.vernichtung(AddElement());
	cout << M2;

	Menge<int> M4 = M1.vereinigung(M2);
	cout << "Множество 4 - объединение множества 1 и множества 2 " << M4;

	return 0;
}

template<class T>
Menge<T>::Menge(int newsize)
{
	size = newsize;
	menge = new T[size];
	for (int i = 0; i < size; i++)
		menge[i] = 0;
}

template<class T>
Menge<T>::Menge(const Menge<T>& copy)
{
	size = copy.size;
	menge = new T[size];

	for (int i = 0; i < size; i++)
	{
		menge[i] = copy.menge[i];
	}
}

template<class T>
Menge<T>::~Menge()
{
	delete[] menge;
}

template<class T>
bool Menge<T>::istMenge(T a)
{
	return true;
}

template<>
bool Menge<int>::istMenge(int a) // Для натуральных чисел
{
	if (a > 0)
		return true;
	else
		return false;
}

template<class T>
bool Menge<T>::istBeinhalten(Menge<T>& a)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < a.size; j++)
			if (menge[i] == a.menge[j])
				count++;
	if (count == size)
		return true;
	else
		return false;
}

template<class T>
bool Menge<T>::check(T a)
{
	for (int i = 0; i < size; i++)
		if (menge[i] == a)
			return false;
	return true;
}

template<class T>
void Menge<T>::eingabe(T a)
{
	if (istMenge(a))
	{
		if (check(a))
		{
			Menge Buf = *this;

			delete[] menge;
			menge = new T[++size];

			for (int i = 0; i < size - 1; i++)
				menge[i] = Buf.menge[i];

			menge[size - 1] = a;
		}
		else
			cout << "Такое значение уже существует!" << endl;
	}
	else
		cout << "Не принадлежит множеству натуральных чисел" << endl;
	sortierung();
}

template<class T>
void Menge<T>::vernichtung(T a)
{
	if (istMenge(a))
	{
		if (!check(a))
		{
			Menge Buf = *this;

			delete[] menge;
			menge = new T[--size];

			int k = 0;
			for (int i = 0; i < Buf.size; i++)
			{
				if (Buf.menge[i] == a)
					continue;
				else
					menge[k++] = Buf.menge[i];
			}
		}
		else
			cout << "Такое значение не существует!" << endl;
	}
	else
		cout << "Не принадлежит множеству натуральных чисел" << endl;
	sortierung();
}

template<class T>
void Menge<T>::sortierung()
{
	int i, j, k;
	T x;
	for (i = 0; i < size; i++)
	{
		k = i;
		x = menge[i];
		for (j = i + 1; j <= size - 1; j++)
		{
			if (menge[j] < x)
			{
				k = j;
				x = menge[k];
			}
		}
		menge[k] = menge[i];
		menge[i] = x;
	}
}

template<class T>
Menge<T> Menge<T>::vereinigung(Menge<T>& a)
{
	int n = size + a.size;
	int newSize = size;
	Menge Buf(n);

	for (int i = 0; i < size; i++)
		Buf.menge[i] = menge[i];

	for (int i = 0; i < a.size; i++)
		if (Buf.check(a.menge[i]))
			Buf.menge[newSize++] = a.menge[i];

	Menge newBuf(newSize);

	for (int i = 0; i < newSize; i++)
		newBuf.menge[i] = Buf.menge[i];

	newBuf.sortierung();
	return newBuf;
}

template<class T>
Menge<T> Menge<T>::kreuzung(Menge<T>& a)
{
	Menge Buf(size);
	int newSize = 0;
	for (int i = 0; i < size; i++)
		if (!a.check(menge[i]))
			Buf.menge[newSize++] = menge[i];

	if (newSize == 0)
	{
		cout << "Множества не пересекаются" << endl;
		return *this;
	}
	else
	{
		Menge newBuf(newSize);
		for (int i = 0; i < newSize; i++)
			newBuf.menge[i] = Buf.menge[i];
		cout << "Множества пересекаются" << endl;
		newBuf.sortierung();
		return newBuf;
	}
}

template<class T>
T Menge<T>::getSize()
{
	T getsize = size;
	return getsize;
}

template<class T>
Menge<T> Menge<T>::operator=(const Menge<T>& a)
{
	delete[] menge;
	size = a.size;
	menge = new T[size];

	for (int i = 0; i < size; i++)
		menge[i] = a.menge[i];

	return menge;
}

template<class T>
istream& operator>>(istream& in, Menge<T>& a)
{
	int temp;
	cout << "Введите значения множества: " << endl;
	for (int i = 0; i < a.size; i++)
	{
		in >> temp;
		if (a.istMenge(temp))
		{
			if (a.check(temp))
				a.menge[i] = temp;
			else
			{
				cout << "Повтор!" << endl;
				i--;
			}
		}
		else
		{
			cout << "Не принадлежит множеству натуральных чисел!" << endl;;
			i--;
		}
	}
	return in;
}

template<class T>
ostream& operator<<(ostream& out, Menge<T>& a)
{
	a.sortierung();
	out << "Множество - (";
	for (int i = 0; i < a.size; i++)
	{
		if (i < a.size - 1)
			out << a.menge[i] << ", ";
		else
			out << a.menge[i] << ")" << endl;
	}
	cout << endl;
	return out;
}

template<class T>
ifstream& operator>>(ifstream& f_in, Menge<T>& a)
{
	T temp;
	for (int i = 0; i < a.size; i++)
	{
		f_in >> temp;
		if (a.istMenge(temp))
		{
			if (a.check(temp))
				a.menge[i] = temp;
			else
			{
				cout << temp << " - повтор!" << endl;
				i--;
			}
		}
		else
		{
			cout << temp << " - не принадлежит множеству натуральных чисел!" << endl;
			i--;
		}

	}
	return f_in;
}

template<class T>
ofstream& operator<<(ofstream& f_out, Menge<T>& a)
{
	a.sortierung();
	f_out << "(";
	for (int i = 0; i < a.size; i++)
	{
		if (i < a.size - 1)
			f_out << a.menge[i] << ", ";
		else
			f_out << a.menge[i] << ")" << endl;
	}
	cout << endl;
	return f_out;
}

int inSize()
{
	int n;
	cout << "Введите размерность множества: ";
	cin >> n;
	cout << endl;
	return n;
}

int AddElement()
{
	cout << "Введите элемент: ";
	int el;
	cin >> el;
	return el;
}