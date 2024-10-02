#include <iostream>
#include <kalam.h>
#include <vector>

const std::string ascii_chars = "@%#*+=-:. ";
const size_t ascii_chars_size = ascii_chars.size();

unsigned char adjustContrast(unsigned char value, float contrast) {
  double new_value = ((((value / 255.0) - 0.5) * contrast) + 0.5) * 255;
  return (new_value < 0) ? 0 : (new_value > 255) ? 255 : new_value;
}

char mapToAscii(unsigned char brightness) {
  // mapping ascii chars according to index
  int index = (brightness * (ascii_chars_size - 1)) / 255;
  return ascii_chars[index];
}

std::vector<unsigned char> rgbToGray(const kalam::Image &img, float contrast) {
  int width = img.getWidth();
  int height = img.getHeight();
  int channels = img.getChannels();
  const unsigned char *data = img.getData();

  std::vector<unsigned char> grayScaleImage(width * height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < height; j++) {
      int index = (j * width + i) * channels;
      unsigned char r = data[index];
      unsigned char g = data[index + 1];
      unsigned char b = data[index + 2];

      // weighted sum method
      unsigned char grayscale =
          static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);

      // make grayscale image
      grayScaleImage[j * width + i] = adjustContrast(grayscale, contrast);
    }
  }
  return grayScaleImage;
}

void generateAscii(const kalam::Image &img, float contrast) {
  // accessing image data with kalam funcs
  int width = img.getWidth();
  int height = img.getHeight();

  std::vector<unsigned char> grayImage = rgbToGray(img, contrast);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << "<image_file>" << std::endl;
    exit(1);
  }

  // this is how we load image object in kalam
  std::string imageFile = argv[1];
  kalam::Image img;

  // loading
  if (!img.load(imageFile) && !img.load(imageFile)) {
    std::cerr << "Error loading image." << std::endl;
    exit(1);
  }

  float contrast;
  argc > 2 ? contrast = std::stof(argv[2]) : contrast = 1.5;

  generateAscii(img, contrast);

  return 0;
}
