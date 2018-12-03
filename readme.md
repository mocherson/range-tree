# rangetree
Implementation of range tree, range tree with fractional cascading and interval tree

# Files
  - indexrtFC.h, indexrtFC.cpp:  rangetree implementation
  - rangetree2d.h, rangetree2d.cpp  2d-rangetree implementation
  - itvtree.h, itvtree.h  intervaltree intervaltree
  
# Getting Started  
  1. test basic 2d range tree, interval tree and rangetree with fractional cascading
 
  ```bash
  make
  
  ./Release/treecomp  datafile   queryfiles
  ```
   
  The results are generated in the path of queryfiles with suffix '.res'
  
  2. test NCList using R package 
  
  ```bash
  Rscript GRangetest.R
  ```
  
  Edit Line 14 and 15 to make sure your data paths are correct.
  The results will go to "timeout_gr.txt"

# Citation
```
@article{mao2018rangetree,
  title={Efficient Genomic Interval Queries Using Augmented Range Trees},
  author={Mao, Chengsheng and Eran, Alal and Luo, Yuan},
  journal={arXiv preprint arXiv:1806.01217},
  year={2018}
}
```
