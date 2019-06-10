#pragma once

#include "world/focus.h"
#include "inventory.h"

#include <array>

class DialogMenu;
class InventoryMenu;
class World;
class Interactive;
class Npc;
class Item;
class Camera;
class Gothic;

class PlayerControl final {
  public:
    PlayerControl(Gothic& gothic,DialogMenu& dlg,InventoryMenu& inv);

    void changeZoom(int delta);

    bool interact(Interactive& it);
    bool interact(Npc&         other);
    bool interact(Item&        item);

    void toogleWalkMode();

    void clearInput();
    void drawWeaponMele();
    void drawWeaponBow();
    void drawWeaponMage(uint8_t s);
    void jump();

    void rotateLeft ();
    void rotateRight();

    void moveForward();
    void moveBack();
    void moveLeft();
    void moveRight();

    void setTarget(Npc* other);
    void actionFocus(Npc& other);
    void actionForward();
    void actionLeft();
    void actionRight();
    void actionBack();

    void marvinF8();

    bool tickMove(uint64_t dt);

    Focus findFocus(Focus *prev, const Camera &camera, int w, int h);

  private:
    enum Control : uint8_t {
      Idle,
      Forward,
      Back,
      Left,
      Right,
      RotateL,
      RotateR,
      Jump,

      ActionFocus,
      ActForward,
      ActLeft,
      ActRight,
      ActBack,

      Walk,

      CloseWeapon,
      DrawWeaponMele,
      DrawWeaponBow,

      DrawWeaponMage3,
      DrawWeaponMage4,
      DrawWeaponMage5,
      DrawWeaponMage6,
      DrawWeaponMage7,
      DrawWeaponMage8,
      DrawWeaponMage9,
      DrawWeaponMage10,

      Last
      };

    bool           ctrl[Control::Last]={};
    bool           cacheFocus=false;

    Gothic&        gothic;
    DialogMenu&    dlg;
    InventoryMenu& inv;

    World*         world() const;
    void           clrDraw();
    auto           weaponState() const -> WeaponState;
    void           implMove(uint64_t dt);
    void           setPos(std::array<float,3> a, uint64_t dt, float speed);
  };
