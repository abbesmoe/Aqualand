/**
 * \file Fish.h
 *
 * \author Moez Abbes
 *
 * Class for any fish
 */

#pragma once
#include "Item.h"

/**
* Class for any fish
*/
class CFish :
    public CItem
{
public:
    /// Default constructor (disabled)
    CFish() = delete;

    /// Copy constructor (disabled)
    CFish(const CFish&) = delete;

    /// Handle updates in time of our fish
    void Update(double elapsed);

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Load the attributes for an item node. 
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Set the fish speed
    /// \param x X Speed
    /// \param y Y Speed
    virtual void SetSpeed(double x, double y) { mSpeedX = x; mSpeedY = y; }
protected:
    /// Constructor
    CFish(CAquarium* aquarium, const std::wstring& filename);

private:
    /// Fish speed in the X direction
    double mSpeedX;

    /// Fish speed in the Y direction
    double mSpeedY;
};

