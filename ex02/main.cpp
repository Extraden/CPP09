#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <iostream>
#include <iomanip>
#include <exception>
#include <sys/time.h>

static double elapsedUs(const timeval& start,
                        const timeval& end)
{
    return (end.tv_sec - start.tv_sec) * 1000000.0
         + (end.tv_usec - start.tv_usec);
}

int main(int argc, char *argv[])
{
    std::vector<int> numbers;

    try
    {
        parseArguments(argc, argv, numbers);

        std::cout << "Before:";
        for (std::size_t i = 0; i < numbers.size(); ++i)
            std::cout << " " << numbers[i];
        std::cout << "\n";

        timeval start, end;

        // Vector: preparation + sorting
        gettimeofday(&start, NULL);

        std::vector<Item> items = intsToItems(numbers);
        fordJohnson(items);

        gettimeofday(&end, NULL);
        double vectorTime = elapsedUs(start, end);

        // Deque: preparation + sorting
        gettimeofday(&start, NULL);

        std::deque<int> dequeNumbers(numbers.begin(),
                                     numbers.end());
        std::deque<Item> dequeItems = intsToItems(dequeNumbers);
        fordJohnson(dequeItems);

        gettimeofday(&end, NULL);
        double dequeTime = elapsedUs(start, end);

        // Check both containers produced the same result
        for (std::size_t i = 0; i < items.size(); ++i)
        {
            if (items[i].value != dequeItems[i].value)
                throw std::runtime_error("Error: results differ");
        }

        std::cout << "After:";
        for (std::size_t i = 0; i < items.size(); ++i)
            std::cout << " " << items[i].value;
        std::cout << "\n";

        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Time to process a range of "
                  << numbers.size()
                  << " elements with std::vector : "
                  << vectorTime << " us\n";

        std::cout << "Time to process a range of "
                  << numbers.size()
                  << " elements with std::deque : "
                  << dequeTime << " us\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
