# // ((AV~B)^~(~C^A))V~(~DV~C)
#include <iostream>
using namespace std;
struct Node
{
	char data;
	Node* next;
};
Node* top = NULL;
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
		return 2;		//lowest precrendence
	}
	else if (op == '^' || op == '⋀')
	{
		return 3;		//middle precedence
	}
	else if (op == '~')
	{
		return 4;		//highest precedence
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
void AND()
{

}
void OR()
{

}
void NOT()
{

}
void Table(int maxTerms, string postFix)
{
	int size = postFix.size();
	char** Table;
	char** Result;
	int row, col, div = 0;
	col = maxTerms;
	row = pow(2,maxTerms);
	int fill = col - 1;
	int divNum;
	Table = new char* [row];
	for (int i = 0; i < row; i++)
	{
		Table[i] = new char[col];
	}
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (i == 0)
			{
				if (j < row / 2)
				{
					Table[j][i] = 'T';
				}
				else
				{
					Table[j][i] = 'F';
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
					Table[j][i] = 'T';
				}
				index = index + div;
				indexNext = indexNext + div;
			}
			else
			{
				for (int j = index; j < indexNext; j++)
				{
					Table[j][i] = 'F';
				}
				index = index + div;
				indexNext = indexNext + div;
			}
			check++;
		}
		fill--;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << Table[i][j] << " ";
		}
		cout << endl;
	}

	Result = new char* [row];
	for (int i = 0; i < row; i++)
	{
		Result[i] = new char[1];
	}
	for (int i = 0; i < size; i++)
	{
		if (isOperator(postFix[i]) == false)
		{
			push(postFix[i]);
		}
		else if (postFix[i] == '~')
		{

		}
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
	cout << "Num of variables is: " << maxTerms << endl;
	cout << "Expression is: " << postFix << endl;
	Table(maxTerms, postFix);
	return 0;
}
