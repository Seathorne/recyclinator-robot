#include "Hall.h"

Hall::Hall(HallId id)
    : _id(id) {
}

Hall::Hall(HallId id, const Hall *north, const Hall *south, const Hall *east, const Hall *west)
    : Hall(id) {
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

const Hall* Hall::getConnection(Direction dir) const {
  return _connections[(int)dir];
}

const Hall* Hall::getConnection() const {
  Direction randDir = (Direction)(rand() % 4);
  return getConnection(randDir);
}
