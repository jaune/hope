{
  'includes': [
    '../../tool/base.gypi'
  ],
  "target_defaults": {
    "libraries": [
      '-llibhope',
      '-lSDL2',
      '-lSDL2main',
    ],
  },
  'targets': [
    {
      'type': 'executable',
      'target_name': 'nanovg',
      'sources': [
        'src/nanovg.cpp',
        'src/nanovg/demo.h',
        'src/nanovg/demo.cpp',
      ],
    },
  ],
}