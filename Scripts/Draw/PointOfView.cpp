#include <vector>

#include "PointOfView.h"
#include "Defaults.h"

std::vector<PointOfView*> AllPOVs;

void DefaultPOVDisplayFunc(sf::RenderWindow* Window)
{}

PointOfView::PointOfView ()
{
    DisplayFunc = DefaultPOVDisplayFunc;
    Zoom = 1;
    WindowToRenderTo = &KNOW::DefaultWindow;
    AllPOVs.push_back(this);
    DoesDisplay = true;
}

void PointOfView::OnDisplay()
{
    WindowToRenderTo->setView(View);
    (*DisplayFunc)(WindowToRenderTo);
}

void POVDrawFunc()
{
    int i = 0;
    while (i<AllPOVs.size())
    {
        if (AllPOVs[i]->DoesDisplay)
        {
            AllPOVs[i]->OnDisplay();
        }
        i++;
    }
}
