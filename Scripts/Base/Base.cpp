#include <vector>

#include "Base.h"


namespace KNOW {
    std::vector<TrackMovement*> AllMovementsTracked;

    TrackMovement::TrackMovement(sf::Vector2f* TargetArg, bool *MoveWhenArg, sf::Vector2f* SourceArg)
    {
        AllMovementsTracked.push_back(this);
        Target = TargetArg;
        MoveWhen = MoveWhenArg;
        Source = SourceArg;
    }

    void TrackMovement::OnDisplay()
    {
        if (*MoveWhen)
        {
            DeltaTarget = sf::Vector2f(*Source - PreviousSourceLocation);
            *Source -= DeltaTarget;
        }
        else DeltaTarget = sf::Vector2f(0.0, 0.0);
    }

    void BaseDrawFunc()
    {
        int i = 0;
        while (i<AllMovementsTracked.size())
        {
            AllMovementsTracked[i]->OnDisplay();
        }
    }
}

