#include "game.h"
#include <iostream>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

graphics::Image &Game::GetGameScreen() { return image; }

void Game::CreateOpponents() {
  Opponent opponent;
  opponent.SetX(175);
  opponent.SetY(100);
  o.push_back(opponent);
}

void Game::CreateOpponentProjectiles() {
  OpponentProjectile opponentprojectile;
  opponentprojectile.SetX(200);
  opponentprojectile.SetY(200);
  op.push_back(opponentprojectile);
}

void Game::CreatePlayerProjectiles() {
  PlayerProjectile playerprojectile;
  playerprojectile.SetX(200);
  playerprojectile.SetY(300);
  pp.push_back(playerprojectile);
}

void Game::Init() {
  p.SetX(180);
  p.SetY(350);
  // CreateOpponents();
  // CreateOpponentProjectiles();
  // CreatePlayerProjectiles();
  image.AddMouseEventListener(*this);
  image.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  graphics::Color white(255, 255, 255);
  image.DrawRectangle(0, 0, image.GetWidth(), image.GetHeight(), white);
  for (int i = 0; i < o.size(); i++) {
    if (o[i].GetIsActive()) {
      o[i].Draw(image);
    }
  }
  for (int i = 0; i < op.size(); i++) {
    if (op[i].GetIsActive()) {
      op[i].Draw(image);
    }
  }
  for (int i = 0; i < pp.size(); i++) {
    if (pp[i].GetIsActive()) {
      pp[i].Draw(image);
    }
  }
  if (p.GetIsActive()) {
    p.Draw(image);
  }
  image.DrawText(0, 0, "Score: " + (image.GetScore()), white)
}

void Game::MoveGameElements() {
  for (int i = 0; i < o.size(); i++) {
    if (o[i].GetIsActive()) {
      o[i].Move(image);
    }
  }
  for (int i = 0; i < op.size(); i++) {
    if (op[i].GetIsActive()) {
      op[i].Move(image);
    }
  }
  for (int i = 0; i < pp.size(); i++) {
    if (pp[i].GetIsActive()) {
      pp[i].Move(image);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < o.size(); i++) {
    if (p.IntersectsWith(&o[i]) == true) {
      p.SetIsActive(false);
      o[i].SetIsActive(false);
    }
  }
  for (int j = 0; j < o.size(); j++) {
    for (int k = 0; k < pp.size(); k++) {
      if (pp[k].IntersectsWith(&o[j]) == true) {
        pp[k].SetIsActive(false);
        o[j].SetIsActive(false);
      }
    }
  }
  for (int l = 0; l < op.size(); l++) {
    if (p.IntersectsWith(&op[l]) == true) {
      p.SetIsActive(false);
      op[l].SetIsActive(false);
    }
  }
}

void Game::OnAnimationStep() {
  if (o.size() < 1) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectile();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  image.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouse) {
  if (mouse.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    int location_x = p.GetX();
    int location_y = p.GetY();

    p.SetX(mouse.GetX() - p.GetWidth() / 2);
    p.SetY(mouse.GetY() - p.GetHeight() / 2);

    if (p.GetX() <= 0 || p.GetX() + p.GetWidth() > image.GetWidth()) {
      p.SetX(location_x);
      p.SetY(location_y);
    }
    if (p.GetY() <= 0 || p.GetY() + p.GetHeight() > image.GetHeight()) {
      p.SetX(location_x);
      p.SetY(location_y);
    }
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> OnMouseEvent_o =
        std::make_unique<PlayerProjectile>(GetX(), GetY());
    pp.push_back(std::move(OnMouseEvent_o));
  }
}

void Game::Start() { image.ShowUntilClosed(); }

void Game::LaunchProjectile() {
  for (int i = 0; i < o.size(); i++) {
    std::unique_ptr<OpponentProjectile> opponents = o[i]->LaunchProjectile();
    if (o != nullptr) {
      op.push_back(std::move(opponents));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = o.size(); i >= 0; i++) {
    if (!o[i]->GetIsActive()) {
      o.erase(o.begin() + i);
    }
  }
  for (int j = op.size(); j >= 0; j++) {
    if (!op[j]->GetIsActive()) {
      op.erase(op.begin() + j);
    }
  }
  for (int k = o.size(); k >= 0; k++) {
    if (!pp[k]->GetIsActive()) {
      pp.erase(pp.begin() + k);
    }
  }
}
