/**
 * \file FishBeta.h
 *
 * \author Moez Abbes
 *
 * Class for a fish of type Beta
 */

#pragma once
#include <memory>

#include "Fish.h"

 /**
  * Class for a fish of type Beta
 */
class CFishBeta :
    public CFish
{
public:
    CFishBeta::CFishBeta(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Set the fish speed
    /// \param x X Speed
    /// \param y Y Speed
    virtual void SetSpeed(double x, double y) override;
};

