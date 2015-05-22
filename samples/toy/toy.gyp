{
  'includes': [
    '../../tool/base.gypi'
  ],
  "target_defaults": {
    "libraries": [
      '-llibhope',
      '-lSDL2',
      '-lSDL2main',
      '-llibwebp_debug',
    ],
  },
  'targets': [
    {
      'type': 'executable',
      'target_name': 'toy',
      'sources': [
        'src/toy.cpp',


        'src/Application.h',
        'src/Application.cpp',


        'src/TileRenderer.h',

        'src/Plan.h',
        'src/CellType.h',
        

        

        'src/logic/storage.h',
        'src/logic/storage.cpp',
        
        'src/logic/plan.h',
        'src/logic/plan.cpp',
        'src/logic/plan/extract.h',
        'src/logic/plan/extract.cpp',
        'src/logic/plan/store.h',
        'src/logic/plan/store.cpp',

        'src/logic/machine.h',
        'src/logic/agent.h',
        'src/logic/deposit.h',
        'src/logic/deposit.cpp',

        'src/logic/path.h',

        'src/logic/location.h',
        'src/logic/location.cpp',
        

        'src/systems/TheGrid.h',
        'src/systems/TheGrid.cpp',

        'src/logic/action.h',
        'src/logic/action.cpp',
        'src/logic/action/action.h',
        'src/logic/action/functions_generated.h',
        'src/logic/action/functions_generated.cpp',
        'src/logic/action/options_generated.h',

        'src/logic/action/Idle.h',
        'src/logic/action/Idle.cpp',

        'src/logic/action/GoToAdjacent.h',
        'src/logic/action/GoToAdjacent.cpp',

        'src/logic/action/machine/OutputPick.h',
        'src/logic/action/machine/OutputPick.cpp',

        'src/logic/action/deposit/Extract.h',
        'src/logic/action/deposit/Extract.cpp',

        'src/logic/action/construction/Construct.h',
        'src/logic/action/construction/Construct.cpp',

        'src/logic/action/itembag/Give.h',
        'src/logic/action/itembag/Give.cpp',

        'src/logic/action/itembag/Pick.h',
        'src/logic/action/itembag/Pick.cpp',


          


        'src/task/Task.h',
        'src/task/Construction.h',
        'src/task/action/ItemTransfert.h',
        'src/task/action/Construct.h',
        'src/task/action/Extract.h',
       
        
        'src/ui/Canvas.h',
        'src/ui/Main.h',
        'src/ui/InputNumber.h',
        'src/ui/StorageList.h',
        'src/ui/StorageListItem.h',
        'src/ui/MachinePanel.h',


        'src/command/Command.h',
        'src/command/Command.cpp',
        'src/command/StorageSetItemRequestQuantity.h',
        'src/command/SelectEntity.h',
        'src/command/AddConstructionTask.h',
        'src/command/CancelConstructionTask.h',
        

        'src/asset/ItemTable.h',
        'src/asset/TileType_generated.h',
        'src/asset/ItemTable_generated.h',
        'src/asset/TileIndexes_generated.h',
        'src/asset/ConstructionRecipeTable_generated.h',

        'src/asset/CraftRecipeTable.h',
        'src/asset/CraftRecipeTable_generated.h',

        'src/asset/MachineTable.h',
        'src/asset/MachineTable_generated.h',

        


        'src/TheGridSystem.h',

        'src/TaskBuilder.h',
        

        'src/ItemGrid.h',
        'src/ItemBag.h',

        'src/ComponentManager.h',
        'src/Components.h',
        
        'src/EntityManager.h',
        'src/Entities.h',
        'src/Entities.cpp',
        'src/ValueArray.h',
        
        'src/types.h',


        'src/ToyGrid.h',
        
        'src/ConstructionGrid.h',


      ],
    },
  ],
}