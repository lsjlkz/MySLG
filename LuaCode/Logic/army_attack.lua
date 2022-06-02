---
--- Created by lsjlkz.
--- DateTime: 2022/5/24 11:05
--- Desc:
---
__Army__Troops = __Army__Troops or {}

local army_ctrl = require("army_ctrl")

function __Army__Troops.attack(army, other_army)
    army:AttackArmy(other_army)
end

function __Army__Troops.attack_test()
    local army_one = army_ctrl.Create(2,2,2,2,2,2,2,2)
    local army_two = army_ctrl.Create(2,2,2,2,2,2,2,2)

    __Army__Troops.attack(army_one, army_two)
end

return __Army__Troops