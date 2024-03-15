from setuptools import setup
import sysconfig

def get_platname():
    # TODO: Cross-Compile...
    return sysconfig.get_platform()

setup(
    include_package_data=True,
    package_data={'': ['libcppcore.dll', 'libcppcore.dylib', 'libcppcore.so']},
    options={
        "bdist_wheel": {
            "plat_name": get_platname(),
        },
    },
)
