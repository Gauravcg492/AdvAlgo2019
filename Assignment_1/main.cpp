#include "src/dynamic_array_implementation.cpp"
//#include "src/splay_tree_implementation.hpp"
#include <iostream>
#include<time.h>

using namespace std;

//You can test/use your code here.
/*int main()
{
    //dynamic_array_implementation array;
	splay_tree_implementation test;
	int ele,op;
	while(1)
	{
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				{
					scanf("%d",&ele);
					printf("");
				}
		}
	}
	
    //Output should be 1
    //array.append(1);
    //cout<<array.get(0);
    return 0;
}*/

int main()
{
	dynamic_array_implementation array;
	//array.set_increase_factor_table_size(1.5);
	//array.set_load_factor_reduction(0.333);
	int c;
	struct timespec start,end;
	srand(time(0));
	clock_gettime(CLOCK_REALTIME,&start);
	for(int i=0;i<100000;i++)
	{
		c = rand()%2;
		if(c==0)
		{
			array.append(rand());
		}
		if(c==1)
		{
			if(array.get_size() > 0)
			{
				array.pop();
			}
		}
	}
	clock_gettime(CLOCK_REALTIME,&end);
	double time = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
	printf("\n %.6f nano seconds.\n",time);
	return 0;
}
