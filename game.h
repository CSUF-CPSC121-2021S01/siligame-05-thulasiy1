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

  std::<Opponent>& GetOpponents() { return o; }
  std::vector<OpponentProjectile>& GetOpponentProjectiles() { return op; }
  std::vector<PlayerProjectile>& GetPlayerProjectiles() { return pp; }
  Player& GetPlayer() { return p; }

  graphics::Image& GetGameScreen();
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();

  void Init();

  void UpdateScreen();

  void Start();

  void MoveGameElements();

  void FilterIntersections();

  void OnAnimationStep() override;

  void OnMouseEvent(const graphics::MouseEvent& mouse_event) override;

 private:
  int width_;
  int height_;
  graphics::Image image;
  std::vector<Opponent> o;
  std::vector<OpponentProjectile> op;
  std::vector<PlayerProjectile> pp;
  Player p;
};

#endif  // GAME_H
