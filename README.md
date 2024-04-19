Usage:

cd path/to/build_dot_txt

strmake

Example of a `build.txt` is under the `example_script` directory.

Edit: Some of the static libraries might not be loaded for some reason (e.g. bass.lib refused to load for me). In such cases, use `pragma comment` instead. 
