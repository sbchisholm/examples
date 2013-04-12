#ifndef __pqxx_example_h_included__
#define __pqxx_example_h_included__

#include <pqxx/pqxx>
#include <iostream>
#include <vector>
#include <string>
#include <boost/foreach.hpp>

class ReadTableRows : pqxx::transactor<>
{
  public:
    ReadTableRows(std::vector<std::string>& result, 
                  std::string name="ReadTableRows")
      : transactor<>(name)
      , m_result(result)
    {}

    void operator() (TRANSACTION& T)
    {
      pqxx::result result = T.exec("SELECT col1 FROM table1");
      BOOST_FOREACH(pqxx::result::const_iterator row, result)
      {
        std::string s;
        if(row["col1"].to(s)) m_result.push_back(s);
      }
    }

    void OnCommit()
    { std::cout << "Success!" << std::endl; }

    void OnAbort(const char Reason[]) throw ()
    { std::cout << "Aborted: " << Reason << std::endl; }

  private:
    std::vector<std::string>& m_result;
};

#endif // __pqxx_example_h_included__
