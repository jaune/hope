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
      'target_name': 'destroy',
      'sources': [
        'src/destroy.cpp',
      ],
    },
  ],
}