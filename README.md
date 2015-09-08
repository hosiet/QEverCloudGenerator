# QEverCloudGenerator
The parser of [evernote-thrift](https://github.com/evernote/evernote-thrift) IDL files generating headers and sources for [QEverCloud](https://github.com/d1vanov/QEverCloud) library. 

This repository is a fork of original [mgsxx's](https://github.com/mgsxx/QEverCloudGenerator) code with the build system changed from qmake to CMake. The original qmake project heavily relies on esoteric qmake trickery which is in fact so esoteric that qmake from Qt 5.5 on Linux keeps crashing for me on attempt to use it on that project for whatever reason. Given that circumstance, my personal prefence for CMake build system and my desire to be able to use the generator, here is this fork. 

The change of the build system is not the only difference between this fork and the original project. The differences include:
* Sufficient simplification and minimization of the project; a lot of original qmake tricks were not reproduced in CMake project just because it was not my immediate purpose of getting things working somehow.
* Right now the modified project doesn't include all QEverCloud sources, sources for QEverCloud tests and examples. Possibly that would be changed in future.
* Support for using either Qt 4 or Qt 5 to build the parser and generate QEverCloud sources.

## Some explanations about the sources

The project contains multiple subdirs some of which employ custom CMake commands and targets to include the steps necessary for parsing thrift files and generating QEverCloud sources within the build process. 

The subprojects in the order they are building:

- [**lemon**](http://www.hwaci.com/sw/lemon/). It's a great LALR(1) parser written in C.
- **thrift_parser**. The meat. It uses LEMON to parse the Evernote Thrift files (it is NOT a general purpose Thrift parser) to gather info from the files (including comments) and then generates the bulk of the QEverCloud.
- **generated**. The subproject consisting entirely of custom CMake commands/targets using the **thrift_parser** for actual parsing and generation of QEverCloud sources. 
