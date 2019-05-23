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

cc = meson.get_compiler('c')
dl_dep = cc.find_library('dl', required : false)
m_dep = cc.find_library('m', required : false)
readline_dep = dependency('readline', required : false)

os = host_machine.system()

is_emscripten = os == 'emscripten'
is_linux = os == 'linux'
is_macos = os == 'darwin'  # FIXME: also could be iOS
is_posix = cc.has_header_symbol('unistd.h', '_POSIX_VERSION')
is_windows = os == 'windows'

conf = configuration_data()
conf.set('LUA_DL_DLL', is_windows and not is_posix)
conf.set('LUA_USE_DLOPEN', is_posix and not is_emscripten)
conf.set('LUA_USE_LINUX', is_linux)
conf.set('LUA_USE_MACOS', is_macos)
conf.set('LUA_USE_POSIX', is_posix)
conf.set('LUA_USE_READLINE', readline_dep.found())
conf.set('LUA_USE_WINDOWS', is_windows)

luaconf_auto = configure_file(
    configuration : conf,
    output : 'luaconf_auto.h',
)

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

lua_libs = {}
lua_all_libdeps = []

foreach lib : lua_lib_names
    the_lib = library('lua-@0@'.format(lib),
        luaconf_auto,
        '@0@.c'.format(lib),
        dependencies : lua_dep,
    )

    if lib == 'lmathlib'
        deps = m_dep
    elif lib == 'loadlib'
        deps = dl_dep
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

lua_linit = library('lua-linit',
    luaconf_auto,
    'linit.c',
    dependencies : [lua_dep, lua_all_libdeps],
)

lua_stdlib_dep = declare_dependency(
    link_with : lua_linit,
    dependencies : lua_all_libdeps,
    include_directories : '.',
)

lua_exe = executable('lua',
    luaconf_auto,
    'lua.c',
    dependencies : [lua_dep, lua_stdlib_dep, readline_dep],
    build_by_default : not meson.is_subproject(),
    native : true,
)

# FIXME: this doesn't build yet, needs updating
luac_exe = executable('luac',
    luaconf_auto,
    'luac.c',
    dependencies : [lua_dep],
    build_by_default : false,  # not meson.is_subproject(),
    native : true,
)
