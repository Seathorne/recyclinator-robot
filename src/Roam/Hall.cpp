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

bool Hall::isWallConst(double y, Side side) const {
  return false;
}
