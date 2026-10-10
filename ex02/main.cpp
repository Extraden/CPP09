#include <vector>
#include <deque>
#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    std::vector<int> numbers;

    try
    {
        parseArguments(argc, argv, numbers);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }

    std::vector<Item> items = intsToItems(numbers);

    std::deque<int> dequeNumbers(numbers.begin(), numbers.end());
    std::deque<Item> dequeItems = intsToItems(dequeNumbers);

    fordJohnson(items);
    fordJohnson(dequeItems);

    std::cout << "Vector: ";
    for (std::size_t i = 0; i < items.size(); ++i)
        std::cout << items[i].value << " ";
    std::cout << "\n";

    std::cout << "Deque:  ";
    for (std::size_t i = 0; i < dequeItems.size(); ++i)
        std::cout << dequeItems[i].value << " ";
    std::cout << "\n";

    return 0;
}
