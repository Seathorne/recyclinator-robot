#include "Hall.h"

Hall::Hall(HallId id, double width)
    : _id(id),
      _width(width) {
}

Hall::Hall(HallId id, const Hall *north, const Hall *south, const Hall *east, const Hall *west, double width)
    : Hall(id, width) {
  setConnection(Direction::North, north);
  setConnection(Direction::South, south);
  setConnection(Direction::East, east);
  setConnection(Direction::West, west);
}

void Hall::setConnection(Direction dir, const Hall *connection) {
  _connections[(int)dir] = connection;
}

HallId Hall::getId() const {
  return _id;
}

void Hall::setLength(double length) {
  _length = length;
}

double Hall::getLength() const {
  return _length;
}

double Hall::getWidth() const {
  return _width;
}

const Hall* Hall::getConnection(Direction dir) const {
  return _connections[(int)dir];
}

const Hall* Hall::getConnection() const {
  Direction randDir = (Direction)(rand() % 4);
  return getConnection(randDir);
}

int Hall::yToIndex(double y) const {
  return min(max(0, (int)y), (int)(_width)-1);
}

bool Hall::isWallConst(double y, Side side, double &distance) const {
  int index = yToIndex(y);
  distance = _wallDistances[(int)side][index];
}

bool Hall::isWidthConst(double y, double &width) const {
  double distLeft, distRight;
  if (isWallConst(y, Side::Left, distLeft)) {
    if (isWallConst(y, Side::Right, distRight)) {
      width = distLeft + distRight;
      return true;
    }
  }

  width = -1;
  return false;
}

double Hall::xSetpointAt(double y) const {
  int index = yToIndex(y);
  return _xSetpoints[index];
}
