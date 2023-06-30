#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <Windows.h>


void bracket_analysis(std::string& s, std::vector<int>& error);
void checking_for_errors(std::string& s, std::vector<int>& error);

int main()
{
	setlocale(LC_ALL, "ru");

	std::string str = "";
	std::vector<int>error;

	std::cout << "F.A.Q. Чтобы прекратить записывать текст, введите символ \"~\" и нажмите \"Enter\"\n";
	std::cout << "Введите текст:\n";
	std::getline(std::cin, str, '~');

	bracket_analysis(str, error);

	checking_for_errors(str, error);

	return 0;
}

void bracket_analysis(std::string& s, std::vector<int>& error)
{
	std::stack<char>st;
	int i = 0;//счётчик символов в строке
	int j = 0;//счётчик скобок

	for (auto it : s)
	{
		if (it == '(' || it == ')' || it == '{' || it == '}' || it == '[' || it == ']') {
			j = i;
			if (st.empty()) {
				st.push(it);
			}
			else {
				if (st.top() == '(') {
					if (it == ')') {
						st.pop();
					}
					else if (it == '}') {
						error.push_back(i);
					}
					else if (it == ']') {
						error.push_back(i);
					}
					else {
						st.push(it);
					}
				}
				else if (st.top() == '{') {
					if (it == '}') {
						st.pop();
					}
					else if (it == ')') {
						error.push_back(i);
					}
					else if (it == ']') {
						error.push_back(i);
					}
					else {
						st.push(it);
					}
				}
				else if (st.top() == '[') {
					if (it == ']') {
						st.pop();
					}
					else if (it == ')') {
						error.push_back(i);
					}
					else if (it == '}') {
						error.push_back(i);
					}
					else {
						st.push(it);
					}
				}
				else {
					error.push_back(i);
				}

			}
		}
		i++;
	}

	if (!st.empty())
		error.push_back(j);

}

void checking_for_errors(std::string& s, std::vector<int>& error)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (error.empty()) {
		std::cout << "\n\nОшибок нет!";
	}
	else {
		std::cout << "\n\nОбнаружилось " << error.size() << " ошибок:\n\n";

		for (int i = 0, j = 0; i < s.length(); i++)
		{
			if (error.size() - 1 >= j && i == error[j]) {
				SetConsoleTextAttribute(hStdOut, BACKGROUND_RED);
				std::cout << s[i];
				SetConsoleTextAttribute(hStdOut, 15 | 0);
				j++;
			}
			else {
				std::cout << s[i];
			}
		}
	}

}
