---
--- Created by lsjlkz.
--- DateTime: 2022/7/19 17:00
--- Desc:
---

__G__LuaMessageTable = __G__LuaMessageTable or {}

__G__LuaMessageTable.reg_server_distribute_table = {}

function __G__LuaMessageTable.reg_server_distribute(msg_type, func)
    reg_server_distribute_table[msg_type] = func
end

function __G__LuaMessageTable.trigger_server_distribute(msg_type, func)
    print(msg_type, func)
end

return __G__LuaMessageTable