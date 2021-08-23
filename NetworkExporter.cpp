// Criado por Pedro Henrique Toth
// Nenhum direito reservado
// 20/08/2021

//#include <bits/stdc++.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace std;
string data[255][5];
int list_size = 0;

void Write_Metrics() {
  string to_file;
  to_file = "Network Exporter - All data get from lsof -i -n -P";
  to_file = to_file + "\n";
  to_file = to_file + "format: network_exporter_port-index_data";
  to_file = to_file + "\n";
  to_file = to_file + "Data - Proccess Name, PID, User, IP Version, Transport Layer, Port";
  to_file = to_file + "\n";

  for (int x = 0; x <= list_size - 1; x++) {
    to_file = to_file + "network_exporter_" + to_string(x) + "_" + data[x][0] + "\n";
    to_file = to_file + "network_exporter_" + to_string(x) + "_" + data[x][1] + "\n";
    to_file = to_file + "network_exporter_" + to_string(x) + "_" + data[x][2] + "\n";
    to_file = to_file + "network_exporter_" + to_string(x) + "_" + data[x][3] + "\n";
    to_file = to_file + "network_exporter_" + to_string(x) + "_" + data[x][4] + "\n";
    to_file = to_file + "network_exporter_" + to_string(x) + "_" + data[x][5] + "\n";
  }

  ofstream myfile;
  myfile.open("example.txt");
  myfile << to_file;
  myfile.close();

}

void what_time_is() {
  time_t now = time(0);
  char * dt = ctime( & now);
  tm * ltm = localtime( & now);
  string timestamp;

  timestamp = to_string(1900 + ltm -> tm_year) + "-";
  timestamp = timestamp + to_string(ltm -> tm_mon) + "-";
  timestamp = timestamp + to_string(ltm -> tm_mday) + "---";
  timestamp = timestamp + to_string(ltm -> tm_hour) + "-";
  timestamp = timestamp + to_string(ltm -> tm_min) + "-";
  timestamp = timestamp + to_string(ltm -> tm_sec);
  cout << timestamp << "\n";
}

void get_Words(string str, int x_pos) {
  istringstream ss(str);
  string word;
  int y_index = 0;
  while (ss >> word) {
     cout << "Y: " << to_string(y_index) << "\n";
    data[x_pos][y_index] = word;
    cout << data[x_pos][y_index] << "\n";
    y_index++;
  }
}

string exec(string command) {
  char buffer[256];
  string result = "";

  // Open pipe to file
  FILE * pipe = popen(command.c_str(), "r");
  if (!pipe) {
    return "popen failed!";
  }

  // read till end of process:
  while (!feof(pipe)) {

    // use buffer to read and add to result
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }

  pclose(pipe);
  return result;
}

void read_file() {
  std::ifstream input("/tmp/network_exporter_output.txt");
  int line_count = 0;
  for (std::string line; getline(input, line);) {
    cout << "X: " << to_string(line_count) << "\n";
    get_Words(line, line_count);
    line_count++;
    list_size++;
  }
}

int main() {
  string ls = exec("lsof -i -n -P | grep LISTEN | awk '{print $1, $2, $3, $5, $8, $9}'");
  std::ofstream out("/tmp/network_exporter_output.txt");
  out << ls;
  out.close();
  read_file();
  Write_Metrics();
}