#ifndef MENU_DRAWING
#define MENU_DRAWING

#include <functional>
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
        virtual void OnDisplay() = 0;
        virtual void OnCollisionCheck();
    };

    /* Inherited class which displays a piece of text, which will open a
     * new MenuRow upon beeing clicked.*/
    class MenuItemLink: public MenuItem
    {
        bool DisplayNext;
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
        void OnCollisionCheck();
    };

    /* Inherited class which displays a slider which can adjust a float
     * value.*/
    class MenuItemSlider: public MenuItem
    {
        class SliderBar: public sf::Drawable, public sf::Transformable
        {
            friend class MenuItemSlider;

            const char* Name;
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
        float* Value;

        const char * Text;
        MenuItemSlider();
        SliderBar Slider;
        void OnDisplay();
    };

    // TODO //
    /* Tickbox adjusting a Boolean variable. */
    class MenuItemTickBox: public MenuItem
    {
        class TickBox: public sf::Drawable, public sf::Transformable
        {
            bool Collide;
            void OnCollision();
            void OnCollisionEntry();
            void OnCollisionExit();

            bool LMBPressed;
            mutable sf::Text Name;
            mutable sf::Sprite TickBoxCube;
            mutable sf::Sprite TickBoxV;
        public:
            bool* Target;
            const char * Text;
            TickBox();
            void draw(sf::RenderTarget& target, sf::RenderStates states)const;
            void CollisionCheck();
        };
    public:
        static sf::Texture TickBoxCubeTex;
        static sf::Texture TickBoxVTex;

        bool* Target;
        TickBox Box;
        MenuItemTickBox();
        void OnDisplay();
        void OnCollisionCheck();
    };

    /* Clickable button, performing a function */
    class MenuItemButton: public MenuItem
    {
        bool Collide;
        void OnCollision();
        void OnCollisionEntry();
        void OnCollisionExit();
    public:
        MenuItemButton();
        std::function<void()> OnClicked = [](){};
        sf::Text Text;
        void OnDisplay();
        void OnCollisionCheck();
    };

    /* Row of MenuItems to display */
    class MenuRow
    {
        bool IsActiveMenu;
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
        friend class MenuItem;
        sf::Vector2f TargetPosition;
    public:
        int HorizontalMenuSize;
        KNOW::View MenuView;
        MenuRow BaseRow;
        MenuRow* Focus;
        void OnDisplay();
        bool PopBack();
        Menu();
    };
}

#endif
