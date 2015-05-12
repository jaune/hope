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

        'src/Task.h',
        'src/Plan.h',
        'src/CellType.h',
        

        'src/NavigationGrid.h',

        

        'src/systems/TheGrid.h',
        'src/systems/Deposit.h',

        'src/systems/Action.h',
        'src/systems/action/AbstractActionSystem.h',
        'src/systems/action/ItemPick.h',
        'src/systems/action/ItemGive.h',
        'src/systems/action/Construct.h',
        'src/systems/action/Extract.h',
        'src/systems/action/GoToAdjacent.h',


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


        'src/TheGridSystem.h',
        'src/TaskSystem.h',

        'src/TaskBuilder.h',
        

        'src/ItemGrid.h',
        'src/ItemBag.h',

        'src/ComponentManager.h',
        'src/Components.h',
        
        'src/EntityManager.h',
        'src/Entities.h',
        'src/ValueArray.h',
        

        'src/ToyGrid.h',
        
        'src/ConstructionGrid.h',


      ],
    },
  ],
}