from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
#import sysconfig
#from packaging.version import Version

import os

class my_build_ext(build_ext):
    def build_extensions(self):
        pass


#export _PYTHON_HOST_PLATFORM="macosx-10.15-universal2"

#def get_platname():
#    # TODO: Cross-Compile...
#    return sysconfig.get_platform()

#version_string = os.environ.get("CPPCORE_VERSION3", "0.0.0")
#version = Version(version_string)

setup(
    name="CppCore",
    version=os.environ.get("CPPCORE_VERSION3", "0.0.0"),
    description="CppCore for Python",
    author="Clint Banzhaf",
    url="https://github.com/cyberjunk/CppCore",
    keywords=[
        "primes", "aes", "crypto", "encoding", 
        "hash", "hmac", "pbkdf2", "dh"
    ],
    include_package_data=True,
    package_data={'': ['libcppcore.*']},
    #options={
    #    "bdist_wheel": {
    #        "plat_name": get_platname(),
    #    },
    #},
    ext_modules = [Extension("", [])],
    cmdclass = {'build_ext': my_build_ext},
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows",
    ]
)
