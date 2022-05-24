---
--- Created by lsjlkz.
--- DateTime: 2022/5/24 11:05
--- Desc:
---
ArmyTroops = ArmyTroops or {}

local army_ctrl = require("army_ctrl")

local function attack(army, other_army)
    army:AttackArmy(other_army)
end

local army_one = army_ctrl.Create(2,2,2,2,2,2,2,2)
local army_two = army_ctrl.Create(2,2,2,2,2,2,2,2)

--army:AttackArmy(other_army:GetID())

attack(army_one, army_two)

