

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/fusion/algorithm.hpp>

#define SOCI_USE_BOOST
#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>

#include <iostream>
#include <vector>
#include <string>
#include <exception>

const std::vector<std::string> values = 
        boost::assign::list_of("row0")("row1")("row2")("row3")("row4")
                              ("row5")("row6")("row7")("row8")("row9");
namespace query {
  const std::string truncateTable("TRUNCATE table1");
  const std::string insertTableRows(
      "INSERT INTO table1(col1, col2) VALUES(:value, :idx)");
  const std::string countTableRows("SELECT count(*) FROM table1");
  const std::string readTableRows("SELECT col1, col2 FROM table1");
}

int main(int argc, char* argv[])
{
  tuple: boost::tuple<std::string, int>  result;

  try {
    soci::session conn(soci::postgresql, argv[1]);

    conn << query::truncateTable;

    size_t idx = 0;
    BOOST_FOREACH(const std::string& value, values) {
      std::cout << "inserting (" << value << ", " << idx << ")" << std::endl;
      conn << query::insertTableRows, soci::use(value, "value"),
                                      soci::use(idx++, "idx");
    }

    conn << query::readTableRows, soci::into(result);
  }
  catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << '\n';
  }
  
  //tuple: std::cout << result.get<1>() << ": " << result.get<0>() << std::endl;
  std::cout << boost::fusion::at_c<1>(result) << ": " 
            << boost::fusion::at_c<0>(result) << std::endl;

  boost::fusion::for_each(result, std::cout << boost::lambda::_1 << ' ');

  std::cout << std::endl;

  return 0;
}

