#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <locale>

int f;

struct Node
{
	int to;
	int incycle;

	Node(int to, int incycle) : to(to), incycle(incycle) {}
};

std::vector <std::vector<Node> > adjList;
std::vector<int> used;
std::vector<Node *> in;


void dfs(int vertex, int prev)
{
	used[vertex] = 1;
	for (int a = 0; a < adjList[vertex].size(); a++)
	{
		Node &node = adjList[vertex][a];
		int to = node.to;
		if (to == prev) continue;
		//std::cout << to;
		if (used[to] == 0)
		{
			in.push_back(&node);
			dfs(to, vertex);
			in.pop_back();
		}
		else
		{
			if (used[to] == 1)
			{
				f &= !node.incycle;
				node.incycle = 1;

				int q = 2;
				int ind = in.size()-1;
				while (in[ind]->to != node.to & ind > 0)
				{
					f &= !in[ind]->incycle;
					in[ind]->incycle = 1;
					ind--;
				}
			}
			if (!f) return;
		}
	}
	used[vertex] = 2;

}


void printadjlist(void)
{
	std::cout << "AdjList:" << std::endl;
	for (int i = 0; i < adjList.size(); i++)
	{
		std::cout << i << "-->";
		for (int a = 0; a < adjList[i].size(); a++)
		{
			std::cout << adjList[i][a].to << ", ";
		}
		std::cout << std::endl;
	}
}


void skip()
{
	system("pause");
	system("cls");
}


void start_test(std::string& name)
{
	adjList.clear();
	used.clear();
	in.clear();
	std::fstream file;
	int count_vertex, Nver, next;


	file.open(name, std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Ошибка открытия файла!\nВозможно вы ввели неправильно имя файла." << std::endl;
		skip();
	}
	else
	{
		file >> count_vertex;
		adjList.resize(count_vertex);
		used.resize(count_vertex);
		while (file >> Nver >> next)
		{
			adjList[Nver].push_back(Node(next, 0));
			adjList[next].push_back(Node(Nver, 0));
		}

		printadjlist();
		f = 1;
		dfs(0, -1);

		if (f)
		{
			std::cout << f << "---Этот граф является кактусом!" << std::endl;
			skip();
		}
		else
		{
			std::cout << f << "---Этот граф не является кактусом!" << std::endl;
			skip();
		}
	}
	file.close();
}




int main()
{
	setlocale(LC_ALL, "");
	int choose;
	bool start = true;
	std::string test_name;

	while (start)
	{

		std::cout << "Вариант: 1.17 Кактус\nПредставление графа: списки смежностей\nВcего 6 тестов.\nЧтобы запустить тест нужно ввести имя файла.\nПример: test1.txt" << std::endl;
		std::cin >> test_name;
		system("cls");

		start_test(test_name);

		std::cout << "Желаете провести новый тест?\n1.Да    2.Нет" << std::endl;
		std::cin >> choose;
		system("cls");

		switch (choose)
		{
		case 1:
		break;

		case 2:
			start = false;
		break;

		default:
			std::cout << "Нет такого пункта!" << std::endl;
			skip();
		}	
	}

	return 0;
}