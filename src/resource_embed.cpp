#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
  try {
    // Parse program arguments
    if (argc != 4) {
      std::cerr
        << "USAGE: <symbName> <inputName> <outputName>\n"
        << "\tCreates <outputName>.cpp with an embedded raw string\n "
        << "\tliteral named <symbName>, holding the contents of <inputName>"
        << std::endl;
      throw std::runtime_error("Wrong nr. of arguments!");
    }
    const std::string symbolName = argv[1];
    const std::string inputName = argv[2];
    const std::string outputName = argv[3];

    // Create input file stream matching to inputName
    std::ifstream input(inputName, std::ios::in);
    if (!input) {
      throw std::runtime_error("Could not read input " + std::string(inputName));
    }

    // Create output file stream matching to outputName
    std::ofstream output(outputName, std::ios::out);
    if (!output) {
      throw std::runtime_error("Could not read output " + std::string(outputName));
    }

    // Copy over output contents with input file contents prepended as a const char*
    output << "const char* " << symbolName << " = R\"RSRCDELIM(\n" << input.rdbuf() << "\n)RSRCDELIM\";\n";

    std::cout << "Embedded " << symbolName << " from file " << inputName
              << " into file " << outputName << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Exception thrown:" << '\n\t' << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}