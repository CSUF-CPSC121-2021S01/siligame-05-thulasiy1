#include "opponent.h"
#include "cpputils/graphics/image.h"
#include "game_element.h"

void Opponent::Draw(graphics::Image& image) {
  graphics::Image opponent;
  opponent.Load("o.bmp");
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      graphics::Color color = opponent.GetColor(i, j);
      image.SetColor(x_ + i, y_ + j, color);
    }
  }
}

void OpponentProjectile::Draw(graphics::Image& image) {
  graphics::Image opponentprojectile;
  opponentprojectile.Load("op.bmp");
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      graphics::Color color = opponentprojectile.GetColor(i, j);
      image.SetColor(x_ + i, y_ + j, color);
    }
  }
}

void Opponent::Move(const graphics::Image& picture) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(picture)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

void OpponentProjectile::Move(const graphics::Image& picture) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(picture)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
