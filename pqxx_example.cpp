
#include "pqxx_example.h"

int main(int argc, char* argv[])
{

  // Connection string is giving as the first argument.
  pqxx::connection conn(argv[1]);
  std::vector<std::string> result;
  conn.perform(ReadTableRows(result), 10);

  size_t idx = 0;
  BOOST_FOREACH(const std::string row, result)
    std::cout << idx++ << ": " << row << std::endl;

  return 0;
}
