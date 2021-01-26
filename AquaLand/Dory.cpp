/**
 * \file Dory.cpp
 *
 * \author Moez Abbes
 */

#include "pch.h"
#include <string>
#include "Dory.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring DoryImageName = L"images/dory.png";

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 30;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = 90;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedX = 20;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedY = 70;

/**
* Constructor
*/
CDory::CDory(CAquarium* aquarium) : CFish(aquarium, DoryImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode> CDory::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);
    itemNode->SetAttribute(L"type", L"dory");
    return itemNode;
}

/**
 * Set the fish speed
 * \param x X Speed
 * \param y Y Speed
 */
void CDory::SetSpeed(double x, double y)
{
    x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    CFish::SetSpeed(x, y);
}