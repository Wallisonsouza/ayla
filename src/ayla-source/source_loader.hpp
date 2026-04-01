#include <fstream>
#include <sstream>
#include <string>

namespace ayla::source {

class TextLoader {
public:
  static std::string load_file(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Erro ao abrir arquivo: " + filepath);

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
  }
};

} // namespace ayla::source