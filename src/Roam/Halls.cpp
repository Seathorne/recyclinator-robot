#include "Halls.h"

Hall Halls::_halls[(int)(HallId::H) + 1] = {
  Hall(A),  Hall(AB), Hall(B),           Hall(C), Hall(CD), Hall(D),
  Hall(AE),          Hall(BF),          Hall(CG),          Hall(DH),
  Hall(E),  Hall(EF), Hall(F), Hall(FG), Hall(G), Hall(GH), Hall(H), 
};

void Halls::init() {
  setConnection(_getById(A), _getById(AB), East);
  setConnection(_getById(AB), _getById(B), East);
  setConnection(_getById(C), _getById(CD), East);
  setConnection(_getById(CD), _getById(D), East);
  
  setConnection(_getById(A), _getById(AE), South);
  setConnection(_getById(AE), _getById(E), South);
  setConnection(_getById(B), _getById(BF), South);
  setConnection(_getById(BF), _getById(F), South);
  setConnection(_getById(C), _getById(CG), South);
  setConnection(_getById(CG), _getById(G), South);
  setConnection(_getById(D), _getById(DH), South);
  setConnection(_getById(DH), _getById(H), South);

  setConnection(_getById(E), _getById(EF), East);
  setConnection(_getById(EF), _getById(F), East);
  setConnection(_getById(F), _getById(FG), East);
  setConnection(_getById(FG), _getById(G), East);
  setConnection(_getById(G), _getById(GH), East);
  setConnection(_getById(GH), _getById(H), East);
}

Direction opposite(Direction dir) {
  switch (dir) {
    case North: return South;
    case South: return North;
    case East: return West;
    case West: return East;
  }
}

void Halls::setConnection(Hall *a, Hall *b, Direction dir) {
  a->setConnection(dir, b);
  b->setConnection(opposite(dir), a);
}

const Hall* Halls::getById(HallId id) {
  return &_halls[(int)id];
}

Hall* Halls::_getById(HallId id) {
  return &_halls[(int)id];
}
