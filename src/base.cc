#include <iostream>
#include <gtkmm.h>
#include <glibmm/fileutils.h>  // For css file loading
#include "locate_binary.h"
#include <filesystem>

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

  Glib::setenv("GTK_CSD", "0", true);  // Disable CSD for native window decorations
#ifndef _WIN32
  std::string bin_dir = get_binary_directory ();
  Glib::setenv("GDK_PIXBUF_MODULE_FILE", bin_dir + "/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache", true);
  Glib::setenv("GSETTINGS_SCHEMA_DIR", bin_dir + "/share/glib-2.0/schemas:" + Glib::getenv("GSETTINGS_SCHEMA_DIR"), true);
  Glib::setenv("XDG_DATA_DIRS", bin_dir + "/share:" + Glib::getenv("XDG_DATA_DIRS"), true);
#endif

  
  auto myapp = Gtk::Application::create("org.gtkmm.winda");

  return myapp->make_window_and_run<MyWindow>(argc, argv);
}
