from setuptools import setup
from distutils.extension import Extension
from Cython.Build import cythonize



setup(
    name='levypy',
        version='0.1.0',
        py_modules=['levypy'],
    ext_modules = cythonize([
    Extension("levypy", ["src/levypy/levypy.pyx"],
              libraries=["leveldb"])
    ]))