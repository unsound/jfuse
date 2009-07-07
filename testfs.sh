#!/bin/sh

java -Djava.library.path=. -cp lib/jfuse.jar org.catacombae.jfuse.test.TestFS "$@"
