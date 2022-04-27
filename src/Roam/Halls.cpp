#include "Halls.h"

constexpr double FtCm = 30.3;

Hall Halls::JunctA(A);
Hall Halls::HallAB(AB);
Hall Halls::JunctB(B);
Hall Halls::JunctC(C);
Hall Halls::HallCD(CD);
Hall Halls::JunctD(D);
Hall Halls::HallAE(AE);
Hall Halls::HallBF(BF);
Hall Halls::HallCG(CG);
Hall Halls::HallDH(DH, 7 * FtCm);
Hall Halls::JunctE(E);
Hall Halls::HallEF(EF);
Hall Halls::JunctF(F);
Hall Halls::HallFG(FG);
Hall Halls::JunctG(G);
Hall Halls::HallGH(GH);
Hall Halls::JunctH(H);

Hall* Halls::_halls[(int)(HallId::H) + 1];

void Halls::init() {
  Hall *halls[(int)(HallId::H)+1] = {
    &JunctA, &HallAB, &JunctB,          &JunctC, &HallCD, &JunctD,
    &HallAE,          &HallBF,          &HallCG,          &HallDH,
    &JunctE, &HallEF, &JunctF, &HallFG, &JunctG, &HallGH, &JunctH,
  };

  for (int i = 0; i <= (int)HallId::H; i++) {
    _halls[i] = halls[i];
  }

  constexpr int BFLength = 87;
  HallBF.setLength(BFLength);
  HallBF._xSetpoints = new double[BFLength];
  HallBF._wallDistances[(int)Side::Left] = new double[BFLength] {
    /* Left  */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3.5, 3, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3.5, 3, 3.5, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4.5, 5.5, 6.5, 7.5,
  };
  HallBF._wallDistances[(int)Side::Right] = new double[BFLength] {
    /* Right */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   4, 4, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   4, 4,   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,   5,   4,   4,   4,
  };
  for (int i = 0; i < BFLength; i++) {
    HallBF._wallDistances[0][i] *= FtCm;
    HallBF._wallDistances[1][i] *= FtCm;
  }
  
  setConnection(&JunctA, &HallAB, East);
  setConnection(&HallAB, &JunctB, East);
  setConnection(&JunctC, &HallCD, East);
  setConnection(&HallCD, &JunctD, East);
  
  setConnection(&JunctA, &HallAE, South);
  setConnection(&HallAE, &JunctE, South);
  setConnection(&JunctB, &HallBF, South);
  setConnection(&HallBF, &JunctF, South);
  setConnection(&JunctC, &HallCG, South);
  setConnection(&HallCG, &JunctG, South);
  setConnection(&JunctD, &HallDH, South);
  setConnection(&HallDH, &JunctH, South);

  setConnection(&JunctE, &HallEF, East);
  setConnection(&HallEF, &JunctF, East);
  setConnection(&JunctF, &HallFG, East);
  setConnection(&HallFG, &JunctG, East);
  setConnection(&JunctG, &HallGH, East);
  setConnection(&HallGH, &JunctH, East);
}

void Halls::setConnection(Hall *a, Hall *b, Direction dir) {
  a->setConnection(dir, b);
  b->setConnection(opposite(dir), a);
}

const Hall* Halls::getById(HallId id) {
  return _halls[(int)id];
}

Direction Halls::opposite(Direction dir) {
  switch (dir) {
    case North: return South;
    case South: return North;
    case East: return West;
    case West: return East;
  }
}

int Halls::degreesBetween(Direction a, Direction b) {
  static constexpr int DegreesBetween[4][4] = {
    { 0, 180, 90, -90 },  // North to NSEW
    { -180, 0, -90, 90 }, // South to NSEW
    { -90, 90, 0, 180 },  // East to NSEW
    { 90, -90, -180, 0 }, // West to NSEW
  };
  return DegreesBetween[(int)a][(int)b];
}
