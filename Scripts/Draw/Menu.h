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
    protected:
        bool Collide;
    public:
        sf::Transformable* Transformable;
        MenuItem();
        virtual void OnDisplay();
    };

    /* Inherited class which displays a piece of text, which will open a
     * new MenuRow upon beeing clicked.*/
    class MenuItemLink: public MenuItem
    {
        bool PreviousLMBPressed;
        void OnCollision();
        void OnCollisionEntry();
        void OnCollisionExit();
    public:
        MenuRow* Next;
        sf::Text Text;
        MenuItemLink();
        MenuItemLink(const char* Text);
        void OnDisplay();
    };

    /* Inherited class which displays a slider which can adjust a float
     * value.*/
    class MenuItemSlider: public MenuItem
    {
        class SliderBar: public sf::Drawable, public sf::Transformable
        {
            friend class MenuItemSlider;

            const char* PreviousText;
            mutable sf::Text TextDrawable;
            mutable sf::Text ValueDisplay;
            mutable sf::Sprite BackgroundSprite;
            mutable sf::RectangleShape Rectangle;
            void InitObjects();

            void OnCollision();
            void OnCollisionEntry();
            void OnCollisionExit();

            float PrevSliderValue;
            float PrevMouseXPos;
            float MouseXPos;
            bool LMBPressed;
            bool PrevLMBPressed;
            bool IsSliding;
            void OnDrag();
            void OnDragEntry();
            void OnDragExit();

        public:
            SliderBar();
            SliderBar(const char* TextArg);

            float* Value;
            float Min;
            float Max;

            const char * Text;
            void draw(sf::RenderTarget& target,sf::RenderStates states)const;

            float CursorToSliderXPos(float CursorX) const;
            float SliderToCursorXPos(float SliderX) const;

            sf::FloatRect getGlobalBounds();

            void setRectangleColor(sf::Color ColorArg);
        };

        bool PrevCollide;
        void OnSliderCollision();
        void OnSliderCollisionEntry();
        void OnSliderCollisionExit();

        static bool BackgroundTextureInitialized;
    public:
        static sf::Texture SlideTexture;

        const char * Text;
        MenuItemSlider();
        SliderBar Slider;
        void OnDisplay();
    };

    /* Row of MenuItems to display */
    class MenuRow
    {
        bool ActiveMenu;
        int Scroll;
    protected:
        friend class MenuItemLink;
        friend class Menu;
        int HorizontalSize;
        int xLocation;
    public:

        KNOW::View MenuRowView;
        MenuRow();
        std::vector<MenuItem*> MenuItems;
        void OnDisplay();
    };

    /* Collection of MenuRows forming a Menu */
    class Menu
    {
        std::vector<MenuRow*> MenuRows;
        void PrivateOnDisplay();
        static MenuRow* Focus;
    public:
        KNOW::View MenuView;
        static void OnDisplay();
        Menu();
        void AddRow(MenuRow RowArg);
        void PopRow();
    };
}

#endif
