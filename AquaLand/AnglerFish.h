/**
 * \file AnglerFish.h
 *
 * \author Moez Abbes
 *
 * Class for a fish of type Angler
 */

#pragma once
#include <memory>

#include "Fish.h"

/**
* Class for a fish of type Angler
*/
class CAnglerFish :
    public CFish
{
public:
    CAnglerFish::CAnglerFish(CAquarium* aquarium);

    /// Default constructor (disabled)
    CAnglerFish() = delete;

    /// Copy constructor (disabled)
    CAnglerFish(const CAnglerFish&) = delete;

    /// Set the angler fish location
    /// \param x X location
    /// \param y Y location
    virtual void SetLocation(double x, double y) override;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Set the fish speed
    /// \param x X Speed
    /// \param y Y Speed
    virtual void SetSpeed(double x, double y) override;

private:
    /// How near a fish must be for use to catch it
    const double CatchDistance = 150;

    /// Any currently caught item
    std::weak_ptr<CItem> mCaught;

    std::weak_ptr<CItem> mCaughtFish;
};

