/**
 * \file FishBeta.cpp
 *
 * \author Moez Abbes
 */

#include "pch.h"
#include <string>
#include "FishBeta.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 100;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = 50;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedX = 70;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedY = 40;

/**
* Constructor
*/
CFishBeta::CFishBeta(CAquarium* aquarium) : CFish(aquarium, FishBetaImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode> CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);
    itemNode->SetAttribute(L"type", L"beta");
    return itemNode;
}

/**
 * Set the fish speed
 * \param x X Speed
 * \param y Y Speed
 */
void CFishBeta::SetSpeed(double x, double y)
{
    x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    CFish::SetSpeed(x, y);
}