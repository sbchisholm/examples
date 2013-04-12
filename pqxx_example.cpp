
#include "pqxx_example.h"

int main()
{

  // Connection string is giving as the first argument.
  pqxx::connection conn(argv[1]);
  std::vector<std::string> result;
  conn.perform(readTableRows(result));

  size_t idx = 0;
  BOOST_FOREACH(const std::string row, result)
    std::cout << idx++ << ": " << row << std::endl;

  return 0;
}
