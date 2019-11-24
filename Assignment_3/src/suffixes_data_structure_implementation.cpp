#include "../include/suffixes_data_structure.hpp"
#include <iostream>
using namespace std;

typedef struct node
{
    struct node *nodes[128];
    vector<pair<int, int>> indexes;
    string edge;
    int counter;
} node;

class suffixes_data_structure_implementation : public suffixes_data_structure
{
private:
    node *root;

public:
    suffixes_data_structure_implementation();
    void build(vector<string> input);
    search_results search(string query);
    search_results search_internal(string str, int ind, node *node);
    node *create_node(int pos, int docNo, string str);
    node *create_node(int pos, string str, vector<pair<int, int>> index);
    node *create_node(int ind, int pos, int docNo, string str);
    void create_internal_node(node *node, string str, int docNo, int ind);
    void extend_tree(string str, int docNo);
    void extend_nodes(string str, int docNo, int ind);
    ~suffixes_data_structure_implementation();
};

suffixes_data_structure_implementation::suffixes_data_structure_implementation()
{
    string temp = "";
    root = create_node(0, 0,temp);
}

void suffixes_data_structure_implementation::build(vector<string> input)
{
    for (int i = 0; i < input.size(); i++)
    {
        extend_tree(input[i], i);
    }
}

void suffixes_data_structure_implementation::extend_tree(string str, int docNo)
{
    int pos = 0;
    if (root->nodes[str[0]] == NULL)
    {
        cout<<"Entering extend tree\n";
        root->nodes[str[0]] = create_node(pos, docNo, str);
        for (int i = 1; i < str.length(); i++)
        {
            extend_nodes(str, docNo, i);
        }
    }
}

void suffixes_data_structure_implementation::extend_nodes(string str, int docNo, int ind)
{
    if (root->nodes[str[ind]] == NULL)
    {
        root->nodes[str[ind]] == create_node(ind, docNo, str);
    }
    else
    {
        create_internal_node(root->nodes[str[ind]], str, docNo, ind);
    }
}

node *suffixes_data_structure_implementation::create_node(int pos, int docNo, string str)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->indexes.push_back(make_pair(docNo, pos));
    if(str.length() == 0)
    {
        temp->edge = str;
    }
    else{
        temp->edge = str.substr(pos);
    }
    temp->nodes[36] = (node *)malloc(sizeof(node));
    temp->nodes[36]->indexes.push_back(make_pair(docNo, pos));
    return temp;
}

node *suffixes_data_structure_implementation::create_node(int pos, string str, vector<pair<int, int>> index)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->indexes = index;
    temp->edge = str.substr(pos);
    temp->nodes[36] = (node *)malloc(sizeof(node));
    temp->nodes[36]->indexes = index;
    return temp;
}

node *suffixes_data_structure_implementation::create_node(int ind, int pos, int docNo, string str)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->indexes.push_back(make_pair(docNo, ind));
    temp->edge = str.substr(pos);
    temp->nodes[36] = (node *)malloc(sizeof(node));
    temp->nodes[36]->indexes.push_back(make_pair(docNo, ind));
    return temp;
}

void suffixes_data_structure_implementation::create_internal_node(node *node, string str, int docNo, int ind)
{
    int i = 0;
    string str1 = node->edge;
    while ((i < str1.length()) && ((ind + i) < str.length()) && (str1[i] == str[ind + i]))
    {
        i++;
    }
    if (i == str1.length() && ind + i < str.length())
    {
        node->nodes[str[ind + i]] = create_node(ind, ind + i, docNo, str);
    }
    else if (ind + i == str.length() && i < str1.length())
    {
        //node->edge.assign(str1, 0, i);
        node->edge = str1.substr(0,i);
        node->indexes.clear();
        node->indexes.push_back(make_pair(docNo, ind));
        node->nodes[str[i]] = create_node(i, str1, node->indexes);
    }
    else if (i < str1.length() && ind + i < str.length() && str[i] != str[ind + i])
    {
        node->edge = str1.substr(0,i);
        node->nodes[str1[i]] = create_node(i, str1, node->indexes);
        node->nodes[str[ind + i]] = create_node(ind, ind + i, docNo, str);
    }
    else
    {
        node->nodes[36]->indexes.push_back(make_pair(docNo, ind));
    }
}

search_results suffixes_data_structure_implementation::search(string query)
{
    search_results results;
    //full search
    if (root->nodes[query[0]] != NULL)
    {
        results = search_internal(query, 0, root->nodes[query[0]]);
    }
    else
    {
        results.matched_string = "";
        results.indices.clear();
    }
    return results;
}

search_results suffixes_data_structure_implementation::search_internal(string str, int ind, node *node)
{
    search_results results;
    int ql = str.length() - ind;
    string str1 = node->edge;
    int sl = str1.length();
    int min = sl < ql ? sl : ql;
    int i = 0;
    while (i < min && str[ind + i] == str1[i])
    {
        i++;
    }
    if (i == min && sl == ql) //full match
    {
        //results.matched_string.assign(str, ind, string::npos);
        results.matched_string = str.substr(ind);
        results.indices = node->nodes[36]->indexes;
        return results;
    }
    else if (i == min && sl < ql)
    {
        if (node->nodes[str[i]] != NULL)
        {
            search_results temp = search_internal(str, i, node->nodes[str[i]]);
            results.indices = temp.indices;
            //results.matched_string.assign(str, ind, ind + i);
            results.matched_string = str.substr(ind,ind+i);
            results.matched_string.append(temp.matched_string);
            return results;
        }
    }

    //results.matched_string.assign(str, ind, ind + i);
    results.matched_string = str.substr(ind,ind+i);
    results.indices.push_back(node->indexes[0]);
    return results;
}

suffixes_data_structure_implementation::~suffixes_data_structure_implementation()
{
    free(root);
}