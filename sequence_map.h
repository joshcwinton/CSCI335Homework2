// Josh Winton
// SequenceMap object definition for Project2 Part 1

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <string>
#include <vector>


class SequenceMap {
public:
  // Constructs a SequenceMap from two strings
  // enzyme_acronyms_ will contain only an_enz_acro
  SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
  }

  // Operates based on the regular string comp between the recognition_sequence_ strings
  bool operator<(const SequenceMap &rhs) const {
    return (recognition_sequence_<rhs.recognition_sequence_);
  }

  // bool rsequals(const SequenceMap &rhs) const {
  //   return (recognition_sequence_==rhs.recognition_sequence_);
  // }

  // Overloaded << for SequenceMap gives every item in enzyme_acronyms_
  friend std::ostream& operator<<(std::ostream& os, const SequenceMap& a){
    for(size_t i = 0; i < a.enzyme_acronyms_.size(); i++){
      os << a.enzyme_acronyms_[i] << ' ';
      // os << a.enzyme_acronyms_.size();
    }
    return os;
  }

  // Assumes recognition_sequence_s are equal to each other
  // Merges the other enzyme_acronym with this one without adding duplicates
  void Merge(const SequenceMap &other_sequence){
    bool match;
    for (size_t i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
      for (size_t j = 0; j < enzyme_acronyms_.size(); j++) {
        match = false;
        if(other_sequence.enzyme_acronyms_[i] == enzyme_acronyms_[j]){
          match = true;
          // break;
        }
      }
      if(match == false){
        enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
      }
    }
  }

  // Default big 5:
  // Destructor
  ~SequenceMap() = default;

  // Copy constructor
  SequenceMap (const SequenceMap & rhs) = default;

  // Move constructor
  SequenceMap (SequenceMap && rhs) = default;

  // Copy assignment
  SequenceMap & operator= (const SequenceMap & rhs) = default;

  // Move assignment
  SequenceMap & operator= (SequenceMap && rhs) = default;

private:
  std::string recognition_sequence_;
  std::vector<std::string> enzyme_acronyms_;
};

#endif
