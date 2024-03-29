from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os

class my_build_ext(build_ext):
    def build_extensions(self):
        pass

#WIN
#set VSCMD_ARG_TGT_ARCH=x64
#set VSCMD_ARG_TGT_ARCH=x86
#set VSCMD_ARG_TGT_ARCH=arm64

#MAC    
#export _PYTHON_HOST_PLATFORM="macosx-10.15-universal2"

#LINUX
#export _PYTHON_HOST_PLATFORM=linux_x86_64
#export _PYTHON_HOST_PLATFORM=linux_i686
#export _PYTHON_HOST_PLATFORM=linux_aarch64
#export _PYTHON_HOST_PLATFORM=linux_armv7hl

#def get_platname():
#    # TODO: Cross-Compile...
#    return sysconfig.get_platform()

setup(
    name="CppCore",
    version=os.environ.get("CPPCORE_VERSION", "0.0.0"),
    description="CppCore for Python",
    author="Clint Banzhaf",
    url="https://github.com/cyberjunk/CppCore",
    keywords=[
        "primes", "aes", "crypto", "encoding", 
        "hash", "hmac", "pbkdf2", "dh"
    ],
    include_package_data=True,
    package_dir={'': 'cppcore'},
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
