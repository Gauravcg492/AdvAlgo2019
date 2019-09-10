//#include"src/splay_tree_implementation.cpp"
#include"src/bst.cpp"
#include<iostream>

int main()
{
	//splay_tree_implementation tree;
	BST bst;
	int c;
	node *temp;
	struct timespec start,end;
	clock_gettime(CLOCK_REALTIME,&start);
	for(int i=0;i<100000;i++)
	{
		c = rand()%3;
		int val = rand()%10000;
		//printf("Option: %d, element: %d\n",c,val);
		if(c==0)
		{
			temp = new node;
			bst.insert(root,temp);
		}
		if(c==1)
		{
 			bst.del(val);
		}
		if(c==2)
		{
			tree.find(val);
		}		 	
		// vector<int> vect = tree.post_order();
		// printf("%d) ",i+1);
		// for(auto j = vect.begin(); j != vect.end(); ++j)
		// {
		// 	printf("%d ",*j);
		// }
		// printf("\n");
	}
	clock_gettime(CLOCK_REALTIME,&end);
	double time = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)*0.000000001;
	printf("\n %.6f nano seconds.\n",time);
	return 0;
}
