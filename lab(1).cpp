// lab(1).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <chrono>
using namespace chrono;
#include <ctime>
struct list
{
	int data;
	list *next;
	list *pred;
};
struct LinkedList
{
	list *head;
	list *tail;
	LinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	~LinkedList()
	{
		while (head != NULL)
		{
			tail = head->next;
			delete head;
			head = tail;
		}
	}

	//1)создание списка
	list* CreateList1(unsigned N)
	{
		list *curr = 0,
			*Pred = 0;
		for (unsigned i = 0; i < N; ++i)
		{
			curr = new list;
			curr->pred = Pred;
			if (Pred)
				Pred->next = curr;
			if (Pred == 0)
				head = curr;
			Pred = curr;
		}
		tail = Pred;
		Pred->next = 0;
		return head;
	}
	list *CreateList2(int data)
	{
		list *curr = new list;
		curr->data= data;
		curr->next = 0;
		if (head != NULL) //список не пуст
		{
			tail->next = curr;
			curr->pred = tail;
			tail = curr;
		}
		else
		{
			curr->pred = 0;
			head = curr;
			tail = curr;
		}
		return head;
	}

	//3)Получение элемента
	list *Get(int index)
	{
		list* curr = head;
		int count = 0;
		while (count != index)
		{
			if (curr == NULL)
				return curr;
			curr = curr->next;
			count++;
		}
		return curr;
	}

	//Вывод списка
	void Show()
	{
		list* elem = head;
		while (elem != NULL)
		{
			cout << elem->data << " ";
			elem = elem->next;
		}
	}

	//Удаление элемента
	void Delete(int index)
	{
		list *curr = Get(index);
		if (curr->pred == NULL)
		{
			list *elem = head->next;
			elem->pred = NULL;
			delete head;
			head = elem;
			return;
		}
		if (curr->next == NULL)
		{
			list *elem = tail->pred;
			elem->next = NULL;
			delete tail;
			tail = elem;
			return;
		}
		if (curr->next != 0 and curr->pred != 0)
		{
			list *left = curr->pred;
			list *right = curr->next;
			left->next = right;
			right->pred = left;
			delete curr;
		}

	}

	//Вставка элемента
	list *Place(int index, int data)
	{
		list* right = Get(index);

		if (right == NULL)
		{
			list *curr = new list;
			curr->data = data;
			curr->pred = tail;
			tail->next = curr;
			curr->next = 0;
			tail = curr;
			return curr;
		}
		list* left = right->pred;
		if (left == NULL)
		{
			list *curr = new list;
			curr->data = data;
			curr->next = head;
			head->pred = curr;
			curr->pred = 0;
			head = curr;
			return curr;
		}

		list* curr = new list;
		curr->next = right;
		curr->pred = left;
		left->next = curr;
		right->pred = curr;
		curr->data = data;
		return curr;
	}

	//Перестановка элементов
	void Swap(int index1, int index2)
	{
		list *elem1 = Get(index1);
		list *elem2 = Get(index2);
		list *left1 = elem1->pred;
		list *right1 = elem1->next;
		list *left2 = elem2->pred;
		list *right2 = elem2->next;
		if (elem2 == tail and elem1 == head)
		{
			elem2->next = right1;
			elem1->next = 0;
			elem1->pred = left2;
			elem2->pred = 0;
			left2->next = elem1;
			right1->pred = elem2;
			head = elem2;
			tail = elem1;
			return;
		}
		if (elem2 == tail and index2 - index1 != 1)
		{
			elem2->next = right1;
			elem1->next = 0;
			swap(elem1->pred, elem2->pred);
			swap(left2->next, left1->next);
			right1->pred = elem2;
			tail = elem1;
			return;
		}
		if (elem1 == head and index2 - index1 != 1)
		{
			swap(elem2->next, elem1->next);
			elem1->pred = left2;
			elem2->pred = 0;
			swap(right1->pred, right2->pred);
			left2->next = elem1;
			head = elem2;
			return;
		}
		if (index2 - index1 == 1)
		{
			list *curr1 = head;
			for (int i = 0; i < index1; i++)
				curr1 = curr1->next;
			list *curr2 = head;
			for (int i = 0; i < index2; i++)
				curr2 = curr2->next;
			int m = curr1->data;
			curr1->data = curr2->data;
			curr2->data = m;
			return;
		}
		if (elem2 != tail and elem1 != head and index2 - index1 != 1)
		{
			swap(elem2->next, elem1->next);
			swap(elem1->pred, elem2->pred);
			swap(left2->next, left1->next);
			swap(right1->pred, right2->pred);
		}
	}
};



