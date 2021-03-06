---
--- Created by lsjlkz.
--- DateTime: 2022/6/8 17:31
--- Desc:
---

__G__LogicTable = __G__LogicTable or {}
local cDefineTable = require("Common/CDefine")

function __G__LogicTable.test(param)
    print(param)
end

function __G__LogicTable.MessageDebug(param)
    for i, v in pairs(param) do
        print(v)
    end
end

function __G__LogicTable.init()
    print("Logic Start...")
    local cGameServer = require("cGameServer")
    cGameServer.CreateNetwork(100, cDefineTable.LogicID, 10010)

    local f = require("Common/Game/Function")
    require("Common/Game/Message")
    local idx = f.RegMesFunction(__G__LogicTable.test)
    f.TriMesFunction(idx, 3)
    cGameServer.CallLuaFunc(idx, 555);

    local message = require("Common/Game/Message")
    message.RegServerDistribute(3, __G__LogicTable.MessageDebug)
    cGameServer.PackMsg(3, {3,4,5, 6, 7, false})

end

return __G__LogicTable
