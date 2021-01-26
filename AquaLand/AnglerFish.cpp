/**
 * \file AnglerFish.cpp
 *
 * \author Moez Abbes
 */

#include "pch.h"
#include <string>
#include "AnglerFish.h"
#include "Aquarium.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring AnglerFishImageName = L"images/angler.png";

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = -60;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = -60;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedX = -20;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedY = -20;

/**
* Constructor
*/
CAnglerFish::CAnglerFish(CAquarium* aquarium) : CFish(aquarium, AnglerFishImageName)
{
}

/**Set the angler fish location
* \param x X location
* \param y Y location
*/
void CAnglerFish::SetLocation(double x, double y)
{
    double dx = x - GetX();
    double dy = y - GetY();

    CItem::SetLocation(x, y);

    auto closest = GetAquarium()->ClosestItem(this, CatchDistance);
    if (closest != nullptr)
    {
        mCaught = closest;
    }

    auto caught = mCaught.lock();
    if (caught != nullptr)
    {
        caught->Move(dx, dy);
    }
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode> CAnglerFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);
    itemNode->SetAttribute(L"type", L"angler");
    return itemNode;
}

/**
 * Set the fish speed
 * \param x X Speed
 * \param y Y Speed
 */
void CAnglerFish::SetSpeed(double x, double y)
{
    x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    CFish::SetSpeed(x, y);
}