int main()
{
	setlocale(0, "");
	srand(time(NULL));
	time_point<steady_clock> start;
	time_point<steady_clock> end;
	time_point<steady_clock> start1;
	time_point<steady_clock> end1;
	time_point<steady_clock> start2;
	time_point<steady_clock> end2;
	time_point<steady_clock> start3;
	time_point<steady_clock> end3;
	time_point<steady_clock> start4;
	time_point<steady_clock> end4;
	LinkedList LinList;
	int index;
	while (true)
	{
		cout << "\n\n1)Создать список\n2)Получить элемент по индексу\n3)Удалить элемент\n4)Вставить элемент\n5)Поменять элементы местами\n0)Выход\n";
		cout << "Ваш выбор: ";
		int p;
		cin >> p;
		if (p == 0)
			break;
		if (p == 1)
		{
			int m;
			cout << "Как вы хотите создать список? ";
			cout << endl;
			cout << "1)Ввести длину списка\n2)Ввести значения с клавиатуры\n";
			cout << "Ваш выбор: ";
			cin >> m;
			if (m == 1)
			{
				cout << "Введите длинну списка:";
				unsigned N;
				cin >> N;
				start = chrono::steady_clock::now();
				list *List = LinList.CreateList1(N);
				end = chrono::steady_clock::now();
				list * Curr = List;
				while (Curr)
				{
					Curr->data = rand() % 100;
					Curr = Curr->next;
				}
				LinList.Show();
				cout << endl;
				cout << "Затраченное время: " << duration_cast<microseconds>(end - start).count() << " мкс.\n";
			}
			if (m == 2)
			{
				int data;
				cout << "Чтобы прекратить ввод введите -1";
				cout << endl;
				cin >> data;
				while (data != -1)
				{
					start4 = chrono::steady_clock::now();
					LinList.CreateList2(data);
					cin >> data;
					end4 = chrono::steady_clock::now();
				}
				LinList.Show();
				cout << endl;
				cout << "Затраченное время: " << duration_cast<seconds>(end4 - start4).count() << " с.\n";
			}
		}
		if (p == 2)
		{
			cout << "Получить элемент с индексом:";

			cin >> index;
			start1 = chrono::steady_clock::now();
			cout << LinList.Get(index)->data;
			end1 = chrono::steady_clock::now();
			cout << "\nЗатраченное время: " << duration_cast<microseconds>(end1 - start1).count() << " мкс.\n";
			cout << endl;
			
		}
		if (p == 3)
		{
			cout << "Введите индекс элемента, который хотите удалить: ";
			cin >> index;
			start2 = chrono::steady_clock::now();
			LinList.Delete(index);
			end2 = chrono::steady_clock::now();
			LinList.Show();
			cout << "\nЗатраченное время: " << duration_cast<microseconds>(end2 - start2).count() << " мкс.\n";
		
		}
		if (p == 4)
		{
			cout << "Введите индекс элемента на место, которого хотите вставить новый:";
			cin >> index;
			cout << "Введите значение нового элемента:";
			int data;
			cin >> data;
			start3 = chrono::steady_clock::now();
			LinList.Place(index, data);
			end3 = chrono::steady_clock::now();
			LinList.Show();
			cout << "\nЗатраченное время: " << duration_cast<microseconds>(end3 - start3).count() << " мкс.\n";
			cout << endl;
			
		}
		if (p==5)
		{
			cout << "Введите индексы элементов (в порядке возрастания), которые хотите поменять местами: ";
			int index1, index2;
			cin >> index1;
			cin >> index2;
			LinList.Swap(index1, index2);
			LinList.Show();
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
