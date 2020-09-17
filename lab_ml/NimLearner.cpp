/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Play45er 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true)
{
    string tok=to_string(startingTokens);
    startingVertex_="p1-"+tok;

    for (int a=startingTokens;a>=0;a--)
    {
      unsigned i=a;
      Vertex newV1="p1-"+to_string(i);
      Vertex newV2="p2-"+to_string(i);
      g_.insertVertex(newV1);
      g_.insertVertex(newV2);

      if (i<startingTokens)
      {
        g_.insertEdge("p2-"+to_string(i+1),newV1);
        g_.setEdgeWeight("p2-"+to_string(i+1),newV1,0);
        g_.insertEdge("p1-"+to_string(i+1),newV2);
        g_.setEdgeWeight("p1-"+to_string(i+1),newV2,0);
      }
      if (i<startingTokens-1)
      {
        g_.insertEdge("p2-"+to_string(i+2),newV1);
        g_.setEdgeWeight("p2-"+to_string(i+2),newV1,0);
        g_.insertEdge("p1-"+to_string(i+2),newV2);
        g_.setEdgeWeight("p1-"+to_string(i+2),newV2,0);
      }
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const
{
  Vertex iter=startingVertex_;
  vector<Edge> path;

  while (!(iter =="p1-0" || iter =="p2-0"))
  {
    string coinsRem=iter.substr(3,iter.length()-1);
    int coinLeft=stoi(coinsRem);

    vector<Vertex> availible=g_.getAdjacent(iter);
    int a=(rand()*100);
    if (coinLeft==1)
    {
      path.push_back(Edge(iter,availible[0]));
      iter=availible[0];
    }
    else if (a%2==0)
    {
      path.push_back(Edge(iter,availible[0]));
      iter=availible[0];
    }
    else
    {
      path.push_back(Edge(iter,availible[1]));
      iter=availible[1];
    }

  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path)
{
   string winner=path.back().source.substr(1);
   for (Edge curr : path)
   {

     if (curr.source.substr(1)==winner) g_.setEdgeWeight(curr.source,curr.dest,g_.getEdgeWeight(curr.source,curr.dest)+1);
     else g_.setEdgeWeight(curr.source,curr.dest,g_.getEdgeWeight(curr.source,curr.dest)-1);

 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
