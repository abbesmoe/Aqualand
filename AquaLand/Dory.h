/**
 * \file Dory.h
 *
 * \author Moez Abbes
 *
 * Class for a fish of type Dory
 */

#pragma once
#include <memory>

#include "Fish.h"

 /**
  * Class for a fish of type Dory
 */
class CDory :
    public CFish
{
public:
    CDory::CDory(CAquarium* aquarium);

    /// Default constructor (disabled)
    CDory() = delete;

    /// Copy constructor (disabled)
    CDory(const CDory&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Set the fish speed
    /// \param x X Speed
    /// \param y Y Speed
    virtual void SetSpeed(double x, double y) override;
};