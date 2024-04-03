#include <iostream>
#include <vector>

class Task1J {
public:
  Task1J();
  void test(std::istream &input = std::cin);
};

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

Task1J::Task1J() {}

struct Rect {
  size_t x;
  size_t y;
  size_t width;
  size_t height;

  Rect(const Rect &other)
      : x(other.x), y(other.y), width(other.width), height(other.height) {}

  Rect(size_t x, size_t y, size_t width, size_t height)
      : x(x), y(y), width(width), height(height) {}

  bool operator==(const Rect &other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const Rect &other) const {
    if (x != other.x) {
      return x < other.x;
    } else if (y != other.y) {
      return y < other.y;
    } else if (width != other.width) {
      return width < other.width;
    }
    return height < other.height;
  }
};

set<Rect> surroundedSet;

enum class ImageType { Embedded = 0, Surrounded = 1, Floating = 2 };

map<string, ImageType> stringToImageType{
    {"embedded", ImageType::Embedded},
    {"surrounded", ImageType::Surrounded},
    {"floating", ImageType::Floating},
};

struct Image {
  size_t width;
  size_t height;
  ImageType layout;
  int dx;
  int dy;
  int beginX;
  int beginY;
};

struct Word {
  int letterCount;
};

enum class ElementType {
  Word = 0,
  Image = 1,
};

struct Element {
  ElementType type;
  Word word;
  Image image;
};

struct Paragraph {
  vector<Element> elements;
};

struct Fragment {
  size_t x;
  size_t y;
  size_t width;
  size_t height;
  bool empty;
  bool isExtended;

  Fragment()
      : x(0), y(0), width(0), height(0), empty(true), isExtended(false) {}

  void toNewLine(size_t h) {
    x = 0;
    y += height;
    width = 0;
    height = h;
    empty = true;
  }
};

struct Document {
  vector<Paragraph> paragraphs;
  vector<Fragment> fragments;
  const size_t pageWidth;
  const size_t lineHeight;
  const size_t letterWidth;

  Document(size_t w, size_t h, size_t c)
      : pageWidth(w), lineHeight(h), letterWidth(c) {}
};

void parseImageParameter(Image &image, const string &text) {
  stringstream stream(text);
  string name, valueString;
  getline(stream, name, '=');
  getline(stream, valueString);
  if (name == "width") {
    int value = stoi(valueString);
    image.width = value;
  } else if (name == "height") {
    int value = stoi(valueString);
    image.height = value;
  } else if (name == "layout") {
    image.layout = stringToImageType[valueString];
  } else if (name == "dx") {
    int value = stoi(valueString);
    image.dx = value;
  } else if (name == "dy") {
    int value = stoi(valueString);
    image.dy = value;
  }
}

void parseLine(bool &isImage, string &text, Image &image, Word &word,
               Paragraph &paragraph) {
  if (!isImage) {
    if (text == "(image") {
      isImage = true;
      image = Image();
    } else {
      word.letterCount = text.size();
      Element element;
      element.type = ElementType::Word;
      element.word = word;
      paragraph.elements.push_back(element);
      word = Word();
    }
  } else {
    if (isImage && text.back() == ')') {
      isImage = false;
      text.pop_back();
    }
    parseImageParameter(image, text);

    if (!isImage) {
      Element element;
      element.type = ElementType::Image;
      element.image = image;
      paragraph.elements.push_back(element);
      image = Image();
    }
  }
}

Document readDocument(istream &inputStream) {
  string line;
  Paragraph paragraph;
  bool isImage = false;
  getline(inputStream, line);
  stringstream ss(line);
  size_t w, h, c;
  ss >> w >> h >> c;
  Document document(w, h, c);
  while (getline(inputStream, line)) {
    if (line.find_first_not_of(' ') == string::npos ||
        line.empty()) { // empty line -> new paragraph
      document.paragraphs.push_back(paragraph);
      paragraph = Paragraph();
      continue;
    }
    string text;
    stringstream stream(line);
    Image image;
    Word word;
    while (getline(stream, text, ' ')) {
      parseLine(isImage, text, image, word, paragraph);
    }
  }
  document.paragraphs.push_back(paragraph);
  return document;
}

