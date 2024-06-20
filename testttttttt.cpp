#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
void ENTER(stack<char> &Undo,char X)
{
	Undo.push(X);
}
void UNDO(stack<char>& Undo,stack<char>& Redo)
{
	char X = Undo.top();
	Undo.pop();
	Redo.push(X);
}
void REDO(stack<char>& Undo,stack<char>& Redo)
{
	char X = Redo.top();
	Redo.pop();
	Undo.push(X);
}
void PRINT(stack<char> Undo)
{
	stack<char> revOrder;
	while (!Undo.empty()) {
		revOrder.push(Undo.top());
		Undo.pop();
	}

	while (!revOrder.empty()) {
		cout << revOrder.top();
	Undo.push(revOrder.top());
		revOrder.pop();
	}

	cout << " ";
}

void PERFORM(vector<string> P)
{   
	stack <char> Undo;
	stack <char> Redo;
	int N = P.size();
	for (int i = 0; i < N; i++) {
		if (P[i] == "UNDO") {
			UNDO(Undo, Redo);
		}
		else if (P[i] == "REDO") {
			REDO(Undo, Redo);
		}
		else if (P[i] == "PRINT") {
			PRINT(Undo);
		}
		else {
			ENTER(Undo, P[i][6]);
		}
	}
}
int main()
{
	vector<string> P = { "ENTER A", "ENTER B",
						"ENTER C", "UNDO",
						"PRINT", "REDO", "PRINT" };
	PERFORM(P);
	return 0;
}
