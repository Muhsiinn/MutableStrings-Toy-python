from setuptools import setup, Extension

mutable_string_module = Extension(
    name="mutable_string",
    sources=[
        "mutable_string_module.c",
        "mutable_string.c",
    ],
    include_dirs=["."],
)

setup(
    name="mutable-string",
    version="0.1.0",
    description="A mutable string implementation in C for Python",
    ext_modules=[mutable_string_module],
)
