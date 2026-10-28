#include "sprite/graphics/EditorWindow.h"
#include <iostream>

#if defined(linux) || defined(APPLE)
#include <X11/Xutil.h>
#include <X11/Xlib.h> 
#include <X11/Xatom.h>
#endif

namespace sprite::graphics
{

    EditorWindow::EditorWindow(unsigned width, unsigned height, const std::string& title)
        : sf::RenderWindow(sf::VideoMode(sf::Vector2u{width, height}), title.c_str(), sf::Style::Titlebar | sf::Style::Close)
    { 
        setFramerateLimit(60);

#if defined(linux) || defined(APPLE)

        ::Window xWindow = (::Window)getNativeHandle();

        // To get the Display*, you typically open a connection to the default display
        Display* display = XOpenDisplay(NULL);

        if (display) {
            // You now have both the Display* and the Window handle
            // Example: Disable resizing using X11 hints as discussed previously
            XSizeHints* hints = XAllocSizeHints();
            hints->flags = PMinSize | PMaxSize;
            hints->min_width = hints->max_width = width;
            hints->min_height = hints->max_height = height;

            XSetWMNormalHints(display, xWindow, hints);
            XSync(display, False);
            // 2. Explicitly tell Extended Window Manager Hints (EWMH) to disable resize
            // This is critical for modern compositors and XWayland (WSLg)
            Atom wm_allowed = XInternAtom(display, "_NET_WM_ALLOWED_ACTIONS", False);
            Atom action_move = XInternAtom(display, "_NET_WM_ACTION_MOVE", False);
            Atom action_close = XInternAtom(display, "_NET_WM_ACTION_CLOSE", False);
            
            // Only allow moving and closing, omitting _NET_WM_ACTION_RESIZE and _NET_WM_ACTION_MAXIMIZE
            Atom allowed_actions[] = { action_move, action_close };
            XChangeProperty(
                display, xWindow, wm_allowed, XA_ATOM, 32, 
                PropModeReplace, (unsigned char*)allowed_actions, 2
            );
            XFree(hints);
            XFlush(display);

            XCloseDisplay(display);
        }
#endif


        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

        std::cout << "SFML VERSION: "
                << SFML_VERSION_MAJOR << "."
                << SFML_VERSION_MINOR << "."
                << SFML_VERSION_PATCH << std::endl;

        int posX = (desktopMode.size.x - width) / 2;
        int posY = (desktopMode.size.y - height) / 2;

        setPosition(sf::Vector2i(posX, posY));
    }

}
