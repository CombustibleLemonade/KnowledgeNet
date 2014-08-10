#ifndef ANIMATION
#define ANIMATION

#include <functional>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;

template <class T>
class AnimationPoint {
public:
    sf::Time X;
    T Y;
    AnimationPoint(sf::Time Xarg);
    AnimationPoint(sf::Time Xarg, T Yarg);
};

template <class T>
class Animation
{
public:
    AnimationPoint<T>* FindPointAfter(sf::Time Xarg);
    std::vector< AnimationPoint<T> > Points;
    virtual T Y(sf::Time X);
};

template <class T>
class AnimationLinear: public Animation<T>
{
public:
    T Y(sf::Time X);
    void Test();
};



template <class T>
AnimationPoint<T>::AnimationPoint(sf::Time Xarg)
{
    X = Xarg;
}

template <class T>
AnimationPoint<T>::AnimationPoint(sf::Time Xarg, T Yarg)
{
    X = Xarg;
    Y = Yarg;
}

template <class T>
AnimationPoint<T>* Animation<T>::FindPointAfter(sf::Time Xarg)
{
    int i = 0;
    if (Points.size() == 0)
        return NULL;
    if (Xarg > Points.back().X)
        return NULL;
    while (i < Points.size())
    {
        if (Points[i].X > Xarg)
        {
            return &(Points[i]);
        }
        i++;
    }
    return &(Points.back());
}

template <class T>
T Animation<T>::Y(sf::Time X)
{
    AnimationPoint<T>* Test = FindPointAfter(sf::Time::Zero);
    return Test->Y;
}

template <class T>
T AnimationLinear<T>::Y(sf::Time X)
{
    if(this->Points[0].X>X)
    {
        return this->Points[0].Y;
    }
    if(this->Points.back().X<X)
    {
        return this->Points.back().Y;
    }

    AnimationPoint<T>* AfterPointer = this->FindPointAfter(X);

    if (AfterPointer)
    {
        AnimationPoint<T> After = *AfterPointer;
        AnimationPoint<T> Before = *(AfterPointer - 1);
        sf::Time DeltaX = After.X - Before.X;
        T DeltaY = After.Y - Before.Y;
        T Slope = DeltaY/DeltaX.asSeconds();
        return Slope*(X-Before.X).asSeconds()+Before.Y;
    }
}

#endif
