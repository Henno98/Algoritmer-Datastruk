// Compulsory1_2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>

int Sol;
int Sol1;
int Solution=1;
int BsNR = 1;
int PrNR;
int NwNR;
void Recurve(int n)
{
	 
		Sol = n;
		Sol1 = Solution;

		if (n == 1)
		{
			Sol1 = n;
		}
		else
		{
			Solution = Sol1 * Sol;
			Recurve(n - 1);
		}
	
};

void FibSeq(int u)
{
	for (int j = 0; j < u; j++) 
	{
		NwNR = PrNR + BsNR;
		PrNR = NwNR;
		BsNR = PrNR - BsNR;
		std::cout << "FibSeq number " << j <<" is:" << NwNR <<"\n";
	}
}

void InvertStack(std::stack<int>& st,int topnr)
{	if(st.empty()==true)
	st.push(topnr);
	else
	{
	int k = st.top();
	st.pop();
	InvertStack(st, topnr);
	st.push(k);
	}

}

void StackTest(int c)
{
	
	std::stack<int> Stack;

		Stack.push(2);
		Stack.push(8);
		Stack.push(5);
		Stack.push(3);
		Stack.push(7);
		Stack.push(12);

	if (Stack.empty() == false) {
		if (Stack.size() < c)
		{
			std::cout << "Stack is empty number does not exist\n";
			return;
		}
		//pops the stack
		for (int i = Stack.size(); i > c; i--)
			{
				Stack.pop();
			}
		if (Stack.empty() == true)
		{
			return;
		}
		//print
		int TopNr = Stack.top();
		std::cout << "stack number in spot "<< Stack.size() << "is" << Stack.top() << "\n";
			StackTest(c - 1);

			InvertStack(Stack,TopNr);
		
	}
}


int main()
{

	

    std::cout << "Hello World!\n";

	Recurve(6);
	std::cout << "Recurse result is:" << Solution <<"\n";

	FibSeq(12);
	std::cout << "FibSeq result is:" << NwNR << "\n";

	StackTest(6);
	
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
