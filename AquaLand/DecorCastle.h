/**
 * \file DecorCastle.h
 *
 * \author Moez Abbes
 *
 * Class for a Decor that's a castle
 */

#pragma once
#include <memory>

#include "Item.h"

 /**
   * Class for a Decor that's a castle
  */
class CDecorCastle :
	public CItem
{
public:
    CDecorCastle::CDecorCastle(CAquarium* aquarium);

    /// Default constructor (disabled)
    CDecorCastle() = delete;

    /// Copy constructor (disabled)
    CDecorCastle(const CDecorCastle&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

