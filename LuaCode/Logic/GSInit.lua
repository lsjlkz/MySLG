---
--- Created by lsjlkz.
--- DateTime: 2022/6/1 17:15
--- Desc:
---


package.path = package.path .. ";../LuaCode/?.lua;"


local function get_this_lua_path()
    module = require("Common/Module")
    path = module.get_root_folder()
    return path
end


local function main()
    print("GSInit start...")

    local cGameServer = require("cGameServer")

    local world_init = require("World/WorldInit")

    --初始化游戏世界
    world_init.init_world()

    cGameServer.CreateNetwork(100, 10, 10086)


end

main()
