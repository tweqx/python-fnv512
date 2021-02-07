from distutils.core import setup, Extension

def main():
    setup(name="fnv512",
          version="1.0.0",
          description="Python library for the fnv-0/fnv-1/fnv-1a hashing functions",
          author="tweqx",
          ext_modules=[Extension("fnv512", ["fnv512.cpp"], extra_compile_args=['-std=c++2a', '-O3'])])

if __name__ == "__main__":
    main()
