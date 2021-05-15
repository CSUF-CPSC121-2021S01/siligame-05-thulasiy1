#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(int width, int height)
      : width_(width), height_(height), image(width, height) {}

  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return o; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return op;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return pp;
  }
  Player &GetPlayer() { return p; }

  graphics::Image &GetGameScreen();
  void CreateOpponents();

  void Init();

  void UpdateScreen();

  void Start();

  void MoveGameElements();

  void FilterIntersections();

  void OnAnimationStep() override;

  void OnMouseEvent(const graphics::MouseEvent &mouse_event) override;

  int GetScore() { return score_; }

  bool HasLost() { return haslost_; }

  void LaunchProjectiles();

  void RemoveInactive();

 private:
  int width_;
  int height_;
  graphics::Image image;
  std::vector<std::unique_ptr<Opponent>> o;
  std::vector<std::unique_ptr<OpponentProjectile>> op;
  std::vector<std::unique_ptr<PlayerProjectile>> pp;
  Player p;
  int score_;
  bool haslost_;
};

#endif  // GAME_H
