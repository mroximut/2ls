/*******************************************************************\

Module: 2LS Main Module

Author: Daniel Kroening, Peter Schrammel

\*******************************************************************/

/// \file
/// 2LS Main Module

#include <util/unicode.h>
#include <iostream>
#include <chrono>
#include <fstream>

#include "2ls_parse_options.h"
#include "solvers/sat/satcheck_ipasir.h"

#ifdef _MSC_VER

int wmain(int argc, const wchar_t **argv_wide)
{
  const char **argv=narrow_argv(argc, argv_wide);
  twols_parse_optionst parse_options(argc, argv);
  return parse_options.main();
}

#else

// Global CNF file that can be accessed by satcheck_ipasir
std::ofstream global_cnf_file;
std::string cnf_filename = "";
int cnf_file_position = 0;

int main(int argc, const char **argv)
{
  auto start_time = std::chrono::steady_clock::now();
  for(int i = 0; i < argc; ++i)
  {
    std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    if (cnf_file_position > 0 && i >= cnf_file_position + 2) {
      argv[i - 2] = argv[i];
    }
    if (argv[i] == std::string("--dump-cnf") && i + 1 < argc) {
      cnf_filename = argv[i + 1];
      cnf_file_position = i;
    }
  }

  if (cnf_file_position > 0) {
    argc -= 2;
    global_cnf_file.open(cnf_filename);
  }


  twols_parse_optionst parse_options(argc, argv);
  int res = parse_options.main();

  if (cnf_file_position > 0) {
    global_cnf_file.close();
  }

  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "t FINAL PROCESSING_TIME: " << duration.count() / 1000.0f << std::endl;
  std::cout << "t FINAL SAT_TIME: " << satcheck_ipasirt::sat_time << std::endl;
  std::cout << "t FINAL SAT_CALLS: " << satcheck_ipasirt::sat_calls << std::endl;
  std::cout << "s FINAL EC=" << res << std::endl;
  return res;
}

#endif
