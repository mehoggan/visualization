import os
import ycm_core
import platform
from clang_helpers import PrepareClangFlags

compilation_database_folder = ''
scriptdir = os.path.dirname(os.path.realpath(__file__))
testdir = os.path.join(scriptdir, 'tests')
gtest_src_dir = os.path.join(os.path.join(os.path.join(scriptdir, 'build'),
                             'googletest-src'), 'googletest')
openggl_graphics_dir = os.path.join(os.path.join(scriptdir, 'build'),
                                    'opengl_graphics-src')
openggl_math_dir = os.path.join(os.path.join(scriptdir, 'build'),
                                'opengl_math-src')
glm_dir = os.path.join(os.path.join(scriptdir, 'build'), 'glm-src')

flags = [
         '-std=c++11',
         '-x',
         'c++',
         '-DQT_CORE_LIB',
         '-DQT_GUI_LIB',
         '-DQT_NETWORK_LIB',
         '-DQT_QML_LIB',
         '-DQT_QUICK_LIB',
         '-DQT_SQL_LIB',
         '-DQT_WIDGETS_LIB',
         '-DQT_XML_LIB',
         '-I', '.',
         '-I', os.path.join(scriptdir, 'include'),
         '-I', os.path.join(testdir, 'include'),
         '-I', os.path.join(gtest_src_dir, 'include'),
         '-I', os.path.join(openggl_graphics_dir, 'include'),
         '-I', os.path.join(openggl_math_dir, 'include'),
         '-I', glm_dir,
         '-D_POSIX_C_SOURCE 199309LL',
         '-D_DARWIN_C_SOURCE',
         '-D_XOPEN_SOURCE 500'
]

if platform.system() == 'Darwin':
    qt_root = '/usr/local/Cellar/qt/5.9.1/Frameworks'
    flags.append('-I')
    flags.append(qt_root)
    child_dirs = os.listdir(qt_root)
    for thing in child_dirs:
        absolute_path = os.path.join(qt_root, thing)
        if '.framework' in thing and os.path.isdir(absolute_path):
            tmp = os.path.join(absolute_path, 'Headers')
            flags.append('-I')
            flags.append(tmp)
elif platform.system() == 'Linux':
    qt_root = '/opt/Qt5.7.0/5.7/gcc_64/include/'
    for root, dirs, files in os.walk(qt_root):
        for name in dirs:
            path = os.path.join(root, name)
            flags.append('-I')
            flags.append(path)

SOURCE_EXTENSIONS = ['.cpp', '.inl', '.mm']

if compilation_database_folder:
    database = ycm_core.CompilationDatabase(compilation_database_folder)
else:
    database = None


def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))


def MakeRelativePathsInFlagsAbsolute(flags, working_directory):
    if not working_directory:
        return flags
    new_flags = []
    make_next_absolute = False
    path_flags = ['-isystem', '-I', '-iquote', '--sysroot=']
    for flag in flags:
        new_flag = flag

        if make_next_absolute:
            make_next_absolute = False
            if not flag.startswith('/'):
                new_flag = os.path.join(working_directory, flag)

        for path_flag in path_flags:
            if flag == path_flag:
                make_next_absolute = True
                break

            if flag.startswith(path_flag):
                path = flag[len(path_flag):]
                new_flag = path_flag + os.path.join(working_directory, path)
                break

        if new_flag:
            new_flags.append(new_flag)
    return new_flags


def FlagsForFile(filename):
    if database:
        # Bear in mind that compilation_info.compiler_flags_ does NOT return a
        # python list, but a "list-like" StringVec object
        compilation_info = database.GetCompilationInfoForFile(filename)
        final_flags = PrepareClangFlags(
            MakeRelativePathsInFlagsAbsolute(
                compilation_info.compiler_flags_,
                compilation_info.compiler_working_dir_),
            filename)
    else:
        relative_to = DirectoryOfThisScript()
        final_flags = MakeRelativePathsInFlagsAbsolute(flags, relative_to)

    return {
        'flags': final_flags,
        'do_cache': True
    }
