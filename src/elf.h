#include <string>
#include <fstream>

class Elf {
 public:
  // for now, we only support filepath!!
  // in this function, it will do the io load task!!
  Elf(const std::string& filepath);
  ~Elf();

 private:
  std::ifstream *in_stream_ = nullptr;
  // return error msg.
  std::string checkMagic();
  // where define kMagic??
  const static char kMagic[];
};