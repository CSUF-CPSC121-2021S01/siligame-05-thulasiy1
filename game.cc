#include "game.h"
#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

graphics::Image &Game::GetGameScreen() { return image; }

void Game::CreateOpponents() {
  Opponent opponent;
  opponent.SetX(175);
  opponent.SetY(100);
}

void Game::Init() {
  p.SetX(180);
  p.SetY(350);
  image.AddMouseEventListener(*this);
  image.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  graphics::Color purple(230, 230, 250);
  if (p.GetIsActive()) {
    p.Draw(image);
  } else {
    image.DrawText(400, 300, "Game Over!", 50, purple);
  }
  for (int i = 0; i < o.size(); i++) {
    if (o[i]->GetIsActive()) {
      o[i]->Draw(image);
    }
  }
  for (int i = 0; i < op.size(); i++) {
    if (op[i]->GetIsActive()) {
      op[i]->Draw(image);
    }
  }
  for (int i = 0; i < pp.size(); i++) {
    if (pp[i]->GetIsActive()) {
      pp[i]->Draw(image);
    }
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < o.size(); i++) {
    if (o[i]->GetIsActive()) {
      o[i]->Move(image);
    }
  }
  for (int i = 0; i < op.size(); i++) {
    if (op[i]->GetIsActive()) {
      op[i]->Move(image);
    }
  }
  for (int i = 0; i < pp.size(); i++) {
    if (pp[i]->GetIsActive()) {
      pp[i]->Move(image);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < o.size(); i++) {
    if (p.IntersectsWith(o[i].get()) == true) {
      p.SetIsActive(false);
      o[i]->SetIsActive(false);
    }
  }
  for (int j = 0; j < o.size(); j++) {
    for (int k = 0; k < pp.size(); k++) {
      if (pp[k]->IntersectsWith(o[j].get()) == true) {
        pp[k]->SetIsActive(false);
        o[j]->SetIsActive(false);
        if (p.GetIsActive()) {
          score_++;
        }
      }
    }
  }
  for (int l = 0; l < op.size(); l++) {
    if (p.IntersectsWith(op[l].get()) == true) {
      p.SetIsActive(false);
      op[l]->SetIsActive(false);
    }
  }
}

void Game::OnAnimationStep() {
  if (o.size() < 1) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
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
    std::unique_ptr<PlayerProjectile> omo =
        std::make_unique<PlayerProjectile>(p.GetX(), p.GetY());
    pp.push_back(std::move(omo));
  }
}

void Game::Start() { image.ShowUntilClosed(); }

void Game::LaunchProjectiles() {
  for (int i = 0; i < o.size(); i++) {
    std::unique_ptr<OpponentProjectile> opponentprojectile =
        o[i]->LaunchProjectile();
    if (opponentprojectile != nullptr) {
      op.push_back(std::move(opponentprojectile));
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
