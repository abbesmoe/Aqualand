/**
 * \file Carp.h
 *
 * \author Moez Abbes
 *
 * Class for a fish of type Carp
 */

#pragma once
#include <memory>

#include "Fish.h"

 /**
  * Class for a fish of type Carp
 */
class CCarp :
    public CFish
{
public:
    CCarp::CCarp(CAquarium * aquarium);

    /// Default constructor (disabled)
    CCarp() = delete;

    /// Copy constructor (disabled)
    CCarp(const CCarp&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Set the fish speed
    /// \param x X Speed
    /// \param y Y Speed
    virtual void SetSpeed(double x, double y) override;
};