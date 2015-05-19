{
  "target_defaults": {
    "default_configuration": "Release_x64",
    "configurations": {
      'Base': {
        "abstract": 1,
        'msvs_settings': {
          'VCCLCompilerTool': {
            'ObjectFile': '$(IntDir)/%(RelativeDir)/',
          },
          'VCLinkerTool': {
            'SubSystem': '2', # 1: Console, 2: Windows
            'LinkTimeCodeGeneration': 1,
            'OptimizeReferences': 2,
            'EnableCOMDATFolding': 2,
            'LinkIncremental': 1,
          }
        },
      },
      'Base_Win32': {
        "abstract": 1,
        "msvs_configuration_platform": "Win32",
      },
      'Base_x64': {
        "abstract": 1,
        "msvs_configuration_platform": "x64",
      },
      'Base_Debug': {
        "abstract": 1,
        'defines': [ 'DEBUG', '_DEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'Optimization': 0,
            'RuntimeLibrary': '1' # 0: MT, 1: MTd, 2: /MD, 3: /MDd
          },
          'VCLinkerTool': {
            'GenerateDebugInformation': 'true',
          }
        },
      },
      'Base_Release': {
        "abstract": 1,
        'defines': [ 'NDEBUG' ],
        'msvs_settings': {
            'VCCLCompilerTool': {
              'Optimization': 3,
              'RuntimeLibrary': '0' # 0: MT, 1: MTd, 2 /MD, 3 /MDd
          },
        },
      },
      "Debug_Win32": {
        'inherit_from': ['Base', 'Base_Win32', 'Base_Debug'],
      },
      "Debug_x64": {
        'inherit_from': ['Base', 'Base_x64', 'Base_Debug'],
      },
      "Release_Win32": {
        'inherit_from': ['Base', 'Base_Win32', 'Base_Release'],
      },
      "Release_x64": {
        'inherit_from': ['Base', 'Base_x64', 'Base_Release'],
      }
    }, # configurations
    #default
      'type': 'executable',
      'msvs_guid': '5ECEC9E5-8F23-47B6-93E0-C3B328B3BE65',
      'msvs_settings': {
        'VCLinkerTool': {
          'AdditionalDependencies': [
            'Gdi32.lib',
            'User32.lib',
            'Comctl32.lib',
            'Advapi32.lib',
            'Vfw32.lib', # video
            'Ole32.lib', # video
            'OleAut32.lib', # video
          ]
        }
      },
      'include_dirs': [
        '../lib/khronos/include',
        '../lib/SDL2/include',
        '../lib/liquidfun/liquidfun/Box2D',

        '../src',
        '../lib/nanovg/src',
        '../lib/flatbuffers/include',

        '../lib/libwebp/src',

        '../lib/mathfu/dependencies/vectorial/include',
        '../lib/mathfu/include',

        '../lib/nanomsg/src',
      ],
      'libraries': [
      ],
      'link_settings': {
        'configurations': {
          'Debug_x64': {
              'library_dirs': [
                '../lib/SDL2/VisualC/SDL/x64/Debug',
                '../lib/SDL2/VisualC/SDLmain/x64/Debug',
              ]
          },
          'Debug_Win32': {
              'library_dirs': [
                '../lib/SDL2/VisualC/SDL/Win32/Debug',
                '../lib/SDL2/VisualC/SDLmain/Win32/Debug',
                '../lib/liquidfun/liquidfun/Box2D/Box2D/Debug',
                '../lib/libwebp/output/debug-static/x86/lib',
                '../build/Debug/lib',
                '../lib/nanomsg/build/Debug'
              ]
          },
        }
      },
  },
}