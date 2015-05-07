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
      '-lliquidfun',
      '-llibwebp_debug',
    ],
  },
  'targets': [
    {
      'type': 'executable',
      'target_name': 'tile',
      'sources': [
        'src/tile.cpp',

        'src/TileRenderer.h',

        'src/Application.h',
        'src/Application.cpp',
      ],
    },
  ],
}