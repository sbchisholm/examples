#ifndef __pqxx_example_h_included__
#define __pqxx_example_h_included__

#include <pqxx/pqxx>
#include <iostream>
#include <vector>
#include <string>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

namespace query {
  static const std::string readTableRowsQuery("SELECT col1 FROM table1");
  static const std::string insertTableRowsQuery("INSERT INTO table1(col1) VALUES('%1%')");
  static const std::string truncateTableQuery("TRUNCATE table1");
}

class ReadTableRows : public pqxx::transactor<>
{
  private:
    typedef pqxx::transactor<> Base;
  public:
    ReadTableRows(std::vector<std::string>& result, 
                  std::string name="ReadTableRows")
      : Base(name)
      , m_result(result)
    {}

    void operator() (argument_type& T)
    {
      pqxx::result result = T.exec(query::readTableRowsQuery);
      BOOST_FOREACH(pqxx::result::const_iterator row, result)
      {
        // add column1 data to the result vector, if the value is null use an
        // empty string as the default value.
        m_result.push_back(row["col1"].as<std::string>(""));
      }
    }

    void OnCommit()
    { std::cout << "Success!" << std::endl; }

    void OnAbort(const char Reason[]) throw ()
    { std::cout << "Aborted: " << Reason << std::endl; }

  private:
    std::vector<std::string>& m_result;
};

class InsertTableRows : public pqxx::transactor<>
{
  private:
    typedef pqxx::transactor<> Base;
    static const std::vector<std::string> values;
  public:
    InsertTableRows(std::string name="InsertTableRows")
      : Base(name)
    {}
    
    void operator() (argument_type& T)
    {
      BOOST_FOREACH(const std::string& value, values) {
        pqxx::result result = T.exec(
            boost::str(boost::format(query::insertTableRowsQuery) % value));
      }
    }

    void OnCommit()
    { std::cout << "Success!" << std::endl; }

    void OnAbort(const char Reason[]) throw ()
    { std::cout << "Aborted: " << Reason << std::endl; }
};

class TruncateTable : public pqxx::transactor<>
{
  private:
    typedef pqxx::transactor<> Base;
  public:
    TruncateTable(std::string name="TruncateTable")
      : Base(name)
    {}
    
    void operator() (argument_type& T)
    {
      pqxx::result result = T.exec(query::truncateTableQuery);
    }

    void OnCommit()
    { std::cout << "Success!" << std::endl; }

    void OnAbort(const char Reason[]) throw ()
    { std::cout << "Aborted: " << Reason << std::endl; }
};

#endif // __pqxx_example_h_included__
