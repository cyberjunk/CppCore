from setuptools import setup
import sysconfig
import os

def get_platname():
    TARGET_OS   = os.environ.get("TARGET_OS",   None)
    TARGET_ARCH = os.environ.get("TARGET_ARCH", None)
    if TARGET_OS == "win":
        if   TARGET_ARCH == "x86":   return "win32"
        elif TARGET_ARCH == "x64":   return "win-amd64"
        elif TARGET_ARCH == "arm64": return "win-arm64"
    elif TARGET_OS == 'osx':
        return "macosx-10.15-universal2"
    elif TARGET_OS == 'linux':
        if   TARGET_ARCH == "x86":   return "linux-i686"
        elif TARGET_ARCH == "x64":   return "linux-x86_64"
        elif TARGET_ARCH == "arm64": return "linux-aarch64"
        elif TARGET_ARCH == "arm":   return "linux-armv7hl"
    return sysconfig.get_platform()

setup(
    name="cppcore",
    version=os.environ.get("CPPCORE_VERSION", "0.0.0"),
    description="CppCore for Python",
    author="Clint Banzhaf",
    url="https://github.com/cyberjunk/CppCore",
    keywords=[
        "aes", "encoding", "bigint", "hash", "sha", "md5", 
        "hmac", "pbkdf2", "dh", "primes"
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
    classifiers=[
        "Development Status :: 4 - Beta",
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: MacOS :: MacOS X",
        "Operating System :: POSIX :: Linux",
        "Topic :: Scientific/Engineering :: Mathematics",
        "Topic :: Security :: Cryptography"
    ]
)
