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
      '-lnanomsg',
      
    ],
  },
  'targets': [
    {
      'type': 'executable',
      'target_name': 'ui',
      'sources': [
        'src/ui.cpp',

        'src/Application.h',
        'src/Application.cpp',

        
        'src/ui/Canvas.h',

        'src/ui/InputNumber.h',
        'src/ui/StorageList.h',
        'src/ui/StorageListItem.h',
      ],
    },
  ],
}