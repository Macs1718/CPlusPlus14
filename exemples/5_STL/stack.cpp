# include <stack>
# include <iostream>
# include <string>

int main()
{
  std::stack<std::string> phrase;
  phrase.emplace("milou."); phrase.emplace(" et "); phrase.emplace("Tintin");
  while (not phrase.empty()) {
      std::cout << phrase.top(); phrase.pop();
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
