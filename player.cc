#include "player.h"
#include "cpputils/graphics/image.h"
#include "game_element.h"

void Player::Draw(graphics::Image& image) {
  graphics::Image player;
  player.Load("p.bmp");
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      graphics::Color color = player.GetColor(i, j);
      image.SetColor(x_ + i, y_ + j, color);
    }
  }
}

void PlayerProjectile::Draw(graphics::Image& image) {
  graphics::Image playerprojectile;
  playerprojectile.Load("pp.bmp");
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      graphics::Color color = playerprojectile.GetColor(i, j);
      image.SetColor(x_ + i, y_ + j, color);
    }
  }
}

void PlayerProjectile::Move(const graphics::Image& picture) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(picture)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
