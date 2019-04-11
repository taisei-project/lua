project('lua', 'c',
    license : 'MIT',
    version : '5.4-taisei',
    meson_version : '>=0.49.0',
    default_options : [
        'c_std=c11',
        'default_library=static',
    ]
)

if get_option('b_ndebug') == 'true' or get_option('b_ndebug') == 'if-release' and not get_option('debug')
    add_project_arguments('-DLUA_USE_APICHECK', language : 'c')
endif

lua_core_src = files(
    'lapi.c',
    'lcode.c',
    'lctype.c',
    'ldebug.c',
    'ldo.c',
    'ldump.c',
    'lfunc.c',
    'lgc.c',
    'llex.c',
    'lmem.c',
    'lobject.c',
    'lopcodes.c',
    'lparser.c',
    'lstate.c',
    'lstring.c',
    'ltable.c',
    'ltm.c',
    'lundump.c',
    'lvm.c',
    'lzio.c',
)

liblua = library('lua',
    lua_core_src,
    build_by_default : false,
)

lua_dep = declare_dependency(
    link_with : liblua,
    include_directories : '.',
)

lua_lib_names = [
    'lauxlib',
    'lbaselib',
    'lcorolib',
    'ldblib',
    'liolib',
    'lmathlib',
    'loadlib',
    'loslib',
    'lstrlib',
    'ltablib',
    'lutf8lib',
]

libm = meson.get_compiler('c').find_library('m', required : false)

lua_libs = {}
lua_all_libdeps = []

foreach lib : lua_lib_names
    the_lib = library('lua-@0@'.format(lib),
        '@0@.c'.format(lib),
        dependencies : lua_dep,
    )

    if lib == 'lmathlib'
        deps = libm
    else
        deps = []
    endif

    dep = declare_dependency(
        link_with : the_lib,
        dependencies : deps,
        include_directories : '.',
    )

    lua_all_libdeps += dep
    set_variable('lua_@0@_dep'.format(lib), dep)
endforeach

lua_exe = executable('lua',
    'lua.c', 'linit.c',
    dependencies : [lua_dep, lua_all_libdeps],
    build_by_default : not meson.is_subproject(),
    native : true,
)

lua_exe = executable('luac',
    'luac.c',
    dependencies : [lua_dep],
    build_by_default : not meson.is_subproject(),
    native : true,
)
