from distutils.core import setup, Extension

setup(name='example_dll',
    ext_modules=[
        Extension('example_dll',
            ['wrap.c'],
            include_dirs = ['.'],
            define_macros = [('FOO','1')],
            undef_macros = ['BAR'],
            library_dirs = ['.'],
            libraries = ['example']
            )
        ]
)