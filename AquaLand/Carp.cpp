/**
 * \file Carp.cpp
 *
 * \author Moez Abbes
 */

#include "pch.h"
#include <string>
#include "Carp.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring CarpImageName = L"images/carp.png";

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 60;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = -30;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedX = 50;

/// Maximum speed in the X direction in
/// in pixels per second
const double MinSpeedY = -20;

/**
* Constructor
*/
CCarp::CCarp(CAquarium* aquarium) : CFish(aquarium, CarpImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode> CCarp::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);
    itemNode->SetAttribute(L"type", L"carp");
    return itemNode;
}

/**
 * Set the fish speed
 * \param x X Speed
 * \param y Y Speed
 */
void CCarp::SetSpeed(double x, double y)
{
    x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    CFish::SetSpeed(x, y);
}