#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// Part 2 — Frequency Counter (10 min)
// Task: Write a program that counts the frequency of words
// in a sentence using an unordered_map.
// Steps:
// 1. Take a line of text input from the user.
// 2. Split it into words (assume words are separated by spaces).
// 3. Use an unordered_map<string, int> to count occurrences of each word.
// 4. Display the word counts.

int main()
{
  string sentence;
  string newWord = "";
  char c;
  int counter = 0;
  unordered_map<string, int> words;
  cout << "Enter a sentence: ";
  getline(cin, sentence);
  for (int i = 0; i < sentence.size(); i++)
  {
    c = sentence[i];
    if (sentence[i] != ' ')
    {
      newWord += c;
    }
    else
    {
      words[newWord]++;
      newWord = "";
      counter = 0;
    }
  }
  if (!newWord.empty()) {
    words[newWord]++;
  }

  for (auto &pair : words)
  {
    cout << pair.first << ": " << pair.second << endl;
  }
  return 0;
}