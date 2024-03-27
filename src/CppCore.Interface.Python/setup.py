from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
#import sysconfig
from packaging.version import Version
import os

class my_build_ext(build_ext):
    def build_extensions(self):
        pass

#def get_platname():
#    # TODO: Cross-Compile...
#    return sysconfig.get_platform()

version_string = os.environ.get("RELEASE_VERSION", "0.0.0.dev0")
version = Version(version_string)

setup(
    version=str(version),
    include_package_data=True,
    package_data={'': ['libcppcore.dll', 'libcppcore.dylib', 'libcppcore.so']},
    #options={
    #    "bdist_wheel": {
    #        "plat_name": get_platname(),
    #    },
    #},
    ext_modules = [Extension("", [])],
    cmdclass = {'build_ext': my_build_ext},
)
