#include "RBTree.h"

int main()
{
    RBTree tree;
    do
    {
        system("cls");

        std::cout << "RED BLACK TREE: " << std::endl;
        std::cout << "1/ Add: " << std::endl;
        std::cout << "2/ Clear: " << std::endl;
        std::cout << "3/ Print: " << std::endl;
        std::cout << "4/ Search: " << std::endl;
        std::cout << "5/ Graphically Print: " << std::endl;

        int num, input;
        std::cin >> num;

        switch (num)
        {
        case 1:
            std::cout << "Enter a number you want to add in a tree: " << std::endl;
            std::cin >> input;

            tree.AddNode(input);
            break;
        case 2:
            tree.Clear();
            break;
        case 3:
            tree.Print();
            break;
        case 4:
            std::cout<<"Enter the number you want to search: "<<std::endl;
            std::cin >> input;
            if (tree.Search(input))
            {
                std:: cout << "There is " << input << " in this tree." << std::endl;
            }
            else
            {
                std::cout << input << " is not in the tree. " << std::endl;
            }
            break;
        case 5:
            system("cls");
            tree.Draw();
            break;            
        }  
        system("pause");
    } 
    while (true);
}

