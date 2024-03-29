/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "zulgurub.h"

DoorData const doorData[] =
{
    { GO_VENOXIS_COIL,                  DATA_VENOXIS,   DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_ARENA_DOOR_1,                  DATA_MANDOKIR,  DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_FORCEFIELD,                    DATA_KILNARA,   DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_ZANZIL_DOOR,                   DATA_ZANZIL,    DOOR_TYPE_ROOM, BOUNDARY_NONE },
    //{ GO_THE_CACHE_OF_MADNESS_DOOR,     DATA_xxxxxxx,   DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { 0,                                0,              DOOR_TYPE_ROOM, BOUNDARY_NONE }
};

class instance_zulgurub : public InstanceMapScript
{
    public:
        instance_zulgurub() : InstanceMapScript(ZGScriptName, 859) { }

        struct instance_zulgurub_InstanceMapScript : public InstanceScript
        {
            instance_zulgurub_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
                venoxisGUID         = 0;
                mandokirGUID        = 0;
                kilnaraGUID         = 0;
                zanzilGUID          = 0;
                jindoGUID           = 0;
                hazzarahGUID        = 0;
                renatakiGUID        = 0;
                wushoolayGUID       = 0;
                grilekGUID          = 0;
                jindoTiggerGUID     = 0;
            }

            void OnCreatureCreate(Creature* creature) override
            {
                switch (creature->GetEntry())
                {
                    case NPC_VENOXIS:
                        venoxisGUID = creature->GetGUID();
                        break;
                    case NPC_MANDOKIR:
                        mandokirGUID = creature->GetGUID();
                        break;
                    case NPC_KILNARA:
                        kilnaraGUID = creature->GetGUID();
                        break;
                    case NPC_ZANZIL:
                        zanzilGUID = creature->GetGUID();
                        break;
                    case NPC_JINDO:
                        jindoGUID = creature->GetGUID();
                        break;
                    case NPC_HAZZARAH:
                        hazzarahGUID = creature->GetGUID();
                        break;
                    case NPC_RENATAKI:
                        renatakiGUID = creature->GetGUID();
                        break;
                    case NPC_WUSHOOLAY:
                        wushoolayGUID = creature->GetGUID();
                        break;
                    case NPC_GRILEK:
                        grilekGUID = creature->GetGUID();
                        break;
                    case NPC_JINDO_TRIGGER:
                        jindoTiggerGUID = creature->GetGUID();
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_VENOXIS_COIL:
                    case GO_ARENA_DOOR_1:
                    case GO_FORCEFIELD:
                    case GO_ZANZIL_DOOR:
                    case GO_THE_CACHE_OF_MADNESS_DOOR:
                        AddDoor(go, true);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_VENOXIS_COIL:
                    case GO_ARENA_DOOR_1:
                    case GO_FORCEFIELD:
                    case GO_ZANZIL_DOOR:
                    case GO_THE_CACHE_OF_MADNESS_DOOR:
                        AddDoor(go, false);
                        break;
                    default:
                        break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state) override
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_VENOXIS:
                    case DATA_MANDOKIR:
                    case DATA_KILNARA:
                    case DATA_ZANZIL:
                    case DATA_JINDO:
                    case DATA_HAZZARAH:
                    case DATA_RENATAKI:
                    case DATA_WUSHOOLAY:
                    case DATA_GRILEK:
                        break;
                    default:
                        break;
                }

                return true;
            }

            /*
            void SetData(uint32 type, uint32 data) override
            {
                switch (type)
                {
                }
            }

            uint32 GetData(uint32 type) const override
            {
                switch (type)
                {
                }

                return 0;
            }
            */

            uint64 GetData64(uint32 type) const override
            {
                switch (type)
                {
                    case DATA_VENOXIS:
                        return venoxisGUID;
                    case DATA_MANDOKIR:
                        return mandokirGUID;
                    case DATA_KILNARA:
                        return kilnaraGUID;
                    case DATA_ZANZIL:
                        return zanzilGUID;
                    case DATA_JINDO:
                        return jindoGUID;
                    case DATA_HAZZARAH:
                        return hazzarahGUID;
                    case DATA_RENATAKI:
                        return renatakiGUID;
                    case DATA_WUSHOOLAY:
                        return wushoolayGUID;
                    case DATA_GRILEK:
                        return grilekGUID;
                    case DATA_JINDOR_TRIGGER:
                        return jindoTiggerGUID;
                    default:
                        break;
                }

                return 0;
            }

        protected:
             uint64 venoxisGUID;
             uint64 mandokirGUID;
             uint64 kilnaraGUID;
             uint64 zanzilGUID;
             uint64 jindoGUID;
             uint64 hazzarahGUID;
             uint64 renatakiGUID;
             uint64 wushoolayGUID;
             uint64 grilekGUID;
             uint64 jindoTiggerGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_zulgurub_InstanceMapScript(map);
        }
};

void AddSC_instance_zulgurub()
{
    new instance_zulgurub();
}
