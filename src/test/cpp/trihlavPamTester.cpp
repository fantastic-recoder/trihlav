#include <string>
#include <iostream>
#include <trihlavLib/trihlavOsIface.hpp>

#include <unistd.h>

using std::string;
using std::endl;
using std::cerr;

using trihlav::OsIface;

int main(int argc, char** argv)
{
  if(argc != 2) {
      cerr<< "Usage: check_user <username>" << endl;
      exit(1);
  }
  string username{argv[1]};

  char* myPswd=getpass("Password: ");
  // *** Get the password by any method, or maybe it was passed into this function.
  string password{myPswd};
  OsIface myOsIface;
  int retval=myOsIface.checkOsPswd(username,password);
  return retval;
}




