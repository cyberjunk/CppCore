from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sysconfig
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

def get_platname():
    print(sysconfig.get_platform())
    TARGET_OS   = os.environ.get("TARGET_OS",   None)
    TARGET_ARCH = os.environ.get("TARGET_ARCH", None)
    if TARGET_OS == "win":
        if   TARGET_ARCH == "x86":   return "win32"
        elif TARGET_ARCH == "x64":   return "win-amd64"
        elif TARGET_ARCH == "arm64": return "win-arm64"
    elif TARGET_OS == 'osx':
        OSXMINVERSION = os.environ.get("OSXMINVERSION", "")
        return "macosx-" + OSXMINVERSION + "-universal2"  
    elif TARGET_OS == 'linux':
        if   TARGET_ARCH == "x86":   return "linux-i686"
        elif TARGET_ARCH == "x64":   return "linux-x86_64"
        elif TARGET_ARCH == "arm64": return "linux-aarch64"
        elif TARGET_ARCH == "arm":   return "linux-armv7hl"
    return sysconfig.get_platform()

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
    packages=['cppcore', 'cppcore.util'],
    package_dir={'cppcore': 'cppcore'},
    package_data={'': ['libcppcore.*']},
    options={
        "bdist_wheel": {
            "plat_name": get_platname(),
        },
    },
    #ext_modules = [Extension("", [])],
    #cmdclass = {'build_ext': my_build_ext},
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows",
    ]
)
