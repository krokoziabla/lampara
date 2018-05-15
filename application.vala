public class Application : Gtk.Application
{
    protected override void activate()
    {
        new RootWindow(this).show();
    }
}
