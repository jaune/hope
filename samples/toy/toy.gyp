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

        'src/resource.h',





        'src/TileIndexes_generated.h',

        'src/TileRenderer.h',

        'src/Task.h',
        'src/Plan.h',
        'src/Agent.h',
        

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


        'src/systems/Task.h',
        'src/systems/task/Construct.h',
        'src/systems/task/ItemTransfert.h',
        'src/systems/task/Extract.h',
        'src/systems/task/Construction.h',

        
        'src/ui/Canvas.h',

        'src/ui/InputNumber.h',
        'src/ui/StorageList.h',
        'src/ui/StorageListItem.h',


        'src/command/Command.h',
        'src/command/StorageSetItemRequestQuantity.h',


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
        
        
        'src/ItemTable_generated.h',

        'src/ToyGrid.h',
        'src/ConstructionRecipeTable_generated.h',
        'src/ConstructionGrid.h',


      ],
    },
  ],
}