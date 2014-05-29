#include <vector>

#include "PointOfView.h"
#include "Defaults.h"

std::vector<PointOfView*> AllPOVs;

PointOfView::PointOfView ()
{
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
        AllPOVs[i]->OnDisplay();
        i++;
    }
}
