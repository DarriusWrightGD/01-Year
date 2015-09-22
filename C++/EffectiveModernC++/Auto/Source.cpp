#include <iostream>

//what is a unversial reference

template<typename T>
void foo( T && param)
{
	std::cout << param << std::endl;
}

int main()
{
	const int n1 = 34;
	int foobar();
	int j = foobar();

	foo(j);
	system("pause");
	return 0;
}

int foobar()
{
	return 23;
}