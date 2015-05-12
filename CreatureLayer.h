#ifndef __CREATURE_LAYER_H__
#define __CREATURE_LAYER_H__


int LoadCreatureFromFilename(char * filename_in);

int LoadCreatureFromZipFilename(char * filename_in);

int CreateCreature(int load_data);

int CreateCreatureAnimation(CreatureModule::CreatureLoadDataPacket * load_data, char *  name_in);

int CreateCreatureManager(int target_creature_in);

void AddCreatureManagerAnimation(int manager_in, int animation_in);

void SetCreatureManagerActiveAnimation(int manager_in, char * animation_name);

void SetCreatureManagerIsPlaying(int manager_in, bool flag);

void SetCreatureManagerSetShouldLoop(int manager_in, bool flag);

void UpdateCreatureManager(int manager_in, float delta);

// Retrieve Values

void SetActiveCreature(int creature_in);

int GetCreatureTotalNumIndices();

int GetCreatureTotalNumPoints();

float GetCreatureUV_Val(int idx);

int GetCreatureIndice_Val(int idx);

float GetCreatureGlobalPoint_Val(int idx);

float GetCreatureRenderPoint_Val(int idx);

#endif
