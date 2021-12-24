// ((AV~B)^~(~C^A))V~(~DV~C)
// AB~VC~A^~^D~C~V~V
#include <iostream>
using namespace std;
struct Node
{
	char data;
	Node* next;
};
struct Node2
{
	int** tTable;
	Node2* next2;
};
Node* top = NULL;
Node2* top2 = NULL;
void push(char x)		//new node with value
{
	if (top == NULL)		//for first node
	{
		Node* newNode = new Node;
		newNode->next = NULL;
		top = newNode;
		newNode->data = x;
	}
	else					//if stack isnt empty
	{
		Node* newNode = new Node;
		newNode->next = top;
		top = newNode;
		newNode->data = x;
	}
}
void Push(int** truthTable, int row)
{
	Node2* newNode = new Node2;
	newNode->tTable = new int* [row];
	for (int i = 0; i < row; i++)
	{
		newNode->tTable[i] = new int[1];
	}
	if (top2 == NULL)		//for first node
	{
		newNode->next2 = NULL;
		top2 = newNode;
		for (int i = 0; i < row; i++)
		{
			newNode->tTable[i][0] = truthTable[i][0];
		}
	}
	else					//if stack isnt empty
	{
		newNode->next2 = top2;
		top2 = newNode;
		for (int i = 0; i < row; i++)
		{
			newNode->tTable[i][0] = truthTable[i][0];
		}
		
	}
}
bool isEmpty()			//checking if the stack is empty
{
	if (top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
char Pop()			//pops the top value in stack
{
	char value;
	value = top->data;
	top = top->next;
	return value;
}
int** pop(int row)			//pops the top value in stack
{
	int** TruthTable;
	TruthTable = new int* [row];
	for (int i = 0; i < row; i++)
	{
		TruthTable[i] = new int[1];
	}
	for (int i = 0; i < row; i++)
	{
		TruthTable = top2->tTable;
	}
	top2 = top2->next2;
	return TruthTable;
}
bool isOperator(char op)	//check for the operators in the string
{
	if (op == '~' || op == '^' || op == '⋀' || op == 'v' || op == 'V' || op == '(' || op == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}
int precedence(char op)	// checking the precedence
{
	if (op == 'v' || op == 'V')
	{
		return 1;		//lowest precrendence
	}
	else if (op == '^' || op == '⋀')
	{
		return 2;		//middle precedence
	}
	else if (op == '~')
	{
		return 3;		//highest precedence
	}
}
string ToPostFix(char* arr, int size)
{
	char pop;
	string fix;
	for (int i = 0; i < size; i++) //loop till end of string
	{
		if (isOperator(arr[i]))		//check if the character is operator
		{
			if (top == NULL)		//if the stack is empty
			{
				push(arr[i]);		//push the first operator
			}
			else if (arr[i] == '(')	//standard push incase of opening paranthesis
			{
				push(arr[i]);
			}
			else if (arr[i] == ')')  //handling when closing paranthesis found 
			{
				while (top->data != '(') //popping all till the starting bracket
				{
					pop = Pop();
					fix = fix + pop; //appending the postfix
				}
				Pop(); //popping the stack 
			}
			else if (precedence(arr[i]) > precedence(top->data)) //if precedence is greater simply push it
			{
				push(arr[i]);
			}
			else if (precedence(arr[i]) <= precedence(top->data))	//if precedence is equal or less
			{
				while (top != NULL &&  top->data != '(' )		//pop until starting bracket or stack is empty
				{
					fix = fix + Pop();
				}
				push(arr[i]);
			}
		}
		else
		{
			fix = fix + arr[i];
		}
	}
	while (top != NULL) //empty stack when the string ends
	{
		pop = Pop();
		fix = fix + pop;
	}
	return fix;
}
int checkMaxTerms(string postFix)
{
	int size = postFix.size();
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (postFix[i] == '~' || postFix[i] == '^' || postFix[i] == 'v' || postFix[i] == 'V' || postFix[i] == '(' || postFix[i] == ')')
		{}
		else
		{
			count++;
			for (int j = 0; j < count; j++)
			{
				if (postFix[count] == postFix[j])
				{
					count--;
				}
			}
		}
	}
	return count;
}
bool duplicate(char postFix,char*rowSym, int col)
{
	for (int i = 0; i < col; i++)
	{
		if (rowSym[i] == postFix)
		{
			return true;
		}
	}
	return false;
}
void createSymbolArray(string postFix, char*rowSym, int col)
{
	for (int i = 0; i < postFix.size(); i++)
	{
		if (isOperator(postFix[i]) == false)
		{
			for (int j = 0; j < col; j++)
			{
				if (rowSym[j] == 'Í')
				{
					if (duplicate(postFix[i], rowSym, col) == false)
					{
						rowSym[j] = postFix[i];
					}
				}
			}
		}
	}
}
int checkColumn(char* rowSym,char postFix,int col,int size)
{
	int traverse = 0;
	for (int j = 0; j < col; j++)
	{
		if (postFix == rowSym[j])
		{
			traverse = j;
			return traverse;
		}
	}
}
int** AND(int **result, int** process, int row)
{
	for (int i = 0; i < row; i++)
	{
		if (process[i][0] == 1 && result[i][0] == 1)
		{
			result[i][0] = 1;
		}
		else
		{
			result[i][0] = 0;
		}
	}
	return result;
}
int** OR(int** result, int** process, int row)
{
	for (int i = 0; i < row; i++)
	{
		if (process[i][0] == 1 || result[i][0] == 1)
		{
			result[i][0] = 1;
		}
		else if(process[i][0] == 0 && result[i][0] == 0)
		{
			result[i][0] = 0;
		}
	}
	return result;
}
int** NOT(int** result, int row)
{
	for (int i = 0; i < row; i++)
	{
		if (result[i][0] == 1)
		{
			result[i][0] = 0;
		}
		else if (result[i][0] == 0)
		{
			result[i][0] = 1;
		}
	}
	return result;
}
void Table(int maxTerms, string postFix)
{
	int size = postFix.size();
	int** Table;
	int** Result;
	int** Process;
	int** Negation;
	int row, col, div = 0;
	col = maxTerms;
	row = pow(2,maxTerms);
	int fill = col - 1;
	int divNum;
	int traverse;
	char currentChar;
	int currentCol;
	Table = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Table[i] = new int[col];
	}
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (i == 0)
			{
				if (j < row / 2)
				{
					Table[j][i] = 1;
				}
				else
				{
					Table[j][i] = 0;
				}
			}	
		}
	}
	for (int i = 1; i < col; i++)
	{
		int index = 0;
		int indexNext = 0;
		int check = 0;
		if (i == (col - fill))
		{
			div = pow(2, ((col - i) - 1));
			divNum = row / div;
			indexNext = div;
		}
		while (check < divNum)
		{
			if (check % 2 == 0)
			{
				for (int j = index; j < indexNext; j++)
				{
					Table[j][i] = 1;
				}
				index = index + div;
				indexNext = indexNext + div;
			}
			else
			{
				for (int j = index; j < indexNext; j++)
				{
					Table[j][i] = 0;
				}
				index = index + div;
				indexNext = indexNext + div;
			}
			check++;
		}
		fill--;
	}
	Result = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Result[i] = new int[1];
	}
	Process = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Process[i] = new int[1];
	}
	Negation = new int* [row];
	for (int i = 0; i < row; i++)
	{
		Negation[i] = new int[1];
	}
	char* rowSym = new char[col];
	createSymbolArray(postFix, rowSym, col);
	for (int i = 0; i < size; i++)
	{
		if (isOperator(postFix[i]) == false)
		{
			currentCol = checkColumn(rowSym, postFix[i], col, size);
			postFix[i] = char(currentCol) + 48;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (isOperator(postFix[i]) == false)
		{
			currentCol = int(postFix[i]) - 48;
			for (int j = 0; j < row; j++)
			{
				Process[j][0] = Table[j][currentCol];
			}
			Push(Process, row);
		}
		else
		{
			if (postFix[i] == '~')
			{
				Negation = NOT(pop(row), row);
				Push(Negation, row);
			}
			else if (postFix[i] == 'v' || postFix[i] == 'V')
			{
				Result = OR(pop(row), pop(row), row);
				Push(Result, row);
			}
			else if (postFix[i] == '^')
			{
				Result = AND(pop(row), pop(row), row);
				Push(Result, row);
			}
		}
	}
	while (top2 != NULL)
	{
		Result = pop(row);
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << Table[i][j] << " ";
		}
		cout << Result[i][0] << " " << endl;
	}
}
int main()
{
	const int size = 100;
	char arr[size] = { NULL };
	string postFix;
	int maxTerms = 0;
	cout << "Enter an Expression to evluate: ";
	cin >> arr;
	int length = 0;
	for (int i = 0; i < 100; i++)
	{
		if (arr[i] != NULL)
		{
			length++;
		}
	}
	postFix = ToPostFix(arr, length);
	maxTerms = checkMaxTerms(postFix);
	Table(maxTerms, postFix);
	return 0;
}
