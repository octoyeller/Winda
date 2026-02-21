#include <iostream>
#include <gtkmm.h>
#include <glibmm/fileutils.h>  // For css file loading
#include "locate_binary.h"

class MyWindow : public Gtk::Window {
public:
  MyWindow();
};

MyWindow::MyWindow() {
  set_title("Winda");
  set_default_size(400, 400);

  // Icon
#ifndef _WIN32
  auto display = get_display();
  auto theme = Gtk::IconTheme::get_for_display(display);
  theme->add_resource_path("/org/gtkmm/winda/icons");
#endif
  set_icon_name("winda");  // Base name without extension

  // Load CSS from file
#ifdef _WIN32
    std::string css_path = "style.css";
#else
    std::string css_path = get_binary_directory () + "style.css";
#endif
  auto provider = Gtk::CssProvider::create();
  try {
    provider->load_from_path(css_path);  // Relative to exe; use absolute path if needed
  } catch (const Glib::FileError& ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
  }

  get_style_context()->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}


int main(int argc, char* argv[]){

  Glib::setenv("GTK_CSD", "0", true);  // Disable CSD for native windows look

  
  auto myapp = Gtk::Application::create();

  return myapp->make_window_and_run<MyWindow>(argc, argv);
}
