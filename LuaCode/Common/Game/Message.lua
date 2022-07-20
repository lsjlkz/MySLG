---
--- Created by lsjlkz.
--- DateTime: 2022/7/19 17:00
--- Desc:
---

__G__MessageTable = __G__MessageTable or {}

__G__MessageTable.RegServerDistributeTable = {}

function __G__MessageTable.RegServerDistribute(msg_type, func)
    __G__MessageTable.RegServerDistributeTable[msg_type] = func
end

function __G__MessageTable.TriggerServerDistribute(msg_type, param)
    if __G__MessageTable.RegServerDistributeTable[msg_type] == nil then
        return
    end
    __G__MessageTable.RegServerDistributeTable[msg_type](param)
end

return __G__MessageTable