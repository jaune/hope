{
  'includes': [
    'tool/base.gypi'
  ],
  'targets': [
    {
      'type': 'static_library',
      'target_name': 'libhope',
      'sources': [
        'lib/nanovg/src/nanovg.c',

        'src/entry/entry_sdl.cpp',

        'src/console_sdl.cpp',

        'src/nvg.h',
        'src/nvg.cpp',

        'src/input/mouse.h',
        'src/input/mouse.cpp',
        
        'src/input/keyboard.h',
        'src/input/keyboard.cpp',
        

        'src/asset/asset.h',
        'src/asset/asset.cpp',

        'src/core/core_sdl.cpp',
        'src/opengles2_wrapper.c',

        'src/crypto/crypto.h',
        'src/crypto/crc32.cpp',

        'src/gles2/Pass.h',
        'src/gles2/VertexAttributeArray.h',
        'src/gles2/Framebuffer.h',

        'src/grid/Location.h',
        'src/grid/Grid.h',
        'src/grid/Grid.cpp',
        'src/grid/PathFinder.h',
        'src/grid/PathCrawler.h',
        'src/grid/FloodFillQuery.h',

        'src/grid/NavigationGrid.h',
        'src/grid/NavigationGrid.cpp',

        'src/ai/need.h',
        'src/ai/Agent.h',
        'src/ai/System.h',
        'src/ai/plan/Plan.h',
        'src/ai/plan/PlanTable.h',
        'src/ai/plan/Step.h',
        'src/ai/plan/StepTable.h',
        'src/ai/plan/StepTable.cpp',


        'src/profile.h',
        'src/profile.cpp',
      ],
    },
  ],
}