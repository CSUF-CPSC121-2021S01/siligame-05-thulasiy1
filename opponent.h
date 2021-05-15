#ifndef OPPONENT_H
#define OPPONENT_H

#include "cpputils/graphics/image.h"
#include "game_element.h"

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image& image);

  void Move(const graphics::Image& picture);

  std::unique_ptr<class OpponentProjectile> LaunchProjectile();
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image& image);

  void Move(const graphics::Image& picture);
};

#endif  // OPPONENT_H
