
#include "pqxx_example.h"
#include <boost/assign/list_of.hpp>

const std::vector<std::string> InsertTableRows::values = 
          boost::assign::list_of("row0")("row1")("row2")("row3")("row4")
                                ("row5")("row6")("row7")("row8")("row9");

int main(int argc, char* argv[])
{
  std::string connectionStr(argv[1]);

  pqxx::connection conn(connectionStr);
  std::vector<std::string> result;

  conn.perform(TruncateTable());
  conn.perform(InsertTableRows());
  conn.perform(ReadTableRows(result));

  size_t idx = 0;
  BOOST_FOREACH(const std::string row, result)
    std::cout << idx++ << ": " << row << std::endl;

  return 0;
}
