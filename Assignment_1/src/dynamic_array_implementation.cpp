#include "../include/dynamic_array.hpp"
#include<cmath>

using namespace std;

//Given just for reference. Only the class name and function names should match.
class dynamic_array_implementation : public dynamic_array
{
private:
    int size;
    int capacity;
    int *arr;
    double increase_factor;
    double decrease_factor;

public:
    dynamic_array_implementation();
    int get_size();
    int get_capacity();
    void set_increase_factor_table_size(double);
    void set_load_factor_reduction(double);
    void append(int);
    void pop();
    int get(int);
    ~dynamic_array_implementation();
};

dynamic_array_implementation::dynamic_array_implementation()
{
    size = 0;
    capacity = 0;
    increase_factor = 2;
    decrease_factor = 0.25;
}
int dynamic_array_implementation::get_size()
{
    return size;
}
int dynamic_array_implementation::get_capacity()
{
    return capacity;
}

void dynamic_array_implementation::set_increase_factor_table_size(double increase_factor)
{
	this->increase_factor = increase_factor;
    return;
}
void dynamic_array_implementation::set_load_factor_reduction(double decrease_factor)
{
	this->decrease_factor = decrease_factor;
    return;
}

void dynamic_array_implementation::append(int element)
{
	if(capacity == 0)
	{
		capacity = 1;
		arr = (int*)malloc(sizeof(int)*capacity);
	}
	if(capacity <= size)
	{		
		capacity =(int) ceil(capacity * increase_factor);
			
		int *temp = (int*)malloc(sizeof(int)*capacity);
		if(temp == NULL)
		{
			throw runtime_error("Allocation Failed");
		}
		for(int i=0; i<size; i++)
		{
			temp[i] = arr[i];
		}
		free(arr);
		arr = temp;	
	}
	arr[size++] = element;
    return;
}

void dynamic_array_implementation::pop()
{
	if(capacity*decrease_factor >= size)
	{
		if(size == 0 )
		{
			cout<<"No elements to pop.\n";
		}
		else
		{
			capacity =(int) ceil(capacity * (increase_factor * decrease_factor));
		}
		int *temp = (int*)malloc(sizeof(int)*capacity);
		for(int i=0; i<size; i++)
		{
			temp[i] = arr[i];
		}
		free(arr);
		arr = temp;
	}
	size--;
	if(size == 0)
	{
		capacity = 0;
	}
    return;
}
int dynamic_array_implementation::get(int index)
{
	if(index >= size || index < 0)
	{
		cout<<"Out of bound";
		return 0;
	}
    return arr[index];
}

dynamic_array_implementation::~dynamic_array_implementation()
{
    if (capacity > 0)
    {
        delete[] arr;
    }
}
