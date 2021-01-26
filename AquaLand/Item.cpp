/**
 * \file Item.cpp
 *
 * \author Moez Abbes
 */

#include "pch.h"
#include <string>
#include "Item.h"
#include "Aquarium.h"
#include "XmlNode.h"

using namespace Gdiplus;
using namespace std;

/** Constructor
* \param aquarium The aquarium this item is a member of
*/
CItem::CItem(CAquarium* aquarium, const std::wstring& filename) :
    mAquarium(aquarium)
{
    mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mItemImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}


/**
 * Destructor
 */
CItem::~CItem()
{
}

/**
 * Determine the distance from this item to some other item.
 * \param other Other item we are testing
 * \return Distance in pixels
 */
double CItem::Distance(std::shared_ptr<CItem> other)
{
    // Create a vector in the direction we are from the nudger
    double dx = mX - other->mX;
    double dy = mY - other->mY;

    // Determine how far away we are
    return sqrt(dx * dx + dy * dy);
}

/**
 *  Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CItem::HitTest(int x, int y)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image.
    // Subtracting the center makes x, y relative to the center of 
    // the image. Adding half the size makes x, y relative to the top 
    // corner of the image.
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mItemImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mItemImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}

/**
 * Draw this item
 * \param graphics Graphics object to draw on
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    if (mMirror)
    {
        graphics->DrawImage(mItemImage.get(),
            float(GetX() + wid / 2), float(GetY() - hit / 2),
            -(float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
    }
    else
    {
        graphics->DrawImage(mItemImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
    }
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode> CItem::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = node->AddChild(L"item");

    itemNode->SetAttribute(L"x", mX);
    itemNode->SetAttribute(L"y", mY);

    return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * \param node The Xml node we are loading the item from
 */
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mX = node->GetAttributeDoubleValue(L"x", 0);
    mY = node->GetAttributeDoubleValue(L"y", 0);
}