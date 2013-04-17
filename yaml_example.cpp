
#include <yaml.h>

int main(int argc, char* argv[])
{
  // load the configuration file
  YAML::Node config = YAML::LoadFile(argv[1]);

  // get the database connection string
  std::cout 
    << "\"" 
    << config["DatabaseConnectionString"].as<std::string>() 
    << "\"" 
    << std::endl;

  return 0;
}
