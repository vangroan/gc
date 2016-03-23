
env = Environment(
        tools=['mingw'],
        CPPPATH='src',
        CFLAGS='-Wall --std=c99',
    )

source = [
    'src/main.c',
    'src/vm.c',
]

env.Program(target='build/gc', source=source)