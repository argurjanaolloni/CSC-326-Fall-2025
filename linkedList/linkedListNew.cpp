#include <iostream>
using namespace std;
// void gitshow() - ill work on this.
struct Commit
{
  int hash;
  string message;
  Commit *next;

  Commit(int h, const string &msg) : hash(h), message(msg), next(nullptr) {}
};

class CommitHistory
{
private:
  Commit *head;

public:
  CommitHistory() : head(nullptr) {}

  // void commit(const std::string& message); // append
  void commit(const string &message)
  {
    int hash = rand() % 10000; // Simulated hash
    Commit *newCommit = new Commit(hash, message);
    if (head == nullptr)
    {
      head = newCommit;
    }
    else
    {
      Commit *temp = head;
      while (temp->next != nullptr)
      {
        temp = temp->next;
      }
      temp->next = newCommit;
    }
  }
  // void log() const; // display all
  void log() const
  {
    // display all commits with the arrow between them : commit1 -> commit2
    if (head == nullptr)
    {
      cout << "There are no commits yet." << endl;
    }
    else
    {
      Commit *temp = head;
      while (temp->next != nullptr)
      {
        cout << temp->message << " --> ";
        temp = temp->next;
      }
      cout << temp->message << "." << endl;
    }
  }
  // void reset(); // Delete last commit
  void reset()
  { // delete the last node - release all memory. Display message: Last commit removed (reset).
    if (head == nullptr)
    {
      cout << "No commits to be deleted.";
    }
    else if (head->next == nullptr)
    {
      delete head;
      head = nullptr;
      cout << "Last commit removed (reset)." << endl;
    }
    else
    {
      Commit *temp = head;
      // while (temp->next != nullptr) this is what i had before
      while (temp->next->next != nullptr)
      {
        temp = temp->next;
      }
      delete temp->next;
      temp->next = nullptr;
      cout << "\nLast commit removed (reset)." << endl;
    }
  }
  // static CommitHistory merge(const CommitHistory &branch1, const CommitHistory &branch2);
  static CommitHistory merge(const CommitHistory &branch1, const CommitHistory &branch2)
  {
    /*
    Create a new linked list that will have a first branch followed by branch 2.
    Create all new nodes so that original branch 1 and branch 2 are not touched.
    Display a message "Branches merged.” when done!
    Return new branch(linked list)
    */
    CommitHistory merged;
    Commit *tempCommit = branch1.head;
    while (tempCommit != nullptr)
    {
      merged.commit(tempCommit->message);
      tempCommit = tempCommit->next;
    }
    tempCommit = branch2.head;
    while (tempCommit != nullptr)
    {
      merged.commit(tempCommit->message);
      tempCommit = tempCommit->next;
    }
    cout << "\nBranches merged" << endl;
    return merged;
  }

  // ~CommitHistory();
  ~CommitHistory()
  {
    // Release all memory
    Commit *temp = head;
    Commit *nodeToDelete = nullptr;
    while (temp != nullptr)
    {
      nodeToDelete = temp;
      temp = temp->next;
      delete nodeToDelete;
    }
    head = nullptr;
  }
};

int main()
{
  srand(time(0)); // For random hash generation

  CommitHistory master;
  master.commit("Initial commit");
  master.commit("Add README");
  master.commit("Implement login system");

  CommitHistory featureBranch;
  featureBranch.commit("Start feature X");
  featureBranch.commit("Fix bug in feature X");

  cout << "\n== Master Branch == ";
  master.log();

  cout << "\n== Feature Branch == ";
  featureBranch.log();

  cout << "\n== Reset last commit on master == ";
  master.reset();
  master.log();

  cout << "\n== Merged History =="; // merge should have 4 nodes, 2 from each master and featureBranch.
  CommitHistory merged = CommitHistory::merge(master, featureBranch);
  merged.reset();
  merged.log();

  cout << "\n== Master Branch Unchanged after merge == ";
  master.log();

  cout << "\n== Feature Branch Unchanged after merge == ";
  featureBranch.log();

  return 0;
}
