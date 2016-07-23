#include <iostream>
#include <vector>
#include <pokerstove/penum/ShowdownEnumerator.h>

using namespace std;
using namespace pokerstove;

int main(int argc, char *argv[]) {
  bool verbose = false;
  if (argc != 3) {
    cout << "Need two arguments (got " << (argc - 1) << ")." << endl << " Usage: ps-eval hand1 hand2" << endl;
    return -1;
  }


  CardSet completeDeck;
  completeDeck.fill();


  CardDistribution hand1, hand2;
  hand1.parse(argv[1]);
  hand2.parse(argv[2]);
  if (verbose) {
    cout << "The whole deck has " << completeDeck.size() << " cards" << endl;
    cout << "Hand 1 '" << argv[1] << "' has " << hand1.size() << " two card combinations"  << endl;
    cout << "Hand 2 '" << argv[2] << "' has " << hand2.size() << " two card combinations"  << endl;
  }

  ShowdownEnumerator showdown;
  vector<EquityResult> result = showdown.calculateEquity(
    vector<CardDistribution>{hand1, hand2},
    CardSet(""),
    PokerHandEvaluator::alloc("h")
  );

  double share1 = result.at(0).winShares + result.at(0).tieShares;
  double share2 = result.at(1).winShares + result.at(1).tieShares;
  double total  = share1 + share2;

  if (verbose) {
    cout << "Hand 1 has "  << share1 / total * 100  << " % equity (" << result.at(0).str() << ")" << endl;
    cout << "Hand 2 has "  << share2 / total * 100  << " % equity (" << result.at(1).str() << ")" << endl;
  } else {
    cout << share1 / total << endl;
  }
}
