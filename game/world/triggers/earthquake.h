#pragma once

#include "abstracttrigger.h"

class World;

class Earthquake : public AbstractTrigger {
  public:
    Earthquake(Vob* parent, World& world, const zenkit::VEarthquake& data, Flags flags);

    void onTrigger(const TriggerEvent& evt) override;

  private:

  };
