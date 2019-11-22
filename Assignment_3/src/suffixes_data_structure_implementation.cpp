#include "../include/suffixes_data_structure.hpp"
using namespace std;

typedef struct node{
    struct node *nodes[128];
    vector<pair<int,int>> indexes;
    string edge;
    int counter;
}node;

class suffixes_data_structure_implementation : public suffixes_data_structure
{
private:
    node* root;
public:
    suffixes_data_structure_implementation();
    void build(vector<string> input);
    search_results search(string query);
    node* create_node(int pos,int docNo,string str);
    node* create_node(int pos,string str,pair<int,int> index);
    node* create_node(int ind, int pos,int docNo,string str);
    void create_internal_node(node* node,string str,int docNo,int ind);
    void extend_tree(string str,int docNo);
    void extend_nodes(string str,int docNo,int ind);
    ~suffixes_data_structure_implementation();
};

suffixes_data_structure_implementation::suffixes_data_structure_implementation()
{
    root = create_node(0,0,"");
}

void suffixes_data_structure_implementation::build(vector<string> input)
{
    for(int i=0; i<input.size(); i++)
    {
        extend_tree(input[i],i);
    }    
}

void suffixes_data_structure_implementation::extend_tree(string str, int docNo)
{
    int pos = 0;
    if(root->nodes[str[0]] == NULL)
    {
        root->nodes[str[0]] = create_node(pos,docNo,str);
        for(int i=1;i<str.length();i++)
        {
            extend_nodes(str,docNo,i);
        }
    }
}

void suffixes_data_structure_implementation::extend_nodes(string str,int docNo,int ind)
{
    if(root->nodes[str[ind]] == NULL)
    {
        root->nodes[str[ind]] == create_node(ind,docNo,str); 
    }
    else
    {
        create_internal_node(root->nodes[str[ind]],str,docNo,ind);
    }    
}

node* suffixes_data_structure_implementation::create_node(int pos,int docNo,string str)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->indexes.push_back(make_pair(docNo,pos));
    temp->edge.assign(str,pos,string::npos);
    temp->nodes[36] = (node*)malloc(sizeof(node));
    temp->nodes[36]->indexes.push_back(make_pair(docNo,pos));
}

node* suffixes_data_structure_implementation::create_node(int pos,string str,pair<int,int> index)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->indexes.push_back(index);
    temp->edge.assign(str,pos,string::npos);
    temp->nodes[36] = (node*)malloc(sizeof(node));
    temp->nodes[36]->indexes.push_back(index);
}

node* suffixes_data_structure_implementation::create_node(int ind,int pos,int docNo,string str)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->indexes.push_back(make_pair(docNo,ind));
    temp->edge.assign(str,pos,string::npos);
    temp->nodes[36] = (node*)malloc(sizeof(node));
    temp->nodes[36]->indexes.push_back(make_pair(docNo,ind));
}

void suffixes_data_structure_implementation::create_internal_node(node* node,string str,int docNo,int ind)
{
    int i = 0;
    string str1 = node->edge;
    while((i < str1.length()) && ((ind + i) < str.length()) && (str1[i] == str[ind+i]))
    {
        i++;
    }
    node->edge.assign(str1,0,i);
    node->nodes[str1[i]] = create_node(i,str1,node->indexes[0]);
    node->nodes[str[ind+i]] = create_node(ind,ind+i,docNo,str);
}