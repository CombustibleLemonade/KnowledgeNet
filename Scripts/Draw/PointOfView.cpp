#include <iostream>

#include <vector>

#include "PointOfView.h"
#include "Base/Defaults.h"

namespace KNOW
{

    std::vector<KNOW::View*> AllViews;


    View::View()
    {
        ZoomValue = 1;
        AllViews.push_back(this);
    }

    void View::OnDisplay(){
        for (int i = 0; i<AllViews.size(); i++)
        {
            AllViews[i]->AdjustToScreenRes();
        }
    }

    void View::AdjustToScreenRes(){
        setSize(sf::Vector2f(KNOW::DefaultWindow.getSize()));
        zoom(ZoomValue);
    }

    void View::SetTargetPosition(sf::Vector2f TargetPosition)
    {}
}
