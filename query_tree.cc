// Josh Winton
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>

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

template <typename TreeType>
bool FindAcronyms(string &a_rec_seq, TreeType &a_tree){
  SequenceMap my_map(a_rec_seq, "");
  if(a_tree.contains(my_map) == false){
    std::cout << "Not Found" << '\n';
    return false;
  } else {
    cout << a_tree.find(my_map) << endl;
  }
  return true;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  // a_tree.printTree(); // Uncomment to print full tree
  string a_rec_seq;
  string b_rec_seq;
  string c_rec_seq;
  cin >> a_rec_seq >> b_rec_seq >> c_rec_seq;
  FindAcronyms(a_rec_seq, a_tree);
  FindAcronyms(b_rec_seq, a_tree);
  FindAcronyms(c_rec_seq, a_tree);
  return 0;
}
