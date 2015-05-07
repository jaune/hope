{
  'includes': [
    '../../tool/base.gypi'
  ],
  "target_defaults": {
    "libraries": [
      '-llibhope',
      '-lSDL2',
      '-lSDL2main',
      '-lliquidfun',
    ],
  },
  'targets': [
    {
      'type': 'executable',
      'target_name': 'agent',
      'sources': [
        'src/agent.cpp',
        'src/resource.h',
        'src/PhysicsSystem.h',

        'src/ai.h',
        'src/ai.cpp',

        'src/world.h',
        'src/world.cpp',

        'src/action.h',
        'src/action.cpp',


      ],
    },
  ],
}