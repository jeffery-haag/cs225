/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {


  flow_=g_;
  residual_=g_;
  source_=source;
  sink_=sink;
  maxFlow_=0;

  for (Vertex beg:flow_.getVertices())
  {
    for (Vertex end:flow_.getAdjacent(beg))
    {
      flow_.setEdgeWeight(beg,end,0);
      flow_.setEdgeLabel(beg,end,beg+end);

    }
  }
  for (Vertex beg:flow_.getVertices())
  {
    for (Vertex end:flow_.getAdjacent(beg))
    {
      residual_.insertEdge(end,beg);
      residual_.setEdgeLabel(end,beg,end+beg);
      residual_.setEdgeLabel(beg,end,beg+end);
      residual_.setEdgeWeight(end,beg,0);

    }
  }

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  if (path.size()<2)return 0;
  int smol=10000;
  for (unsigned i=0;i<path.size()-1;i++)
  {
    if (residual_.getEdgeWeight(path[i],path[i+1])<smol)
    smol=residual_.getEdgeWeight(path[i],path[i+1]);
  }
  return smol;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow()
{
  vector<Vertex> path;
  while (findAugmentingPath(source_,sink_,path))
  {
    int capacity=pathCapacity(path);
    maxFlow_=maxFlow_+capacity;
    for (unsigned i=0;i<path.size()-1;i++)
    {


      if (flow_.edgeExists(path[i],path[i+1]))
      {
        int dummy1=flow_.getEdgeWeight(path[i],path[i+1])+capacity;
        flow_.setEdgeWeight(path[i],path[i+1],dummy1);
      }

      else
      {
        int dummy2=flow_.getEdgeWeight(path[i+1],path[i])-capacity;
        flow_.setEdgeWeight(path[i+1],path[i],dummy2);

      }

      int dummy3=residual_.getEdgeWeight(path[i+1],path[i])+capacity;
      int dummy4=residual_.getEdgeWeight(path[i],path[i+1])-capacity;

      residual_.setEdgeWeight(path[i+1],path[i],dummy3);
      residual_.setEdgeWeight(path[i],path[i+1],dummy4);


    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
