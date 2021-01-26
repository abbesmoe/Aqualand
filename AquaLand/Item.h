/**
 * \file Item.h
 *
 * \author Moez Abbes
 *
 * Base class for any item in our aquarium.
 */

#pragma once
#include <memory>
#include <string>
#include "XmlNode.h"

class CAquarium;

/**
* Base class for any item in our aquarium.
*/
class CItem
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;

    virtual ~CItem();

    /** The X location of the item
    * \returns X location in pixels */
    virtual double GetX() const { return mX; }

    /** The Y location of the item
    * \returns Y location in pixels */
    virtual double GetY() const { return mY; }

    /// Set the item location
    /// \param x X location
    /// \param y Y location
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /// Draw this item
    /// \param graphics Graphics device to draw on
    void Draw(Gdiplus::Graphics* graphics);

    /** Test this item to see if it has been clicked on
     * \param x X location on the aquarium to test
     * \param y Y location on the aquarium to test
     * \return true if clicked on */
    bool HitTest(int x, int y);

    /// Determine the distance from this item to some other item.
    double CItem::Distance(std::shared_ptr<CItem> other);

    /// Move the item by directly changing x,y by delta amounts
    /// \param dx X amount to move
    /// \param dy Y amount to move
    void Move(double dx, double dy) { mX += dx; mY += dy; }

    /// returns a pointer to CAquarium that can be used by Anglerfish
    /// to call CAquarium functions.
    CAquarium* GetAquarium() { return mAquarium; }

    /// Save this item to an XML node
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Load the attributes for an item node. 
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    /// Set the mirror status
    /// \param m New mirror flag
    void SetMirror(bool m) { mMirror = m; }

    /// Get the width of the aquarium
    /// \returns Aquarium width
    int GetWidth() const { return mItemImage->GetWidth(); }

    /// Get the height of the aquarium
    /// \returns Aquarium height
    int GetHeight() const { return mItemImage->GetHeight(); }

protected:
    CItem(CAquarium* aquarium, const std::wstring& filename);

private:
    /// The aquarium this item is contained in
    CAquarium* mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The image of this fish
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;

    bool mMirror = false;   ///< True mirrors the item image
};
