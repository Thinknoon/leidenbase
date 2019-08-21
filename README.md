# Leidenbase

An R to C interface that runs the Leiden community detection algorithm to find a basic partition. It is the equivalent of the find_partition() function that is given in the Leidenalg distribution file 'leiden/src/functions.py' and includes the underlying Leidenalg C++ source code files of Leidenalg release version 0.7.0. The Leiden algorithm is described in

> *From Louvain to Leiden: guaranteeing well-connected communities.*  
   V. A. Traag, L. Waltman, and N. J. van Eck,  
   Scientific Reports (2019), DOI: 10.1038/s41598-019-41695-z  


## Getting Started

### Prerequisites

This distribution requires software development tools including C, C++, and FORTRAN compilers. These compilers are provided often with your operating system or as packages. The R Project distributes [FORTRAN compilers for MacOS](https://cran.r-project.org/bin/macosx/tools/).

### Installing
  
#### Installing from R
  
Use devtools::install_github()

```
devtools::install_github('https://github.com/cole-trapnell-lab/leidenbase.git')
``` 

### Leidenbase functions

The R wrapper for running the Leiden algorithm find partition function is  

    leiden_find_partition <- function( igraph,
                               partition_type = c( 'RBConfigurationVertexPartition',
                                                   'CPMVertexPartition',
                                                   'ModularityVertexPartition',
                                                   'RBERVertexPartition',
                                                   'SignificanceVertexPartition',
                                                   'SurpriseVertexPartition' ),
                               initial_membership = NULL,
                               edge_weights = NULL,
                               node_sizes = NULL,
                               seed = NULL,
                               resolution_parameter = 0.5,
                               num_iter = 2 )

The C++ wrapper for running the Leiden algorithm find partition function
is  


    int leidenFindPartition( igraph_t *pigraph,
                             std::string const partitionType,
                             std::vector < size_t > const *pinitialMembership,
                             std::vector < double > const *pedgeWeights,
                             std::vector < size_t > const *pnodeSizes,
                             size_t seed,
                             double resolutionParameter,
                             int numIter,
                             std::vector < size_t > *pmembership,
                             std::vector < double > *pcommunityModularity,
                             double *pquality,
                             int *pstatus )`


## Licenses

Leidenbase and leidenalg are distributed under the GPL-3+ license. The C igraph library is distributed under the GPL-2+ license. Licenses for software libraries redistributed with the C igraph library are in LICENSE files in the corresponding sub-directories.

## Acknowledgements

We express our gratitude to the authors of the igraph and Leidenalg packages for designing, writing, and making them freely available as source code.

