#!/bin/sh

LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:lib" java -cp lib/jfuse.jar org.catacombae.jfuse.examples.HelloFS "$@"
