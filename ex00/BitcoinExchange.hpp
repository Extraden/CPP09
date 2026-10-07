#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define DATABASE "./data.csv"

#include <string>
#include <map>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

    void loadDatabase(const std::string& database);
    void  exchange(const char *input);
    int  parseLine(const std::string& line, std::string& date, double& rate);

	private:
    std::map<std::string, double> rates;
};

#endif
