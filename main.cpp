#include <iostream>
#include <kalam.h>

const std::string ascii_chars = "@%#*+=-:. ";

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <image_file>" << std::endl;
    exit(1);
  }

  std::string imageFile = argv[1];

  // this is how we load image object in kalam
  kalam::Image img;
}
