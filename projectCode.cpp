#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

vector<int>used_wagons;
vector<int>::iterator it;

bool isNumeric(std::string const& str)//функция,проверяющая строку на содержание символов кроме чисел 
{
	return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

int getChislo()//функция для ввода количества вагонов
{
	string N;
	cout << "Введите количетсво вагонов ";
	cin >> N;
	while (isNumeric(N) == false || isNumeric(N) == true && stoi(N) == 0)
	{
		if (isNumeric(N) == true && stoi(N) == 0)
		{
			cout << "Введите число больше 0 " << endl;
		}
		else
		{
			cout << "Вы ввели неправильное кол-во вагонов " << endl;
		}
		cout << "Введите количетсво вагонов ";
		cin >> N;
	}

	return stoi(N);
}

bool find_elem(int elem)//функция чтобы проверить был ли номер вагона уже введён 
{
	for (it = used_wagons.begin();it != used_wagons.end(); it++)
	{
		if (*it == elem)
		{
			return true;
		}
	}
	return false;
}


int getWagon(int nomer,int N)//функция для ввода номера вагона 
{
	string wagon;
	cout << "Введите номер " << nomer + 1 << "го вагона ";
	cin >> wagon;


	while (isNumeric(wagon) == false || find_elem(stoi(wagon)) == true || stoi(wagon) == 0 || stoi(wagon) > N)
	{

		if (isNumeric(wagon) == true && stoi(wagon) != 0 || isNumeric(wagon) == true && stoi(wagon) > N )
		{
			if (isNumeric(wagon) == true && stoi(wagon) > N)
			{
				cout << "Вы не можете ввести номер больше "<< N << endl;
				cout << "Введите номер " << nomer + 1 << "го вагона заново ";
			}
			else
			{
				cout << "Данный вагон уже присутсвует " << endl;
				cout << "Введите номер " << nomer + 1 << "го вагона заново ";
			}
		}
		else
		{
			cout << "Вы ввели некорректные данные для "<<nomer+1 <<"го вагона " << endl;
			cout << "Введите номер " << nomer + 1 << "го вагона заново ";
		}

		cin >> wagon;
	}




	used_wagons.push_back(stoi(wagon));

	return stoi(wagon);

}


int main()
{
	string output;
	stack <int> deadlock;
	queue <int> train;


	setlocale(LC_ALL, "Russian");

	int N;
	int stop = 1;
	int count_of_wagons = 0;
	N = getChislo();//запрашиваем кол-во вагонов в поезде

	
	int wagon;

	for (int i = 0; i < N; i++)//запрашиваем номера вагонов 
	{	
		wagon = getWagon(i,N);
		train.push(wagon);

	}


	while (!train.empty()) //цикл постепенного взятия вагонов из тупика
	{
		wagon = train.front(); 
		train.pop();
		count_of_wagons++;
		deadlock.push(wagon);

		if (wagon == stop) //при нахождении минимального номера вагона начинаем выгрузку 
		{
			output += "1\t";
			output += to_string(count_of_wagons);
			output += '\n'; 

			count_of_wagons = 0; 


			while ((wagon == stop))//выгрузка вагонов из тупика
			{

				deadlock.pop();
				count_of_wagons++;

				if (stop == N)
				{
					break;
				}

				if (!deadlock.empty())
				{
					wagon = deadlock.top();
				}

				stop++;

			}
			output += "2\t";
			output += to_string(count_of_wagons);
			output += '\n'; 
			count_of_wagons = 0;

		}

	}

	cout << endl;
	if (train.empty() && deadlock.empty())
	{
		cout << output;
	}
	else
	{
		cout << "0";
	}
}


