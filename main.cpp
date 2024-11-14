#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>

std::string escapeQuotes(const std::string &str) {
  std::string escaped = str;
  size_t pos = 0;
  while ((pos = escaped.find("\"", pos)) != std::string::npos) {
    escaped.replace(pos, 1, "\\\"");
    pos += 2;
  }
  return escaped;
}

void sendNotification(const std::string &message, const std::string &title) {
  std::string escapedMessage = escapeQuotes(message);
  std::string escapedTitle = escapeQuotes(title);
  std::string script = "terminal-notifier -title \"" + escapedTitle +
                       "\" -message \"" + escapedMessage + "\" -timeout 10";
  system(script.c_str());
}

void runPomodoro() {
  int countPomodoros = 0;

  while (true) {
    sendNotification("Start focusing!", "Work Time");
    std::this_thread::sleep_for(std::chrono::minutes(25));

    countPomodoros++;

    if (countPomodoros < 4) {
      sendNotification("Take a 5 min break", "Short Break!");
      std::this_thread::sleep_for(std::chrono::minutes(5));
    } else {
      sendNotification("Take a 15 min break", "Long Break!");
      std::this_thread::sleep_for(std::chrono::minutes(15));
      countPomodoros = 0;
    }

    if (countPomodoros < 4) {
      sendNotification("Break is over! Ready for another session?",
                       "Back to Work");
    } else {
      sendNotification("Long break is over! Ready to start fresh?",
                       "New Cycle");
    }
  }
}

int main() {
  runPomodoro();
  return 0;
}