pair<bool, size_t> isSegmentIntersect(size_t startX, size_t finishX, size_t y) {
  for (auto it = surroundedSet.begin(); it != surroundedSet.end(); ++it) {
    auto &rect = *it;
    bool ok = (finishX > rect.x) && (startX < rect.x + rect.width) &&
              (y >= rect.y) && (y < rect.y + rect.height);
    if (ok)
      return make_pair(true, rect.x + rect.width);
  }
  return make_pair(false, 0);
}

pair<bool, size_t> canInsert(const Fragment &fragment, size_t pageWidth,
                             size_t elementWidth, size_t c) {
  size_t startX = fragment.x + fragment.width;
  size_t finishX = startX + elementWidth;
  if (!fragment.empty) {
    finishX += c;
  }
  bool can = (finishX <= pageWidth) &&
             !isSegmentIntersect(startX, finishX, fragment.y).first;
  return make_pair(can, finishX - fragment.x);
}

void updateImage(Image &image, const Fragment &fragment) {
  image.beginX = fragment.x + fragment.width - image.width;
  image.beginY = fragment.y;
}

void updateFragment(Fragment &fragment, size_t width, size_t height) {
  fragment.width = width;
  if (height > fragment.height) {
    fragment.height = height;
  }
}

void checkSurroundedSet(size_t y) {
  vector<Rect> toDelete;
  for (auto it = surroundedSet.begin(); it != surroundedSet.end(); ++it) {
    auto &rect = *it;
    if (rect.y + rect.height < y) {
      toDelete.push_back(rect);
    }
  }

  for (const auto &rect : toDelete) {
    surroundedSet.erase(rect);
  }
}

void findNewFragment(Fragment &fragment, size_t w, size_t h, size_t c,
                     size_t neededWidth, bool useDelimeter = false) {
  size_t startX = fragment.x + fragment.width;
  size_t finishX = startX + neededWidth;

  size_t y = fragment.y;
  size_t startY = y;

  if (useDelimeter && fragment.isExtended) {
    finishX += c;
  }

  if (finishX > w) {
    y += fragment.height > h ? fragment.height : h;
    startX = 0;
    finishX = neededWidth;
    fragment.height = h;
    fragment.isExtended = false;
  }

  auto result = isSegmentIntersect(startX, finishX, y);
  while (result.first) {
    startX = result.second;
    finishX = startX + neededWidth;

    if (finishX > w) {
      y += fragment.height > h ? fragment.height : h;
      startX = 0;
      finishX = neededWidth;
      fragment.height = h;
      fragment.isExtended = false;
    }
    result = isSegmentIntersect(startX, finishX, y);
  }

  fragment.x = startX;
  fragment.y = y;
  if (startY != y) {
    fragment.height = h;
  }
  fragment.width = 0;
  fragment.empty = true;
  fragment.isExtended = false;

  checkSurroundedSet(y);
}

void processWord(Element &element, Fragment &fragment, Document &document) {
  size_t w = document.pageWidth;
  size_t h = document.lineHeight;
  size_t c = document.letterWidth;

  int wordWidth = element.word.letterCount * c;
  auto result = canInsert(fragment, w, wordWidth, c);
  if (result.first) {
    fragment.width = result.second;
  } else {
    if (fragment.width != 0) {
      document.fragments.push_back(fragment);
    }
    findNewFragment(fragment, w, h, c, wordWidth, true);

    fragment.width = wordWidth;
  }
  fragment.empty = false;
  fragment.isExtended = true;
}

void processEmbeddedImage(Image &image, Fragment &fragment,
                          Document &document) {
  size_t w = document.pageWidth;
  size_t h = document.lineHeight;
  size_t c = document.letterWidth;

  auto result = canInsert(fragment, w, image.width, c);
  size_t width;
  if (result.first) {
    width = result.second;
  } else {
    if (fragment.width != 0) {
      document.fragments.push_back(fragment);
    }
    width = image.width;
    findNewFragment(fragment, w, h, c, width, true);
  }
  updateFragment(fragment, width, image.height);
  updateImage(image, fragment);
  fragment.empty = false;
  fragment.isExtended = true;
}

