#include "zonetrigger.h"

#include <zenkit/vobs/Trigger.hh>

#include "world/objects/npc.h"
#include "world/world.h"

ZoneTrigger::ZoneTrigger(Vob* parent, World &world, const zenkit::VTriggerChangeLevel& trig, Flags flags)
  :AbstractTrigger(parent,world,trig,flags){
  levelName = trig.level_name;
  startVobName = trig.start_vob;
  }

void ZoneTrigger::onIntersect(Npc &n) {
  if(n.isPlayer())
    world.triggerChangeWorld(levelName, startVobName);
  }
