// <Your name>
// Main file for Part2(b) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

namespace {

string GetEnzymeAcronym(string & db_line){
  string r_string;
  int stop = 0;
  for (size_t i = 0; i < db_line.length(); i++) {
    if(db_line[i] == '/'){
      stop = i;
      break;
    }
  }
  r_string = db_line.substr(0, stop);
  db_line = db_line.substr(stop+1);
  return r_string;
}

string GetNextRecognitionSequence(string & db_line, string & a_reco_seq){
  string r_string;
  int stop = 0;
  for (size_t i = 0; i < db_line.length(); i++) {
    if(db_line[i] == '/'){
      stop = i;
      break;
    }
  }
  r_string = db_line.substr(0, stop);
  db_line = db_line.substr(stop+1);
  return r_string;
}

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  // You can use public functions of TreeType. For example:
  string db_line;
  int row = 1;
  int START_ROW = 11;
  int END_ROW = 780;

  ifstream db_file(db_filename);
  if(db_file.is_open()){
    // Read the file line-by-line:
    while (getline(db_file, db_line)) {
      if(row >= START_ROW && row <= END_ROW){
        // Get the first part of the line:
        string an_enz_acro = GetEnzymeAcronym(db_line);
        string a_reco_seq;
        while (db_line.length() > 1) {
          a_reco_seq = GetNextRecognitionSequence(db_line, a_reco_seq);
          SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
          if(a_tree.contains(new_sequence_map)){
            a_tree.find(new_sequence_map).Merge(new_sequence_map);
          } else {
            a_tree.insert(new_sequence_map);
          }
        }
      }
      row++;
    }
  }
}


// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)
  QueryTree(db_filename, a_tree); // 2b number 1
  int NodeCount = a_tree.countNodes();
  cout << "2: " <<  NodeCount << endl;
  int TotalDepth = a_tree.getTotalDepth();
  float AvgDepth = (float)NodeCount/TotalDepth;
  cout << "3a: " << AvgDepth << endl;
  float log2n = log2(NodeCount);
  float DepthRatio = AvgDepth/log2n; // Not done
  cout << "3b: " << DepthRatio << endl;


  string db_line;
  ifstream db_file(db_filename);
  int END_ROW = 480;
  int row = 0;
  int findCount = 0;
  if(db_file.is_open()){
    // Read the file line-by-line:
    while (getline(db_file, db_line)) {
      if(row <= END_ROW){
        SequenceMap my_map(db_line, "");
        a_tree.findCounter(my_map, findCount);
      }
      row++;
    }
  }
  db_file.close();
  int queryCount = row;
  cout << "4a: " << findCount/queryCount << " (Not sure about this one.)" << endl;
  float RecurAvgFind = (float)findCount/queryCount;
  cout << "4b: " << RecurAvgFind << endl; //not done
  

  int removeCount = 0;
  row = 0;
  ifstream db_file2(db_filename);
  if(db_file2.is_open()){
    // Read the file line-by-line:
    while (getline(db_file2, db_line)) {
      if(row <= END_ROW){
        SequenceMap my_map(db_line, "");
        a_tree.removeCounter(my_map, removeCount);
      }
      row++;
    }
  }
 
  cout << "5a: " << removeCount << endl;
  float RecurAvgRemove= (float)removeCount/row;
  cout << "5b: " << RecurAvgRemove << endl;
  cout << "6a: " << "Not Done" << endl;
  cout << "6b: " << "Not Done" << endl;
  cout << "6c: " << "Not Done" << endl;


}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);
  return 0;
}
