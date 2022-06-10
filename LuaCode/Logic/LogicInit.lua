---
--- Created by lsjlkz.
--- DateTime: 2022/6/8 17:31
--- Desc:
---

__G__LogicTable = __G__LogicTable or {}
local cDefineTable = require("Common/CDefine")

function __G__LogicTable.init()
    print("Logic Start...")
    local cGameServer = require("cGameServer")
    cGameServer.CreateNetwork(100, cDefineTable.LogicID, 10010)
    local army_attack = require("Logic/army_attack")
    army_attack.attack_test()
end

return __G__LogicTable