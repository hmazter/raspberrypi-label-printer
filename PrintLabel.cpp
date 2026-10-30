#include <iostream>
#include <string>
#include <cups/cups.h>

std::string get_printer() {
  cups_dest_t *dests = nullptr;
  int num_dests = cupsGetDests(&dests);
  if (num_dests == 0) {
    throw std::domain_error("No printer found");
  }

  if (num_dests > 1) {
    std::cerr << "Multiple printers found\n";
  }

  std::string name = dests->name;
  cupsFreeDests(num_dests, dests);
  return name;
}

int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      throw std::invalid_argument("Usage: PrintLabel <ImageName> [<ImageName> ...]");
    }

    std::string printer_name = get_printer();
    std::cout << "Selected printer: " << printer_name << "\n";

    int num_options = 0;
    cups_option_t *options = nullptr;

    num_options = cupsAddOption("PageSize", "w102h252", num_options, &options); // 99012 Large address

    for (int i = 1; i < argc; i++) {
      if (cupsPrintFile(printer_name.c_str(), argv[i], "Label", num_options, options) == 0) {
        std::cerr << "Failed to print: " << argv[i] << " (" << cupsLastErrorString() << ")\n";
      }
    }
    cupsFreeOptions(num_options, options);

    return 0;
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
