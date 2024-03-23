from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
#import sysconfig

class my_build_ext(build_ext):
    def build_extensions(self):
        pass

#def get_platname():
#    # TODO: Cross-Compile...
#    return sysconfig.get_platform()

setup(
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
