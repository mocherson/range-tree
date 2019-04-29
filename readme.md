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
@article{mao2019efficient,
  title={Efficient Genomic Interval Queries Using Augmented Range Trees},
  author={Mao, Chengsheng and Eran, Alal and Luo, Yuan},
  journal={Scientific reports},
  volume={9},
  number={1},
  pages={5059},
  year={2019},
  publisher={Nature Publishing Group}
}
```
```
Mao, Chengsheng, Alal Eran, and Yuan Luo. "Efficient Genomic Interval Queries Using Augmented Range Trees." Scientific reports 9.1 (2019): 5059.
```
