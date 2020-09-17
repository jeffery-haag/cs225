/**
 * @file kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *
 * @author Zesheng Wang
 * @author Wade Fagen-Ulmschneider
 * @author Cinda Heeren
 * @author Jack Toole
 * @author Sean Massung
 */

#pragma once

#include <vector>
#include "util/coloredout.h"
#include "point.h"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/**
 * KDTree class: implemented using Points in Dim dimensional space (given
 * by the template parameter).
 */
template <int Dim>
class KDTree
{
  private:
    /**
     * Internal structure for a node of KDTree.
     * Contains left, right children pointers and a K-dimensional point
     */
    struct KDTreeNode
    {
      Point<Dim> point;
      KDTreeNode *left, *right;

      KDTreeNode() : point(), left(NULL), right(NULL) {}
      KDTreeNode(const Point<Dim> &point) : point(point), left(NULL), right(NULL) {}
    };

  public:



    bool smallerDimVal(const Point<Dim>& first, const Point<Dim>& second,
                       int curDim) const;

    bool shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest,
                       const Point<Dim>& potential) const;



    KDTree(const vector<Point<Dim>>& newPoints);


    KDTree(const KDTree<Dim>& other);

    KDTree const &operator=(const KDTree<Dim>& rhs);


    ~KDTree();


    Point<Dim> findNearestNeighbor(const Point<Dim>& query) const;


    void printTree(ostream& out = cout,
                   colored_out::enable_t enable_bold = colored_out::COUT,
                   int modWidth = -1) const;

  private:

    /** Internal representation, root and size **/
    KDTreeNode *root;
    size_t size;

    /** Helper function for grading */
    int getPrintData(KDTreeNode * subroot) const;

    /** Helper function for grading */
    void printTree(KDTreeNode * subroot, std::vector<std::string>& output,
                   int left, int top, int width, int currd) const;

                   ////////////////////////////////
    vector<Point<Dim>> list;
    KDTreeNode* recBuild(int dim, int beg, int end);
    void quickSelect(int dim,int left,int right,int k);
    int partition(int dim,int left,int right,int k);
    void delHelper(KDTreeNode* curr);
   int nnHelp(const Point<Dim>& query, int curr, int left, int right, int dim) const;
    Point<Dim> best;
    int dist;
    int distance(Point<Dim> a,Point<Dim> b) const;
    //Point<Dim>* best=new Point<Dim>;
};

#include "kdtree.hpp"
#include "kdtree_extras.hpp"
