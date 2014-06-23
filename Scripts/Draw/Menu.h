#ifndef MENU_DRAWING
#define MENU_DRAWING

#include <vector>
#include <SFML/Graphics.hpp>
#include "PointOfView.h"

namespace KNOW{
    class MenuRow;

    /* Single GUI element in menus. Inherited classes can display links to
     * other MenuRows, sliders, checkboxes, etc. */
    class MenuItem
    {
        int Offset;
        virtual void OnCollision();
        virtual void OnCollisionEntry();
        virtual void OnCollisionExit();
    protected:
        bool Collide;
        MenuRow* Parent;
    public:
        sf::Transformable Transformable;
        MenuItem();
        virtual void OnDisplay(int i);
    };

    /* Inherited class which displays a piece of text, which will open a
     * new MenuRow upon beeing clicked.*/
    class MenuItemLink: public MenuItem
    {
        bool PreviousLMBPressed;

        virtual void OnCollision();
        virtual void OnCollisionEntry();
        virtual void OnCollisionExit();
    public:
        sf::Text Transformable;
        MenuItemLink();
        MenuItemLink(const char* Text);
        void OnDisplay(int i);
    };

    /* Row of MenuItems to display */
    class MenuRow
    {
        bool ActiveMenu;
    protected:
        int RowIterator;
    public:
        KNOW::View MenuRowView;
        MenuRow();
        std::vector<MenuItem*> MenuItems;
        void OnDisplay();
    };

    /* Collection of MenuRows forming a Menu */
    class Menu
    {
        friend class MenuRow;
        std::vector<MenuRow*> MenuRows;
        void PrivateOnDisplay();
    public:
        static void OnDisplay();
        Menu();
    };
}

#endif
