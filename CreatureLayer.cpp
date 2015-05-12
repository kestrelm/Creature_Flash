#include "CreatureLayer.h"

#include "CreatureModule.h"
#include <map>
#include <string>

static std::map<int, std::shared_ptr<CreatureModule::Creature> > creatures_map;
static std::map<int, std::shared_ptr<CreatureModule::CreatureAnimation> > animation_map;
static std::map<int, std::shared_ptr<CreatureModule::CreatureManager> > managers_map;
static std::map<int, std::shared_ptr<CreatureModule::CreatureLoadDataPacket> > data_map;

static int creatures_cnter = 0;
static int animation_cnter = 0;
static int managers_cnter = 0;
static int data_cnter = 0;

int LoadCreatureFromFilename(char * filename_in)
{
  data_cnter++;

  CreatureModule::CreatureLoadDataPacket * new_packet = new CreatureModule::CreatureLoadDataPacket();
  CreatureModule::LoadCreatureJSONData(std::string(filename_in), *new_packet);

  data_map[data_cnter] = std::shared_ptr<CreatureModule::CreatureLoadDataPacket>(new_packet);

  return data_cnter;
}

int LoadCreatureFromZipFilename(char * filename_in)
{
  data_cnter++;

  CreatureModule::CreatureLoadDataPacket * new_packet = new CreatureModule::CreatureLoadDataPacket();
  CreatureModule::LoadCreatureZipJSONData(std::string(filename_in), *new_packet);

  data_map[data_cnter] = std::shared_ptr<CreatureModule::CreatureLoadDataPacket>(new_packet);

  return data_cnter;
}

int CreateCreature(int load_data)
{
  creatures_cnter++;
  
  std::shared_ptr<CreatureModule::CreatureLoadDataPacket> cur_data = data_map[load_data];
  
  CreatureModule::Creature * new_creature = new CreatureModule::Creature(*(cur_data.get()));
  creatures_map[creatures_cnter] = std::shared_ptr<CreatureModule::Creature>(new_creature);
  
  return creatures_cnter;
}

int CreateCreatureAnimation(CreatureModule::CreatureLoadDataPacket * load_data, char *name_in)
{
  animation_cnter++;

  CreatureModule::CreatureAnimation * new_animation = new CreatureModule::CreatureAnimation(*load_data, std::string(name_in));
  animation_map[animation_cnter] = std::shared_ptr<CreatureModule::CreatureAnimation>(new_animation);
  
  return animation_cnter;
}

int CreateCreatureManager(int target_creature_in)
{
  managers_cnter++;
  CreatureModule::CreatureManager * new_manager = new CreatureModule::CreatureManager(creatures_map[target_creature_in]);
  managers_map[managers_cnter] = std::shared_ptr<CreatureModule::CreatureManager>(new_manager);
  
  return managers_cnter;
}


void AddCreatureManagerAnimation(int manager_in, int animation_in)
{
  std::shared_ptr<CreatureModule::CreatureManager> cur_manager = managers_map[manager_in];
  std::shared_ptr<CreatureModule::CreatureAnimation> cur_animation = animation_map[animation_in];

  cur_manager->AddAnimation(cur_animation);
}


void SetCreatureManagerActiveAnimation(int manager_in, char *  animation_name)
{
  std::shared_ptr<CreatureModule::CreatureManager> cur_manager = managers_map[manager_in];
  cur_manager->SetActiveAnimationName(std::string(animation_name));
}

void SetCreatureManagerIsPlaying(int manager_in, bool flag)
{
  std::shared_ptr<CreatureModule::CreatureManager> cur_manager = managers_map[manager_in];
  cur_manager->SetIsPlaying(flag);
}

void UpdateCreatureManager(int manager_in, float delta)
{
  std::shared_ptr<CreatureModule::CreatureManager> cur_manager = managers_map[manager_in];
  cur_manager->Update(delta);
}

void SetCreatureManagerSetShouldLoop(int manager_in, bool flag)
{
  std::shared_ptr<CreatureModule::CreatureManager> cur_manager = managers_map[manager_in];
  cur_manager->SetShouldLoop(flag);
}

// Retrieve Values
static std::shared_ptr<CreatureModule::Creature> active_creature;
void SetActiveCreature(int creature_in)
{
  active_creature = creatures_map[creature_in];
}

int GetCreatureTotalNumIndices()
{
  return active_creature->GetTotalNumIndices();
}

int GetCreatureTotalNumPoints()
{
  return active_creature->GetTotalNumPoints();
}

float GetCreatureUV_Val(int idx)
{
  return *(active_creature->GetGlobalUvs() + idx);
}

int GetCreatureIndice_Val(int idx)
{
  return *(active_creature->GetGlobalIndices() + idx);
}

float GetCreatureGlobalPoint_Val(int idx)
{
  return *(active_creature->GetGlobalPts() + idx);
}

float GetCreatureRenderPoint_Val(int idx)
{
  return *(active_creature->GetRenderPts() + idx);
}
