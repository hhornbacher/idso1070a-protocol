#ifndef _GRAPH_WIDGET_H_
#define _GRAPH_WIDGET_H_

#include <gtkmm/widget.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/styleproperty.h>

class GraphWidget : public Gtk::Widget
{
public:
  GraphWidget();
  virtual ~GraphWidget();

protected:
  //Overrides:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void get_preferred_width_vfunc(int &minimum_width, int &natural_width) const override;
  void get_preferred_height_for_width_vfunc(int width, int &minimum_height, int &natural_height) const override;
  void get_preferred_height_vfunc(int &minimum_height, int &natural_height) const override;
  void get_preferred_width_for_height_vfunc(int height, int &minimum_width, int &natural_width) const override;
  void on_size_allocate(Gtk::Allocation &allocation) override;
  void on_map() override;
  void on_unmap() override;
  void on_realize() override;
  void on_unrealize() override;
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

  //Signal handler:
  void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection> &section, const Glib::Error &error);

  Glib::RefPtr<Gdk::Window> refGdkWindow;
  Glib::RefPtr<Gtk::CssProvider> refCssProvider;
};

#endif // _GRAPH_WIDGET_H_