void newFragment(Fragment &fragment, Document &document) {
  document.fragments.push_back(fragment);
  fragment.x += fragment.width;
  fragment.width = 0;
  fragment.empty = true;
  fragment.isExtended = false;
}

void processSurroundedImage(Image &image, Fragment &fragment,
                            Document &document) {
  size_t w = document.pageWidth;
  size_t h = document.lineHeight;
  size_t c = document.letterWidth;

  newFragment(fragment, document);
  auto result = canInsert(fragment, w, image.width, 0);
  if (result.first) {
    surroundedSet.insert(Rect(fragment.x + fragment.width, fragment.y,
                              image.width, image.height));
    fragment.width = result.second;
  } else {
    if (fragment.width != 0) {
      document.fragments.push_back(fragment);
    }
    findNewFragment(fragment, w, h, c, image.width);
    surroundedSet.insert(Rect(fragment.x + fragment.width, fragment.y,
                              image.width, image.height));
    fragment.width = image.width;
  }
  updateImage(image, fragment);
  newFragment(fragment, document);
  fragment.isExtended = false;
}

int checkImagePosition(const Image &image, int x, size_t w) {
  if (x < 0) {
    x = 0;
  } else if (x + image.width > w) {
    x = w - image.width;
  }
  return x;
}

Image lastImage;
bool lastFloatingImage;

void processFloatingImage(Image &image, const Fragment &fragment, size_t w,
                          bool relativeFloatimgImage) {
  int x, y;
  if (relativeFloatimgImage) {
    x = lastImage.beginX + lastImage.width;
    y = lastImage.beginY;
  } else {
    x = fragment.x + fragment.width;
    y = fragment.y;
  }
  x += image.dx;
  y += image.dy;
  x = checkImagePosition(image, x, w);
  image.beginX = x;
  image.beginY = y;
  lastImage = image;
}

void processElement(Element &element, Fragment &fragment, Document &document) {
  size_t w = document.pageWidth;
  if (element.type == ElementType::Word) {
    processWord(element, fragment, document);
    lastFloatingImage = false;
  } else if (element.type == ElementType::Image) {
    Image &image = element.image;
    if (image.layout == ImageType::Embedded) {
      processEmbeddedImage(image, fragment, document);
      lastFloatingImage = false;
    } else if (image.layout == ImageType::Surrounded) {
      processSurroundedImage(image, fragment, document);
      lastFloatingImage = false;
    } else if (image.layout == ImageType::Floating) {
      processFloatingImage(image, fragment, w, lastFloatingImage);
      lastFloatingImage = true;
    }
  }
}

void processFragments(Document &document) {
  size_t h = document.lineHeight;
  Fragment fragment;
  fragment.height = h;
  for (size_t i = 0; i < document.paragraphs.size(); ++i) {
    Paragraph &paragraph = document.paragraphs[i];
    for (size_t j = 0; j < paragraph.elements.size(); ++j) {
      processElement(paragraph.elements[j], fragment, document);
    }
    document.fragments.push_back(fragment);
    fragment.toNewLine(h);
    lastFloatingImage = false;
  }
}

void printResult(const Document &document, ostream &output) {
  bool first = true;
  for (size_t i = 0; i < document.paragraphs.size(); ++i) {
    for (size_t j = 0; j < document.paragraphs.at(i).elements.size(); ++j) {
      const Element &element = document.paragraphs.at(i).elements.at(j);
      if (element.type != ElementType::Image)
        continue;
      if (!first) {
        output << endl;
      }
      output << element.image.beginX << " " << element.image.beginY;
      first = false;
    }
  }
}

void Task1J::test(std::istream &stream) {

  Document document = readDocument(stream);
  processFragments(document);
  printResult(document, cout);
}

int main() { Task1J().test(); }
