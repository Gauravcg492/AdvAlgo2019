#include "src/suffixes_data_structure_implementation.cpp"
#include "include/suffixes_data_structure.hpp"

int main()
{
    vector<string> input;
    //input.push_back("It has survived not only five centuries.");
    //input.push_back("Contrary to popular belief, Lorem Ipsum is not simply.");
    input.push_back("hello");
    input.push_back("hello");
    suffixes_data_structure_implementation test_obj;
    test_obj.build(input);
    return 0;
}