/*
 *  Licence
 *  -------
 *
 *  Copyright (C) 2016 V.A. Traag
 *
 *  This file is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any later
 *  version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 *  PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program. If not, see http://www.gnu.org/licenses/.
 */

#ifndef OPTIMISER_H
#define OPTIMISER_H
#include "GraphHelper.h"
#include "MutableVertexPartition.h"
#include <set>
#include <map>

#include <iostream>
using std::cerr;
using std::endl;
using std::set;
using std::map;

/****************************************************************************
Class for doing community detection using the Leiden algorithm.

Given a certain partition type is calls diff_move for trying to move a node
to another community. It moves the node to the community that *maximises*
this diff_move. If no further improvement is possible, the graph is
aggregated (collapse_graph) and the method is reiterated on that graph.
****************************************************************************/

class Optimiser
{
  public:
    Optimiser();
    double optimise_partition(MutableVertexPartition* partition);
    template <class T> T* find_partition(Graph* graph);
    template <class T> T* find_partition(Graph* graph, double resolution_parameter);

    // The multiplex functions that simultaneously optimise multiple graphs and partitions (i.e. methods)
    // Each node will be in the same community in all graphs, and the graphs are expected to have identical nodes
    // Optionally we can loop over all possible communities instead of only the neighbours. In the case of negative
    // layer weights this may be necessary.
    double optimise_partition(vector<MutableVertexPartition*> partitions, vector<double> layer_weights);

    double move_nodes(MutableVertexPartition* partition);
    double move_nodes(MutableVertexPartition* partition, int consider_comms);
    double move_nodes(vector<MutableVertexPartition*> partitions, vector<double> layer_weights);
    double move_nodes(vector<MutableVertexPartition*> partitions, vector<double> layer_weights, int consider_comms, int consider_empty_community);

    double merge_nodes(MutableVertexPartition* partition);
    double merge_nodes(MutableVertexPartition* partition, int consider_comms);
    double merge_nodes(vector<MutableVertexPartition*> partitions, vector<double> layer_weights);
    double merge_nodes(vector<MutableVertexPartition*> partitions, vector<double> layer_weights, int consider_comms);

    double move_nodes_constrained(MutableVertexPartition* partition, MutableVertexPartition* constrained_partition);
    double move_nodes_constrained(MutableVertexPartition* partition, int consider_comms, MutableVertexPartition* constrained_partition);
    double move_nodes_constrained(vector<MutableVertexPartition*> partitions, vector<double> layer_weights, MutableVertexPartition* constrained_partition);
    double move_nodes_constrained(vector<MutableVertexPartition*> partitions, vector<double> layer_weights, int consider_comms, MutableVertexPartition* constrained_partition);

    double merge_nodes_constrained(MutableVertexPartition* partition, MutableVertexPartition* constrained_partition);
    double merge_nodes_constrained(MutableVertexPartition* partition, int consider_comms, MutableVertexPartition* constrained_partition);
    double merge_nodes_constrained(vector<MutableVertexPartition*> partitions, vector<double> layer_weights, MutableVertexPartition* constrained_partition);
    double merge_nodes_constrained(vector<MutableVertexPartition*> partitions, vector<double> layer_weights, int consider_comms, MutableVertexPartition* constrained_partition);

    inline void set_rng_seed(size_t seed) { igraph_rng_seed(&rng, seed); };

    virtual ~Optimiser();

    int consider_comms;  // Indicates how communities will be considered for improvement. Should be one of the parameters below
    int refine_partition; // Refine partition before aggregating
    int refine_consider_comms; // Indicates how communities will be considered for improvement within the refinement. Should be one of the parameters below
    int optimise_routine; // What routine to use for optimisation
    int refine_routine; // What routine to use for optimisation
    int consider_empty_community; // Determine whether to consider moving nodes to an empty community

    static const int ALL_COMMS = 1;       // Consider all communities for improvement.
    static const int ALL_NEIGH_COMMS = 2; // Consider all neighbour communities for improvement.
    static const int RAND_COMM = 3;       // Consider a random commmunity for improvement.
    static const int RAND_NEIGH_COMM = 4; // Consider a random community among the neighbours for improvement.

    static const int MOVE_NODES = 10;  // Use move node routine
    static const int MERGE_NODES = 11; // Use merge node routine

  protected:

  private:
    void print_settings();

    igraph_rng_t rng;
};

template <class T> T* Optimiser::find_partition(Graph* graph)
{
  T* partition = new T(graph);
  #ifdef DEBUG
    cerr << "Use default partition (all nodes in own community)" << endl;
  #endif
  this->optimise_partition(partition);
  return partition;
}

template <class T> T* Optimiser::find_partition(Graph* graph, double resolution_parameter)
{
  T* partition = new T(graph, resolution_parameter);
  #ifdef DEBUG
    cerr << "Use default partition (all nodes in own community)" << endl;
  #endif
  this->optimise_partition(partition);
  return partition;
}
#endif // OPTIMISER_H
