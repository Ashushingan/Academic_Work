#!bin/bash
gprof kmeans_prof gmon.out | gprof2dot -o callgraph.dot
dot -Tpng callgraph.dot -o callgraph.png
