from distutils.core import setup, Extension
setup(name='murmur3',
      ext_modules=[Extension('murmur3',
                             sources=['murmur3module.c',
                                      'murmur3.c'])])
