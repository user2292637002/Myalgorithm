#include"KMP.h"

int main()
{
	string str = "sad";
	string pattern = "sad";
	int index = kmp(str, pattern);
	cout << "Pattern found at index: " << index << endl;
	return 0;
}